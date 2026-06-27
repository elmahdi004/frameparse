/*
 * frameparse - formatting helpers.
 *
 * This file is deliberately separate from the parser core so that the core
 * stays focused on wire validation while the user-facing helpers handle
 * presentation concerns.  The functions are careful about truncation: every
 * formatter always NUL-terminates when the destination buffer is non-empty,
 * and they return the total number of bytes that would have been written.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "frameparse_tools.h"

static size_t fp_append_text(char *out, size_t cap, size_t pos, const char *text) {
    if (cap == 0) {
        return pos + strlen(text);
    }

    size_t remaining = (pos < cap) ? cap - pos - 1 : 0;
    size_t text_len = strlen(text);
    if (remaining > 0) {
        size_t copy = (text_len < remaining) ? text_len : remaining;
        memcpy(out + pos, text, copy);
        out[pos + copy] = '\0';
    }
    return pos + text_len;
}

static size_t fp_append_uint(char *out, size_t cap, size_t pos, unsigned int value) {
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%u", value);
    return fp_append_text(out, cap, pos, tmp);
}

static int fp_label_is_printable(const fp_frame *frame) {
    for (size_t i = 0; i < frame->label_len; i++) {
        unsigned char ch = (unsigned char)frame->label[i];
        if (!isprint(ch) || ch == '\\') {
            return 0;
        }
    }
    return 1;
}

const char *fp_record_type_name(uint8_t rec_type) {
    switch (rec_type) {
    case FP_REC_METADATA: return "metadata";
    case FP_REC_PAYLOAD:  return "payload";
    case FP_REC_ROUTING:  return "routing";
    default:              return "unknown-record";
    }
}

const char *fp_tlv_type_name(uint8_t tlv_type) {
    switch (tlv_type) {
    case FP_TLV_LABEL:    return "label";
    case FP_TLV_PRIORITY: return "priority";
    case FP_TLV_TTL:      return "ttl";
    default:              return "unknown-tlv";
    }
}

size_t fp_hex_encode(const uint8_t *data, size_t len, char *out, size_t out_cap) {
    static const char hex[] = "0123456789abcdef";
    size_t written = len * 2;
    if (out_cap == 0) {
        return written;
    }

    size_t pos = 0;
    for (size_t i = 0; i < len; i++) {
        if (pos + 1 < out_cap) {
            out[pos] = hex[data[i] >> 4];
            out[pos + 1] = hex[data[i] & 0x0f];
        }
        pos += 2;
    }

    out[(pos < out_cap) ? pos : (out_cap - 1)] = '\0';
    return written;
}

size_t fp_render_status(fp_status status, char *out, size_t out_cap) {
    const char *text = fp_strstatus(status);
    return fp_append_text(out, out_cap, 0, text);
}

size_t fp_frame_summary(const fp_frame *frame, char *out, size_t out_cap) {
    if (frame == NULL) {
        return fp_append_text(out, out_cap, 0, "<null frame>");
    }

    size_t pos = 0;
    pos = fp_append_text(out, out_cap, pos, "records=");
    pos = fp_append_uint(out, out_cap, pos, frame->record_count);
    pos = fp_append_text(out, out_cap, pos, " metadata=");
    pos = fp_append_uint(out, out_cap, pos, frame->metadata_count);
    pos = fp_append_text(out, out_cap, pos, " priority=");
    pos = fp_append_uint(out, out_cap, pos, frame->priority);
    pos = fp_append_text(out, out_cap, pos, " ttl=");
    pos = fp_append_uint(out, out_cap, pos, frame->ttl);
    pos = fp_append_text(out, out_cap, pos, " label=");

    if (frame->label_len == 0) {
        pos = fp_append_text(out, out_cap, pos, "<empty>");
        return pos;
    }

    if (fp_label_is_printable(frame)) {
        pos = fp_append_text(out, out_cap, pos, "\"");
        for (size_t i = 0; i < frame->label_len; i++) {
            char ch[2] = { frame->label[i], '\0' };
            pos = fp_append_text(out, out_cap, pos, ch);
        }
        pos = fp_append_text(out, out_cap, pos, "\"");
        return pos;
    }

    pos = fp_append_text(out, out_cap, pos, "0x");
    char hexbuf[FP_MAX_LABEL * 2 + 1];
    fp_hex_encode((const uint8_t *)frame->label, frame->label_len, hexbuf, sizeof(hexbuf));
    pos = fp_append_text(out, out_cap, pos, hexbuf);
    return pos;
}
