/*
 * frameparse - libFuzzer entry point.
 *
 * Each fuzzer iteration feeds the raw input straight into the real parser.
 * We allocate the frame on the heap and free it every time so that
 * AddressSanitizer can attribute any out-of-bounds access precisely and so
 * that leaks are visible.
 */
#include <cstddef>
#include <cstdint>

#include "frameparse.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    fp_frame frame;
    if (fp_frame_init(&frame) != FP_OK) {
        return 0;
    }

    /* Exercise the full multi-stage parser. Return value is intentionally
     * ignored: we care about crashes / sanitizer reports, not the verdict. */
    fp_parse(data, size, &frame);

    fp_frame_free(&frame);
    return 0;
}
