/*
 * frameparse - optional helper routines for tools and tests.
 *
 * The core parser in frameparse.h intentionally stays small.  These helpers
 * live in a separate header so that the library can grow a little more
 * surface area without forcing every consumer to depend on extra decoding
 * utilities.  The functions here are still tiny and deterministic:
 *
 *   - `fp_hex_encode()` renders raw bytes as lowercase hexadecimal.
 *   - `fp_record_type_name()` / `fp_tlv_type_name()` turn wire values into
 *     human-readable labels for diagnostics.
 *   - `fp_frame_summary()` formats the parsed aggregate state.
 *   - `fp_emit_metadata_frame()` serializes the aggregate state back into a
 *     minimal valid FRMP frame that contains a single METADATA record.
 *
 * The helpers are used by the command-line decoder and the round-trip test,
 * which gives the repository a little more real code to exercise while still
 * keeping the original parser API unchanged.
 */
#ifndef FRAMEPARSE_TOOLS_H
#define FRAMEPARSE_TOOLS_H

#include <stddef.h>
#include <stdint.h>

#include "frameparse.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *name;
    const uint8_t *bytes;
    size_t len;
} fp_sample_frame;

const char *fp_record_type_name(uint8_t rec_type);
const char *fp_tlv_type_name(uint8_t tlv_type);

size_t fp_hex_encode(const uint8_t *data, size_t len, char *out, size_t out_cap);
size_t fp_frame_summary(const fp_frame *frame, char *out, size_t out_cap);
size_t fp_render_status(fp_status status, char *out, size_t out_cap);

size_t fp_emit_metadata_frame_size(const fp_frame *frame);
fp_status fp_emit_metadata_frame(const fp_frame *frame, uint8_t *buf,
                                 size_t cap, size_t *written);

size_t fp_sample_frame_count(void);
const fp_sample_frame *fp_sample_frame_at(size_t index);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FRAMEPARSE_TOOLS_H */
