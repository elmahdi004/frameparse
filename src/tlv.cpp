/*
 * frameparse - TLV extraction.
 *
 * A TLV is: type(1) | len(1) | value[len].  We read the two header bytes
 * and then borrow `len` bytes from the reader for the value.  The value
 * pointer is always validated against the remaining input here, so record
 * handlers can trust that `out->value` covers exactly `out->len` bytes.
 */
#include "internal.h"

int fp_tlv_next(fp_reader *r, fp_tlv *out) {
    /* Clean end: nothing left in this record's payload. */
    if (fp_remaining(r) == 0) {
        return 0;
    }

    uint8_t type;
    uint8_t len;
    if (!fp_read_u8(r, &type) || !fp_read_u8(r, &len)) {
        return -1; /* truncated TLV header */
    }

    const uint8_t *value = fp_read_bytes(r, len);
    if (value == NULL) {
        return -1; /* declared length runs past the payload */
    }

    out->type  = type;
    out->len   = len;
    out->value = value;
    return 1;
}
