#include <cstdint>
#include <functional>
#include "Cpu.h"

void nop(Cpu& cpu) {};
void load_16_bit(uint16_t* reg, uint16_t value) {
    *reg = value;
};

using OpcodeHandler = std::function<void(Cpu&)>;
OpcodeHandler opcode_table[256];


void inialize_opcode_map() {
    opcode_table[0x00] = &nop;
    
};
