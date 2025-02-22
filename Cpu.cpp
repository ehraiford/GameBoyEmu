#include "Cpu.h"

Cpu::Cpu(const std::string& name, uint16_t ram_id, uint32_t starting_instruction_pointer) {
    this->program_counter = 0;
    this->instruction_pointer = starting_instruction_pointer;
    this->name = name;
    this->ram_id = ram_id;
}

void Cpu::tick() {
    // Implementation of tick logic
}
