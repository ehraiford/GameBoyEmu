#!/bin/bash

# Build the fast_emu_gui library
cd ../gui/fast_emu_gui
cargo build --release
cd ../../tests

mkdir -p build
cd build

cmake ..

make

# ./tests_fetch_decode

# Run tests with ctest
ctest --output-on-failure
