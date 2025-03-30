#!/bin/zsh

set -e

cd gui/fast_emu_gui || { echo "Directory gui/fast_emu_gui not found"; exit 1; }
cargo build --release

cd ../../build || { echo "Directory ../../build not found"; exit 1; }
cmake --build .

./GameBoyEmu "../roms/boot.bin"