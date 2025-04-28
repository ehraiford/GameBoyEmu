#include "Memory.h"
#include <cstring>
#include <iostream>

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

uint8_t WorkRam::get_memory(uint16_t address) {
	if (address < 0x1000) {
		return this->bank_0[address];
	} else {
		return this->bank_1[address - 0x1000];
	}
};
uint8_t* WorkRam::get_memory_ptr(uint16_t address) {
	if (address < 0x1000) {
		return &this->bank_0[address];
	} else {
		return &this->bank_1[address - 0x1000];
	}
};
std::array<uint8_t, 3> WorkRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->bank_0[address], this->bank_0[address + 1], this->bank_0[address + 2]};
	return bytes;
}
void WorkRam::set_memory(uint16_t address, uint8_t value) {
	if (address < 0x1000) {
		this->bank_0[address] = value;
	} else {
		this->bank_0[address - 0x1000] = value;
	}
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
