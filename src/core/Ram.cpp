#include "Ram.h"
#include <iostream>

Ram::~Ram() {};
Ram::Ram() {};

uint8_t Ram::get_memory(uint16_t address) {
  this->mtx.lock();
  uint8_t value = this->memory[address];
  this->mtx.unlock();
  return value;
};
std::array<uint8_t, 3> Ram::get_instruction(uint16_t address) {
  this->mtx.lock();
  std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
  this->mtx.unlock();
  return bytes;
}
void Ram::set_memory(uint16_t address, uint8_t value) {
  this->mtx.lock();
  this->memory[address] = value;
  this->mtx.unlock();
};