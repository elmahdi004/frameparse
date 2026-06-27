#!/bin/bash -eu
#
# ClusterFuzzLite build script.
#
# Invoked with the repository as the working directory and these variables
# provided by the build environment:
#   $CXX                 C++ compiler (clang++)
#   $CXXFLAGS            compiler flags (include sanitizer + coverage flags)
#   $LIB_FUZZING_ENGINE  link flags for the fuzzing engine (libFuzzer)
#   $OUT                 directory where built fuzz targets must be placed
#
# It compiles every library translation unit plus the harness into a single
# fuzz target: $OUT/parser_fuzzer.

mkdir -p "$OUT"

# Compile each library source under src/ into an object file.
objs=()
for src in src/*.cpp; do
    obj="$(basename "${src%.cpp}").o"
    $CXX $CXXFLAGS -I include -c "$src" -o "$obj"
    objs+=("$obj")
done

# Link the harness with the library objects and the fuzzing engine.
$CXX $CXXFLAGS -I include \
    fuzz/parser_fuzzer.cc "${objs[@]}" \
    $LIB_FUZZING_ENGINE \
    -o "$OUT/parser_fuzzer"

# Ship the seed corpus alongside the target (ClusterFuzzLite picks this up).
if [ -d fuzz/corpus/parser_fuzzer ]; then
    (cd fuzz/corpus/parser_fuzzer && zip -qr "$OUT/parser_fuzzer_seed_corpus.zip" .)
fi
