/*
 * frameparse - record payload parsing.
 *
 * A METADATA record carries a sequence of TLV options.  We walk them with
 * fp_tlv_next() (which validates each value against the payload bounds) and
 * fold the recognised ones into the decoded frame:
 *
 *   LABEL    - appended to frame->label
 *   PRIORITY - first byte stored in frame->priority
 *   TTL      - first byte stored in frame->ttl
 *
 * PAYLOAD and ROUTING records only need their framing validated for this
 * version of the format, so their payloads are accepted as-is.  Unknown
 * record types and unknown TLV types are skipped (forward-compatible).
 */
#include <string.h>

#include "internal.h"

static fp_status parse_metadata(const uint8_t *payload, size_t payload_len,
                                fp_frame *frame) {
    frame->metadata_count++;

    fp_reader r;
    fp_reader_init(&r, payload, payload_len);

    fp_tlv tlv;
    int rc;
    while ((rc = fp_tlv_next(&r, &tlv)) == 1) {
        switch (tlv.type) {
        case FP_TLV_LABEL:
            /*
             * Append this label fragment to the accumulated label.
             *
             * fp_tlv_next() already guaranteed that `tlv.len` bytes are
             * present in the payload, so reading from tlv.value is safe.
             *
             * Bounds check the DESTINATION before copying: reject the frame
             * if appending this fragment would exceed the label buffer.
             * (label_len <= FP_MAX_LABEL and tlv.len <= 255, so the sum
             * cannot overflow size_t.)
             */
            if (frame->label_len + tlv.len > FP_MAX_LABEL) {
                return FP_ERR_TLV;
            }
            memcpy(frame->label + frame->label_len, tlv.value, tlv.len);
            frame->label_len += tlv.len;
            break;

        case FP_TLV_PRIORITY:
            if (tlv.len >= 1) {
                frame->priority = tlv.value[0];
            }
            break;

        case FP_TLV_TTL:
            if (tlv.len >= 1) {
                frame->ttl = tlv.value[0];
            }
            break;

        default:
            /* Unknown option: already consumed by fp_tlv_next(), skip it. */
            break;
        }
    }

    return (rc < 0) ? FP_ERR_TLV : FP_OK;
}

fp_status fp_parse_record(uint8_t rec_type, const uint8_t *payload,
                          size_t payload_len, fp_frame *frame) {
    switch (rec_type) {
    case FP_REC_METADATA:
        return parse_metadata(payload, payload_len, frame);

    case FP_REC_PAYLOAD:
    case FP_REC_ROUTING:
        /* Framing already validated by the caller; nothing else to extract. */
        (void)payload;
        (void)payload_len;
        return FP_OK;

    default:
        /* Unknown record type: skip for forward compatibility. */
        return FP_OK;
    }
}
