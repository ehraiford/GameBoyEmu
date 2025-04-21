#GameBoyEmu

The plan is for this to eventually be an accurate emulator of Nintendo's GameBoy.

The goal for this emulator was to help me get better at C++ as my emulation experience has primarily been in Rust. 

Currently, it should execute and disassemble instructions for a rom you provide it in the CLI. I've tested it with a basic bootrom. 

To run it, you can run `build_and_run.sh` from the scripts directory. It is currently hardcoded to search for `dmg_boot.bin` in the roms director which you'll have to supply yourself. If you are running this from VS Code, there's a convenient task that can run this for you.

With the CPU finally running swimmingly (as far as can be told, currently), the next goal is the PPU.

This is just a nights and weekends project and is being developed alongside a reusable development GUI written in Rust so progress on it will be slow.
