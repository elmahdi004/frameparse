/*
 * frameparse - a small binary "FRMP" container parser.
 *
 * Public API.  The library decodes a compact framing format used as a
 * teaching target for fuzzing.  It is deliberately small but multi-stage:
 *
 *   Header (10 bytes)
 *     "FRMP"            4 bytes  magic
 *     version           1 byte   must equal FP_VERSION
 *     flags             1 byte   reserved bit flags (ignored for now)
 *     record_count      2 bytes  big-endian
 *     reserved          2 bytes  big-endian, must be 0
 *
 *   record_count records, each:
 *     rec_type          1 byte
 *     rec_len           2 bytes  big-endian, payload length
 *     payload           rec_len bytes
 *
 *   A METADATA record's payload is a sequence of TLV options:
 *     tlv_type          1 byte
 *     tlv_len           1 byte
 *     value             tlv_len bytes
 *
 * See README.md for the full specification.
 */
#ifndef FRAMEPARSE_H
#define FRAMEPARSE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Wire constants. */
#define FP_MAGIC "FRMP"
#define FP_MAGIC_LEN 4
#define FP_HEADER_LEN 10
#define FP_VERSION 1

/* Maximum number of bytes we keep for an accumulated label. */
#define FP_MAX_LABEL 64

/* Record types. */
enum fp_record_type {
    FP_REC_METADATA = 0x01,
    FP_REC_PAYLOAD  = 0x02,
    FP_REC_ROUTING  = 0x03
};

/* TLV option types found inside a METADATA record. */
enum fp_tlv_type {
    FP_TLV_LABEL    = 0x01,
    FP_TLV_PRIORITY = 0x02,
    FP_TLV_TTL      = 0x03
};

/* Status codes returned by the parser. */
typedef enum {
    FP_OK = 0,
    FP_ERR_SHORT,    /* ran out of bytes while reading a fixed field */
    FP_ERR_MAGIC,    /* bad magic                                    */
    FP_ERR_VERSION,  /* unsupported version                          */
    FP_ERR_RESERVED, /* reserved field not zero                      */
    FP_ERR_RECORD,   /* malformed record framing                     */
    FP_ERR_TLV,      /* malformed TLV framing                        */
    FP_ERR_NOMEM     /* allocation failed                            */
} fp_status;

/*
 * Decoded view of a frame.  `label` is a heap buffer of FP_MAX_LABEL bytes
 * that accumulates the LABEL TLVs of the metadata records.
 */
typedef struct {
    char    *label;          /* heap buffer, capacity FP_MAX_LABEL */
    size_t   label_len;      /* bytes currently stored in label    */
    uint8_t  priority;       /* last PRIORITY TLV seen             */
    uint8_t  ttl;            /* last TTL TLV seen                  */
    uint16_t record_count;   /* records declared in the header     */
    uint16_t metadata_count; /* METADATA records actually parsed   */
} fp_frame;

/* Initialise a frame (allocates the label buffer). Returns FP_OK or FP_ERR_NOMEM. */
fp_status fp_frame_init(fp_frame *frame);

/* Release any memory owned by a frame. Safe to call on a zeroed frame. */
void fp_frame_free(fp_frame *frame);

/*
 * Parse `len` bytes from `buf` into `frame` (which must already be init'd).
 * Returns FP_OK on success or an fp_status error code.
 */
fp_status fp_parse(const uint8_t *buf, size_t len, fp_frame *frame);

/* Human-readable description of a status code. */
const char *fp_strstatus(fp_status status);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FRAMEPARSE_H */
