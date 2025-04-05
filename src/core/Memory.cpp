#include "Memory.h"
#include <iostream>

uint8_t Rom::get_memory(uint16_t address) {
	uint8_t value = this->bank_0[address];
	return value;
};
std::array<uint8_t, 3> Rom::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->bank_0[address], this->bank_0[address + 1], this->bank_0[address + 2]};
	return bytes;
}
void Rom::set_memory(uint16_t address, uint8_t value) {
	this->bank_0[address] = value;
};

void Rom::load_data(const std::vector<uint8_t> &data) {
	for (size_t i = 0; i < data.size(); ++i) {
		this->set_memory(i, data[i]);
	}
};