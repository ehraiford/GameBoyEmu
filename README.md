#GameBoyEmu

The plan is for this to eventually be a cycle accurate emulator of Nintendo's GameBoy.

The goal for this emulator was to help me get better at C++ as my emulation experience has primarily been in Rust. 

Currently, it should work as a disassembler for a rom you provide it in the CLI. I've tested it with a basic bootrom. 
Opcodes have been implemented and will rely on the same lifting mechanism as the disassembler. The current step is mapping the lifted instruction and arguments to the proper CPU method. 
after that will be the PPU and then IO devices. 

As I am right now fighting C++ and the JumpTable to get them to work together, the project is currently non-functional. If you checkout commit 33d24d3, it should compile there. To run it, you can run `build_and_run.sh` from the scripts directory. It is currently hardcoded to search for `dmg_boot.bin` in the roms director which you'll have to supply yourself. If you are running this from VS Code, there's a convenient task that can run this for you.

This is just a nights and weekends project and is being developed alongside a reusable development GUI written in Rust so progress on it will be slow.
