# frameparse

A small C++ library that parses a compact binary container format (**FRMP**)
made of a header, a list of records, and nested TLV options. It ships with a
command-line decoder, a unit-test suite, and a **ClusterFuzzLite** fuzzing
harness.

> ⚠️ **This is a fuzzing-practice target.** It contains an *intentional*
> memory-safety bug so you can learn the full fuzzing workflow end to end
> (build → fuzz → crash → triage → fix). It is **not** production code and is
> not meant to be submitted anywhere as a "found in the wild" vulnerability.
> See [The intentional bug](#the-intentional-bug).

## Format

All multi-byte integers are big-endian.

```
Header (10 bytes)
  magic         4   "FRMP"
  version       1   must be 1
  flags         1   reserved
  record_count  2   number of records
  reserved      2   must be 0

Record (repeated record_count times)
  rec_type      1   0x01 METADATA | 0x02 PAYLOAD | 0x03 ROUTING
  rec_len       2   payload length
  payload     rec_len

METADATA payload = sequence of TLVs
  tlv_type      1   0x01 LABEL | 0x02 PRIORITY | 0x03 TTL
  tlv_len       1   value length
  value       tlv_len
```

Unknown record types and unknown TLV types are skipped, so the format is
forward-compatible.

## Layout

```
frameparse/
├── include/frameparse.h     public API
├── src/                     parser implementation
│   ├── internal.h           bounded reader + TLV helpers
│   ├── reader.cpp           bounds-checked read cursor
│   ├── tlv.cpp              TLV extraction
│   ├── record.cpp           record / metadata parsing
│   └── frame.cpp            header + record iteration
├── tools/
│   ├── framedump.cpp        CLI decoder
│   └── gen_corpus.py        seed-corpus generator
├── fuzz/
│   ├── parser_fuzzer.cc     libFuzzer harness
│   └── corpus/parser_fuzzer/  seed inputs
├── tests/test_basic.cpp     unit tests
└── .clusterfuzzlite/
    ├── build.sh             builds $OUT/parser_fuzzer
    └── Dockerfile           OSS-Fuzz base-builder image
```

## Building & running the tools

With any C++ compiler:

```sh
# CLI decoder
c++ -I include src/*.cpp tools/framedump.cpp -o framedump

# Unit tests
c++ -I include src/*.cpp tests/test_basic.cpp -o test_basic && ./test_basic

# Generate the seed corpus
python3 tools/gen_corpus.py
```

## Fuzzing

### Locally with clang + libFuzzer + AddressSanitizer

```sh
clang++ -g -O1 -fno-omit-frame-pointer \
    -fsanitize=address,fuzzer \
    -I include src/*.cpp fuzz/parser_fuzzer.cc -o parser_fuzzer

./parser_fuzzer fuzz/corpus/parser_fuzzer/
```

### With the ClusterFuzzLite layout

`.clusterfuzzlite/build.sh` compiles every `src/*.cpp` plus the harness into
`$OUT/parser_fuzzer` and zips the seed corpus, using the standard
`$CXX` / `$CXXFLAGS` / `$LIB_FUZZING_ENGINE` / `$OUT` variables.

## The intentional bug

`src/record.cpp` accumulates `LABEL` TLVs into a fixed 64-byte heap buffer
with `memcpy`, but never checks that `label_len + tlv_len` stays within
`FP_MAX_LABEL`. Reaching it requires a valid header, a `METADATA` record, and
a `LABEL` TLV whose value is long enough — i.e. structured input, not random
bytes. The `rich_metadata` seed is one byte away from triggering it, which is
what lets the fuzzer find it quickly.

The fix is a bounds check before the copy (truncate or reject when the label
would overflow). Try fuzzing first, watch AddressSanitizer report the
`heap-buffer-overflow`, then add the check and confirm the crash is gone.

## License

MIT — see [LICENSE](LICENSE).
