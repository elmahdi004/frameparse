/*
 * framedump - tiny CLI that decodes a .frmp file and prints a summary.
 *
 *   framedump <file>
 *
 * Exits 0 if the frame parsed cleanly, 1 on a parse error, 2 on usage error.
 */
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "frameparse.h"
#include "frameparse_tools.h"

static std::vector<uint8_t> read_file(const char *path, bool *ok) {
    std::vector<uint8_t> bytes;
    FILE *f = fopen(path, "rb");
    if (f == nullptr) {
        *ok = false;
        return bytes;
    }
    uint8_t buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        bytes.insert(bytes.end(), buf, buf + n);
    }
    fclose(f);
    *ok = true;
    return bytes;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file.frmp>\n", argv[0]);
        return 2;
    }

    bool ok = false;
    std::vector<uint8_t> bytes = read_file(argv[1], &ok);
    if (!ok) {
        fprintf(stderr, "error: cannot read '%s'\n", argv[1]);
        return 2;
    }

    fp_frame frame;
    if (fp_frame_init(&frame) != FP_OK) {
        fprintf(stderr, "error: out of memory\n");
        return 2;
    }

    fp_status st = fp_parse(bytes.data(), bytes.size(), &frame);
    char status_buf[64];
    char summary_buf[256];
    fp_render_status(st, status_buf, sizeof(status_buf));
    printf("status        : %s\n", status_buf);
    if (st == FP_OK) {
        fp_frame_summary(&frame, summary_buf, sizeof(summary_buf));
        printf("summary       : %s\n", summary_buf);
        printf("records       : %u\n", frame.record_count);
        printf("metadata recs : %u\n", frame.metadata_count);
        printf("priority      : %u\n", frame.priority);
        printf("ttl           : %u\n", frame.ttl);
        printf("label (%zu B)  : %.*s\n",
               frame.label_len, (int)frame.label_len, frame.label);
    }

    fp_frame_free(&frame);
    return (st == FP_OK) ? 0 : 1;
}
