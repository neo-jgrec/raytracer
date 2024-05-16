#!/bin/bash

SCRIPT_LOCATION="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
OUTPUT_DIR="$SCRIPT_LOCATION/build/bin"
BUILD_MODE="Release"

if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi
if [ "$#" -eq 1 ] && [ "$1" = "-d" ]; then
    echo "-- DEBUG MODE"
    BUILD_MODE="Debug"
fi

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_MODE" -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$OUTPUT_DIR" -DCMAKE_LIBRARY_OUTPUT_DIRECTORY="$OUTPUT_DIR/lib"
cmake --build build -j
