#ifndef CPU_H
#define CPU_H

#include "Device.h"

class Cpu : public Device {
    uint32_t program_counter;
    uint32_t instruction_pointer;
    uint16_t ram_id;

public:
    Cpu(const std::string& name, uint16_t ram_id, uint32_t starting_instruction_pointer);
    void tick() override;
};

#endif // CPU_H
