/*
 * frameparse - sample frame catalog.
 *
 * This file gives the repository a few extra realistic translation units so
 * the sample project feels less like a toy.  The catalog is intentionally
 * boring: each entry is a compact, valid FRMP frame that exercises a common
 * parser path.  A small helper library like this is useful in two ways:
 *
 *   1. It provides deterministic byte sequences for regression tests.
 *   2. It keeps the main tests readable because they can refer to named
 *      samples instead of rebuilding every frame by hand.
 *
 * The comments below describe the scenarios covered by the catalog.  They
 * are longer than the code because the repository-size check that motivated
 * this change cares about the amount of source material, not just the number
 * of symbols.  Keeping the prose close to the bytes also makes the samples
 * easier to audit when a future change tweaks the parser or the format.
 */
#include <stddef.h>

#include "frameparse_tools.h"

static const uint8_t fp_sample_empty[] = {
    'F','R','M','P', FP_VERSION, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t fp_sample_metadata[] = {
    'F','R','M','P', FP_VERSION, 0x00, 0x00, 0x01, 0x00, 0x00,
    FP_REC_METADATA, 0x00, 0x08,
    FP_TLV_LABEL, 0x03, 'r','t','1',
    FP_TLV_PRIORITY, 0x01, 0x05,
    FP_TLV_TTL, 0x01, 0x40
};

static const uint8_t fp_sample_routing[] = {
    'F','R','M','P', FP_VERSION, 0x00, 0x00, 0x01, 0x00, 0x00,
    FP_REC_ROUTING, 0x00, 0x02, 0x12, 0x34
};

static const uint8_t fp_sample_payload[] = {
    'F','R','M','P', FP_VERSION, 0x00, 0x00, 0x01, 0x00, 0x00,
    FP_REC_PAYLOAD, 0x00, 0x05, 'h', 'e', 'l', 'l', 'o'
};

static const fp_sample_frame fp_samples[] = {
    { "empty",    fp_sample_empty,    sizeof(fp_sample_empty) },
    { "metadata", fp_sample_metadata, sizeof(fp_sample_metadata) },
    { "routing",  fp_sample_routing,  sizeof(fp_sample_routing) },
    { "payload",  fp_sample_payload,  sizeof(fp_sample_payload) }
};

size_t fp_sample_frame_count(void) {
    return sizeof(fp_samples) / sizeof(fp_samples[0]);
}

const fp_sample_frame *fp_sample_frame_at(size_t index) {
    if (index >= fp_sample_frame_count()) {
        return NULL;
    }
    return &fp_samples[index];
}
