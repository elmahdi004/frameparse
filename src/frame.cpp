/*
 * frameparse - top-level frame parsing.
 *
 * Validates the 10-byte header, then iterates the declared records, handing
 * each payload to fp_parse_record().  All framing reads go through the
 * bounded reader, so the only memory-safety concern lives in the record
 * layer (the label accumulation).
 */
#include <stdlib.h>
#include <string.h>

#include "internal.h"

fp_status fp_frame_init(fp_frame *frame) {
    memset(frame, 0, sizeof(*frame));
    frame->label = (char *)malloc(FP_MAX_LABEL);
    if (frame->label == NULL) {
        return FP_ERR_NOMEM;
    }
    return FP_OK;
}

void fp_frame_free(fp_frame *frame) {
    if (frame == NULL) {
        return;
    }
    free(frame->label);
    frame->label = NULL;
    frame->label_len = 0;
}

fp_status fp_parse(const uint8_t *buf, size_t len, fp_frame *frame) {
    fp_reader r;
    fp_reader_init(&r, buf, len);

    /* --- Header --- */
    const uint8_t *magic = fp_read_bytes(&r, FP_MAGIC_LEN);
    if (magic == NULL) {
        return FP_ERR_SHORT;
    }
    if (memcmp(magic, FP_MAGIC, FP_MAGIC_LEN) != 0) {
        return FP_ERR_MAGIC;
    }

    uint8_t version;
    uint8_t flags;
    if (!fp_read_u8(&r, &version) || !fp_read_u8(&r, &flags)) {
        return FP_ERR_SHORT;
    }
    if (version != FP_VERSION) {
        return FP_ERR_VERSION;
    }

    uint16_t record_count;
    uint16_t reserved;
    if (!fp_read_u16be(&r, &record_count) || !fp_read_u16be(&r, &reserved)) {
        return FP_ERR_SHORT;
    }
    if (reserved != 0) {
        return FP_ERR_RESERVED;
    }
    frame->record_count = record_count;

    /* --- Records --- */
    for (uint16_t i = 0; i < record_count; i++) {
        uint8_t  rec_type;
        uint16_t rec_len;
        if (!fp_read_u8(&r, &rec_type) || !fp_read_u16be(&r, &rec_len)) {
            return FP_ERR_RECORD;
        }

        const uint8_t *payload = fp_read_bytes(&r, rec_len);
        if (payload == NULL) {
            return FP_ERR_RECORD;
        }

        fp_status st = fp_parse_record(rec_type, payload, rec_len, frame);
        if (st != FP_OK) {
            return st;
        }
    }

    return FP_OK;
}

const char *fp_strstatus(fp_status status) {
    switch (status) {
    case FP_OK:           return "ok";
    case FP_ERR_SHORT:    return "truncated input";
    case FP_ERR_MAGIC:    return "bad magic";
    case FP_ERR_VERSION:  return "unsupported version";
    case FP_ERR_RESERVED: return "reserved field not zero";
    case FP_ERR_RECORD:   return "malformed record";
    case FP_ERR_TLV:      return "malformed TLV";
    case FP_ERR_NOMEM:    return "out of memory";
    default:              return "unknown";
    }
}
