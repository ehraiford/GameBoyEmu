#ifndef OPCODES_H
#define OPCODES_H

#include <array>
#include "Cpu.h"

typedef void (Cpu::*OpFunc)(void *);
class OpCode
{
    OpFunc op_func;
    uint8_t cycles;
    uint8_t bytes;

public:
    OpCode(OpFunc func, uint8_t cycles, uint8_t bytes) : op_func(func), cycles(cycles), bytes(bytes) {};

    void execute(Cpu *cpu, void *args);
};

struct JumpTableEntry
{
    OpCode *op_code;
    void *(*get_arguments)(Cpu *, uint8_t *);
};

extern std::array<JumpTableEntry, 256> jump_table;
extern std::array<JumpTableEntry, 256> jump_table_cb;

#endif // OPCODES_H
