#include "Opcodes.h"
#include "../core/Cpu.h"
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>

void OpCode::execute(Cpu *cpu, void *args) {
  (cpu->*op_func)(args);
};
uint8_t OpCode::get_length() {
  return this->bytes;
};
uint8_t OpCode::get_cycles() {
  return this->cycles;
}