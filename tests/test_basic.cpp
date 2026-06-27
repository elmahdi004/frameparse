/*
 * frameparse - basic sanity tests on valid and invalid inputs.
 *
 * These run WITHOUT sanitizers/fuzzing and just confirm the parser behaves
 * on well-formed data and rejects malformed framing.  Build by compiling the
 * library sources under src/ together with this file, then run the binary.
 */
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#include "frameparse.h"

/* Helpers to assemble a frame by hand. */
static void put_u16be(std::vector<uint8_t> &v, uint16_t x) {
    v.push_back((uint8_t)(x >> 8));
    v.push_back((uint8_t)(x & 0xff));
}

static std::vector<uint8_t> make_header(uint16_t record_count) {
    std::vector<uint8_t> v = {'F', 'R', 'M', 'P', FP_VERSION, 0x00};
    put_u16be(v, record_count); /* record_count */
    put_u16be(v, 0);            /* reserved     */
    return v;
}

static int failures = 0;
#define CHECK(cond)                                                      \
    do {                                                                 \
        if (!(cond)) {                                                   \
            printf("FAIL %s:%d  %s\n", __FILE__, __LINE__, #cond);       \
            failures++;                                                  \
        }                                                                \
    } while (0)

static void test_empty_frame() {
    std::vector<uint8_t> v = make_header(0);
    fp_frame f;
    fp_frame_init(&f);
    CHECK(fp_parse(v.data(), v.size(), &f) == FP_OK);
    CHECK(f.record_count == 0);
    CHECK(f.metadata_count == 0);
    fp_frame_free(&f);
}

static void test_metadata_label() {
    const char *label = "edge-router-01";
    uint8_t llen = (uint8_t)strlen(label);

    /* One METADATA record: LABEL + PRIORITY + TTL. */
    std::vector<uint8_t> payload;
    payload.push_back(FP_TLV_LABEL);
    payload.push_back(llen);
    payload.insert(payload.end(), label, label + llen);
    payload.push_back(FP_TLV_PRIORITY);
    payload.push_back(1);
    payload.push_back(7);
    payload.push_back(FP_TLV_TTL);
    payload.push_back(1);
    payload.push_back(64);

    std::vector<uint8_t> v = make_header(1);
    v.push_back(FP_REC_METADATA);
    put_u16be(v, (uint16_t)payload.size());
    v.insert(v.end(), payload.begin(), payload.end());

    fp_frame f;
    fp_frame_init(&f);
    CHECK(fp_parse(v.data(), v.size(), &f) == FP_OK);
    CHECK(f.metadata_count == 1);
    CHECK(f.priority == 7);
    CHECK(f.ttl == 64);
    CHECK(f.label_len == llen);
    CHECK(memcmp(f.label, label, llen) == 0);
    fp_frame_free(&f);
}

static void test_bad_magic() {
    std::vector<uint8_t> v = make_header(0);
    v[0] = 'X';
    fp_frame f;
    fp_frame_init(&f);
    CHECK(fp_parse(v.data(), v.size(), &f) == FP_ERR_MAGIC);
    fp_frame_free(&f);
}

static void test_truncated_record() {
    std::vector<uint8_t> v = make_header(1);
    v.push_back(FP_REC_METADATA);
    put_u16be(v, 50); /* claims 50 bytes of payload that are not there */
    fp_frame f;
    fp_frame_init(&f);
    CHECK(fp_parse(v.data(), v.size(), &f) == FP_ERR_RECORD);
    fp_frame_free(&f);
}

int main() {
    test_empty_frame();
    test_metadata_label();
    test_bad_magic();
    test_truncated_record();

    if (failures == 0) {
        printf("all tests passed\n");
        return 0;
    }
    printf("%d test(s) failed\n", failures);
    return 1;
}
