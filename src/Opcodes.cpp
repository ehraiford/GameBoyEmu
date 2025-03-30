#include <cstdint>
#include <functional>
#include <array>
#include "Cpu.h"
#include "Opcodes.h"
#include <iostream>

void OpCode::execute(Cpu *cpu, void *args)
{
    (cpu->*op_func)(args);
};
uint8_t OpCode::get_length()
{
    return this->bytes;
};
uint8_t OpCode::get_cycles()
{
    return this->cycles;
}