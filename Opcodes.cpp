#include <cstdint>
#include <functional>
#include <array>
#include "Cpu.h"

typedef void (Cpu::*OpFunc)(void*);
class OpCode {
    OpFunc op_func;
    uint8_t cycles;
public: 
    OpCode(OpFunc func, uint8_t cycles) : op_func(func), cycles(cycles) {};
    
    void execute(Cpu* cpu, void* args) {
        (cpu->*op_func)(args);
    };
};

static OpCode nop = OpCode(&Cpu::nop, 1);
static OpCode copy = OpCode(&Cpu::copy, 1);
