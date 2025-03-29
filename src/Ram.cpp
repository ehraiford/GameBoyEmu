#include "Ram.h"
#include <iostream>

Ram::~Ram() {};
Ram::Ram() {};

uint8_t Ram::get_memory(uint16_t address)
{
    return this->memory[address];
};
std::array<uint8_t, 3> Ram::get_instruction(uint16_t address)
{
    return {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
}
void Ram::set_memory(uint16_t address, uint8_t value)
{
    this->memory[address] = value;
};
uint8_t *Ram::get_mem_pointer(uint16_t address)
{
    return &this->memory[address];
};