#!/usr/bin/env python3
"""Generate a seed corpus of valid FRMP frames for the fuzzer.

Run from the repository root:

    python3 tools/gen_corpus.py

Writes seeds into fuzz/corpus/parser_fuzzer/.  Good seeds matter: they teach
the fuzzer the structure of the format so it can reach deep, structure-gated
code paths quickly instead of wasting time guessing a valid header.
"""
import os
import struct

OUT_DIR = os.path.join("fuzz", "corpus", "parser_fuzzer")

MAGIC = b"FRMP"
VERSION = 1

REC_METADATA = 0x01
REC_PAYLOAD = 0x02
REC_ROUTING = 0x03

TLV_LABEL = 0x01
TLV_PRIORITY = 0x02
TLV_TTL = 0x03


def header(record_count):
    return MAGIC + bytes([VERSION, 0x00]) + struct.pack(">HH", record_count, 0)


def tlv(t, value):
    assert len(value) <= 255
    return bytes([t, len(value)]) + value


def record(rec_type, payload):
    return bytes([rec_type]) + struct.pack(">H", len(payload)) + payload


def metadata(label=b"", priority=None, ttl=None, extra=b""):
    payload = b""
    if label:
        payload += tlv(TLV_LABEL, label)
    if priority is not None:
        payload += tlv(TLV_PRIORITY, bytes([priority]))
    if ttl is not None:
        payload += tlv(TLV_TTL, bytes([ttl]))
    payload += extra
    return record(REC_METADATA, payload)


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    seeds = {}

    # 1) Minimal valid frame: header only, no records.
    seeds["empty"] = header(0)

    # 2) One metadata record with a short label + priority + ttl.
    seeds["metadata_simple"] = header(1) + metadata(
        label=b"edge-router-01", priority=7, ttl=64
    )

    # 3) Mixed frame: a payload record followed by a metadata record.
    seeds["mixed"] = (
        header(2)
        + record(REC_PAYLOAD, b"\x00\x01\x02\x03 telemetry sample")
        + metadata(label=b"sensor-a", priority=3, ttl=32)
    )

    # 4) A routing record only.
    seeds["routing"] = header(1) + record(
        REC_ROUTING, b"\x0a\x00\x00\x01\x0a\x00\x00\x02"
    )

    # 5) Two small label fragments that accumulate (still within bounds).
    seeds["label_fragments"] = header(1) + record(
        REC_METADATA, tlv(TLV_LABEL, b"site-") + tlv(TLV_LABEL, b"brussels")
    )

    # 6) A "rich" metadata record: a 60-byte label (valid, <= 64) followed by
    #    a large unknown TLV.  This is a near-miss: a single byte flip of the
    #    label length lets the value run long enough to overflow the 64-byte
    #    destination buffer, so it gives the fuzzer a fast path to the bug.
    big_label = b"A" * 60
    filler = tlv(0x09, b"B" * 130)  # unknown TLV, skipped by the parser
    seeds["rich_metadata"] = header(1) + record(
        REC_METADATA, tlv(TLV_LABEL, big_label) + filler
    )

    for name, data in seeds.items():
        path = os.path.join(OUT_DIR, name + ".frmp")
        with open(path, "wb") as f:
            f.write(data)
        print(f"wrote {path} ({len(data)} bytes)")


if __name__ == "__main__":
    main()
