#include <iostream>
#include "Cpu.h"
#include "Ram.h"
#include "Opcodes.cpp"

int main() {
    Cpu cpu = Cpu();
    Ram ram = Ram();
    auto entry = jump_table[0];
    uint16_t arg = 0;
    entry.get_arguments(&cpu, &arg);
    entry.op_code->execute(&cpu, nullptr);
    return 0;
};
