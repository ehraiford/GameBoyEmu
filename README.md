#GameBoyEmu

The plan is for this to eventually be a cycle accurate emulator of Nintendo's GameBoy.

The goal for this emulator was to help me get better at C++ as my emulation experience has primarily been in Rust. 

Currently, it should work as a disassembler for a rom you provide it in the CLI. Ive tested it with a basic bootrom. 
Opcodes have been implemented and will rely on the same lifting mechanism as the disassembler. The current step is mapping the lifted instruction and arguments to the proper CPU method. 
after that will be the PPU and then IO devices. 

This is just a nights and weekends project and is being developed alongside a reusable development GUI written in Rust so progress on it will be slow.
