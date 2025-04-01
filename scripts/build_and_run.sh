#!/bin/zsh

set -e

cd ../gui/fast_emu_gui || { echo "Directory gui/fast_emu_gui not found"; exit 1; }
cargo build --release

mkdir -p ../../build 
cd ../../build 
cmake --build .

./GameBoyEmu "../roms/dmg_boot.bin"