#include "Memory.h"
#include <iostream>

uint8_t IORegisters::get_memory(uint16_t address) {
	return this->memory[address];
};
/// @brief This shouldn't ever actually be invoked,
/// but it's part of the interface, so we'll implement it for completion's sake.
/// @param address
/// @return
std::array<uint8_t, 3> IORegisters::get_instruction(uint16_t address) {
	std::cerr << "Trying to read IORegisters as an instruction. This shouldn't happen." << std::endl;
	return std::array<uint8_t, 3>({this->memory[address], this->memory[address + 1], this->memory[address + 2]});
}
uint8_t* IORegisters::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};

void IORegisters::set_memory(uint16_t address, uint8_t value) {
	switch (address) {
	case 0x46:
		// DMA transfer
		break;
	default:
		this->memory[address] = value;
		break;
	};
};