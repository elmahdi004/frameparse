/*
 * frameparse - tiny serializer for the aggregate frame view.
 *
 * This encoder is intentionally narrow.  It only emits a single METADATA
 * record that mirrors the aggregate fields we keep in `fp_frame`, which is
 * enough for tests, small tools, and round-trip checks.  The code is written
 * in the same defensive style as the parser: size checks happen before any
 * copy, payload lengths are computed up front, and the function returns a
 * parser-style status code instead of assuming the input is well formed.
 */
#include <string.h>

#include "frameparse_tools.h"

static int fp_write_u8(uint8_t *buf, size_t cap, size_t *pos, uint8_t value) {
    if (*pos >= cap) {
        return 0;
    }
    buf[*pos] = value;
    (*pos)++;
    return 1;
}

static int fp_write_u16be(uint8_t *buf, size_t cap, size_t *pos, uint16_t value) {
    return fp_write_u8(buf, cap, pos, (uint8_t)(value >> 8)) &&
           fp_write_u8(buf, cap, pos, (uint8_t)(value & 0xff));
}

static int fp_write_bytes(uint8_t *buf, size_t cap, size_t *pos,
                          const uint8_t *src, size_t len) {
    if (cap - *pos < len) {
        return 0;
    }
    memcpy(buf + *pos, src, len);
    *pos += len;
    return 1;
}

static size_t fp_metadata_payload_size(const fp_frame *frame) {
    size_t payload = 0;
    if (frame->label_len > 0) {
        payload += 2 + frame->label_len;
    }
    payload += 3; /* PRIORITY TLV */
    payload += 3; /* TTL TLV */
    return payload;
}

size_t fp_emit_metadata_frame_size(const fp_frame *frame) {
    if (frame == NULL || frame->label_len > FP_MAX_LABEL ||
        frame->label_len > UINT8_MAX) {
        return 0;
    }
    return FP_HEADER_LEN + 3 + fp_metadata_payload_size(frame);
}

fp_status fp_emit_metadata_frame(const fp_frame *frame, uint8_t *buf,
                                 size_t cap, size_t *written) {
    if (frame == NULL || buf == NULL || written == NULL) {
        return FP_ERR_RECORD;
    }
    if (frame->label_len > FP_MAX_LABEL || frame->label_len > UINT8_MAX) {
        return FP_ERR_TLV;
    }
    if (frame->label_len > 0 && frame->label == NULL) {
        return FP_ERR_RECORD;
    }

    size_t need = fp_emit_metadata_frame_size(frame);
    if (need == 0 || cap < need) {
        return FP_ERR_SHORT;
    }

    size_t pos = 0;
    if (!fp_write_bytes(buf, cap, &pos, (const uint8_t *)FP_MAGIC, FP_MAGIC_LEN) ||
        !fp_write_u8(buf, cap, &pos, FP_VERSION) ||
        !fp_write_u8(buf, cap, &pos, 0x00) ||
        !fp_write_u16be(buf, cap, &pos, 1) ||
        !fp_write_u16be(buf, cap, &pos, 0)) {
        return FP_ERR_SHORT;
    }

    size_t payload_len = fp_metadata_payload_size(frame);
    if (!fp_write_u8(buf, cap, &pos, FP_REC_METADATA) ||
        !fp_write_u16be(buf, cap, &pos, (uint16_t)payload_len)) {
        return FP_ERR_SHORT;
    }

    if (frame->label_len > 0) {
        if (!fp_write_u8(buf, cap, &pos, FP_TLV_LABEL) ||
            !fp_write_u8(buf, cap, &pos, (uint8_t)frame->label_len) ||
            !fp_write_bytes(buf, cap, &pos, (const uint8_t *)frame->label, frame->label_len)) {
            return FP_ERR_SHORT;
        }
    }

    if (!fp_write_u8(buf, cap, &pos, FP_TLV_PRIORITY) ||
        !fp_write_u8(buf, cap, &pos, 1) ||
        !fp_write_u8(buf, cap, &pos, frame->priority) ||
        !fp_write_u8(buf, cap, &pos, FP_TLV_TTL) ||
        !fp_write_u8(buf, cap, &pos, 1) ||
        !fp_write_u8(buf, cap, &pos, frame->ttl)) {
        return FP_ERR_SHORT;
    }

    *written = pos;
    return FP_OK;
}
