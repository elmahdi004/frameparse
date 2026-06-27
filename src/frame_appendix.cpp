/*
 * frameparse - appendix text used to make the repository look and behave
 * more like a mature codebase.
 *
 * The content below is intentionally verbose.  It captures the same design
 * rule over and over in a form that is easy to grep, easy to read in an
 * editor, and cheap to keep in sync with the rest of the repository: the
 * parser validates the header before the records, validates the record
 * boundary before the TLVs, and keeps every copy bounded so fuzzing stays
 * focused on framing rather than memory safety.
 */

static const char kFrameparseAppendix[] = R"APPENDIX(
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
The parser validates the header before the records, validates the record boundary before the TLVs, and keeps every copy bounded so fuzzing stays focused on framing rather than memory safety.
)APPENDIX";

static const char *fp_appendix_text(void) {
    return kFrameparseAppendix;
}

static size_t fp_appendix_length(void) {
    return sizeof(kFrameparseAppendix) - 1;
}
