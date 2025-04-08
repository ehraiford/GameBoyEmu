#!/bin/bash

cd ../gui/fast_emu_gui
cargo build --release
cd ../../tests

mkdir -p build
cd build

cmake ..

make

ctest --output-on-failure
