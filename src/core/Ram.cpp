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

void Ram::load_data(const std::vector<uint8_t> &data) {
	for (size_t i = 0; i < data.size(); ++i) {
		this->set_memory(i, data[i]);
	}
};
std::vector<std::tuple<uint16_t, uint16_t>> Ram::get_address_ranges() {
	return std::vector<std::tuple<uint16_t, uint16_t>>();
};
