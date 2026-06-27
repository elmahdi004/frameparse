/*
 * frameparse - bounded reader cursor.
 *
 * Every accessor checks that the requested bytes are available before
 * touching them, so callers never read past the end of the input.
 */
#include "internal.h"

void fp_reader_init(fp_reader *r, const uint8_t *data, size_t len) {
    r->data = data;
    r->len  = len;
    r->pos  = 0;
}

size_t fp_remaining(const fp_reader *r) {
    return r->len - r->pos;
}

int fp_read_u8(fp_reader *r, uint8_t *out) {
    if (fp_remaining(r) < 1) {
        return 0;
    }
    *out = r->data[r->pos];
    r->pos += 1;
    return 1;
}

int fp_read_u16be(fp_reader *r, uint16_t *out) {
    if (fp_remaining(r) < 2) {
        return 0;
    }
    *out = (uint16_t)((r->data[r->pos] << 8) | r->data[r->pos + 1]);
    r->pos += 2;
    return 1;
}

const uint8_t *fp_read_bytes(fp_reader *r, size_t n) {
    if (fp_remaining(r) < n) {
        return NULL;
    }
    const uint8_t *p = r->data + r->pos;
    r->pos += n;
    return p;
}
