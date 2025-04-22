#include "DataBus.h"
#include "../executors/Ppu.h"
#include "Memory.h"
#include <iostream>

void DataBus::set_memory(uint16_t address, uint8_t value) {
	auto [device, offset] = this->determine_device_from_address(address);
	device->set_memory(address - offset, value);
};

uint8_t DataBus::get_memory(uint16_t address) {
	auto [device, offset] = this->determine_device_from_address(address);
	return device->get_memory(address - offset);
}

std::array<uint8_t, 3> DataBus::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> instruction = {0, 0, 0};
	instruction[0] = this->get_memory(address);
	instruction[1] = this->get_memory(address + 1);
	instruction[2] = this->get_memory(address + 2);
	return instruction;
}
uint8_t* DataBus::get_memory_ptr(uint16_t address) {
	auto [device, offset] = this->determine_device_from_address(address);
	return device->get_memory_ptr(address - offset);
};

std::tuple<Memory*, uint16_t> DataBus::determine_device_from_address(uint16_t address) {
	switch (address) {
	case 0x0000 ... 0x7FFF:
		return std::make_tuple(this->rom, 0);
	case 0x8000 ... 0x9FFF:
		// std::cout << "Accessing address: 0x" << std::hex << address << std::endl;
		return std::make_tuple(this->video_ram, 0x8000);
	case 0xA000 ... 0xBFFF:
		return std::make_tuple(this->external_ram, 0xA000);
	case 0xC000 ... 0xFDFF:
		return std::make_tuple(this->work_ram, 0xC000);
	case 0xFE00 ... 0xFE9F:
		return std::make_tuple(this->object_attribute_memory, 0xFE00);
	case 0xFEA0 ... 0xFEFF:
		// TODO: Figure out what to do with prohibited memory
		return std::make_tuple(nullptr, 0);
	case 0xFF00 ... 0xFF7F:
		return std::make_tuple(this->io_registers, 0xFF00);
	case 0xFF80 ... 0xFFFE:
		return std::make_tuple(this->high_ram, 0xFF80);
	case 0xFFFF:
		return std::make_tuple(this->io_registers, 0xFFFF);
	}
};
Rom* DataBus::get_databus() {
	return this->rom;
}
