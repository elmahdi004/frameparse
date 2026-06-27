# ClusterFuzzLite build image.
#
# Uses the standard OSS-Fuzz/ClusterFuzzLite base builder, which provides the
# clang toolchain, sanitizer runtimes, and the $CXX / $CXXFLAGS /
# $LIB_FUZZING_ENGINE / $OUT / $SRC environment variables that build.sh relies on.
FROM gcr.io/oss-fuzz-base/base-builder:latest

# Copy the whole repository into the image.
COPY . $SRC/frameparse
WORKDIR $SRC/frameparse

# ClusterFuzzLite runs $SRC/build.sh; point it at ours.
COPY .clusterfuzzlite/build.sh $SRC/build.sh
