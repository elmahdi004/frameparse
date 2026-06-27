/*
 * frameparse - internal helpers (not part of the public API).
 *
 * A bounded reader cursor and a TLV extractor.  Everything here performs
 * explicit bounds checks so that the rest of the parser can read fields
 * without touching memory outside the input buffer.
 */
#ifndef FRAMEPARSE_INTERNAL_H
#define FRAMEPARSE_INTERNAL_H

#include <stddef.h>
#include <stdint.h>

#include "frameparse.h"

/* A read cursor over an immutable byte range [data, data+len). */
typedef struct {
    const uint8_t *data;
    size_t         len;
    size_t         pos;
} fp_reader;

/* One decoded TLV: type, declared length, and a pointer into the input. */
typedef struct {
    uint8_t        type;
    uint8_t        len;
    const uint8_t *value; /* points into the reader's buffer, `len` bytes */
} fp_tlv;

void   fp_reader_init(fp_reader *r, const uint8_t *data, size_t len);
size_t fp_remaining(const fp_reader *r);

/* Fixed-width reads. Return 1 on success, 0 if not enough bytes remain. */
int fp_read_u8(fp_reader *r, uint8_t *out);
int fp_read_u16be(fp_reader *r, uint16_t *out);

/* Return a pointer to the next `n` bytes and advance, or NULL if short. */
const uint8_t *fp_read_bytes(fp_reader *r, size_t n);

/*
 * Read the next TLV from `r`.
 * Returns  1  a TLV was decoded into `out`,
 *          0  the reader is exhausted (clean end),
 *         -1  the framing is malformed (truncated TLV).
 */
int fp_tlv_next(fp_reader *r, fp_tlv *out);

/* Parse a single record payload into `frame` (declared in record.cpp). */
fp_status fp_parse_record(uint8_t rec_type, const uint8_t *payload,
                          size_t payload_len, fp_frame *frame);

#endif /* FRAMEPARSE_INTERNAL_H */
