#!/bin/bash

SCRIPT_LOCATION="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

if [ ! -d "build" ]; then
    mkdir build
fi
if [ "$#" -eq 1 ] && [ "$1" = "-d" ]; then
    echo "-- DEBUG MODE"
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$SCRIPT_LOCATION/. -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$SCRIPT_LOCATION/./lib
else
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$SCRIPT_LOCATION/. -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$SCRIPT_LOCATION/./lib
fi

cmake --build build -j
