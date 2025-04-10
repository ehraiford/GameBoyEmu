#include "Opcodes.h"
#include "../executors/Cpu.h"
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>

uint8_t OpCode::get_length() {
	return this->bytes;
};
uint8_t OpCode::get_cycles() {
	return this->cycles;
}
void OpCode::execute(Cpu* cpu) {
	
}