// TODO: All of these are currently stubbed out just to appease the linker.
// TODO: They will be implemented more properly in due time.

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
uint8_t* Rom::get_memory_ptr(uint16_t address) {
	return &this->bank_0[address];
};
void Rom::set_memory(uint16_t address, uint8_t value) {
	this->bank_0[address] = value;
};

void Rom::load_data(const std::vector<uint8_t>& data) {
	for (size_t i = 0; i < data.size(); ++i) {
		this->set_memory(i, data[i]);
	}
};

uint8_t VideoRam::get_memory(uint16_t address) {
	return this->memory[address];
};
std::array<uint8_t, 3> VideoRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
};
uint8_t* VideoRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
void VideoRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t ExternalRam::get_memory(uint16_t address) {
	return this->memory[address];
};
std::array<uint8_t, 3> ExternalRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
uint8_t* ExternalRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
void ExternalRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t WorkRam::get_memory(uint16_t address) {
	return this->bank_0[address];
};
uint8_t* WorkRam::get_memory_ptr(uint16_t address) {
	return &this->bank_0[address];
};
std::array<uint8_t, 3> WorkRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->bank_0[address], this->bank_0[address + 1], this->bank_0[address + 2]};
	return bytes;
}
void WorkRam::set_memory(uint16_t address, uint8_t value) {
	this->bank_0[address] = value;
};

uint8_t ObjectAttributeMemory::get_memory(uint16_t address) {
	return this->memory[address];
};
uint8_t* ObjectAttributeMemory::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
std::array<uint8_t, 3> ObjectAttributeMemory::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
void ObjectAttributeMemory::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t HighRam::get_memory(uint16_t address) {
	return this->memory[address];
};
uint8_t* HighRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
std::array<uint8_t, 3> HighRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
void HighRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};
