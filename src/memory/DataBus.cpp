#include "DataBus.h"
#include "../executors/Ppu.h"
#include "Memory.h"
#include <iostream>

/// @brief This method is for random runtime accesses. It uses the devices' reported ranges to
/// Any access whose address is known at compile time, (like DMA or checking an IO register),
/// should use a separate dedicated function.
/// @param address
/// @param value
void DataBus::set_memory(uint16_t address, uint8_t value) {
	auto device = this->determine_device_from_address(address);
	device->set_memory(address, value);
};

/// @brief This method is for random runtime accesses. It uses the devices' reported ranges to
/// Any access whose address is known at compile time, (like DMA or checking an IO register),
/// should use a separate dedicated function.
/// @param address
uint8_t DataBus::get_memory(uint16_t address) {
	auto device = this->determine_device_from_address(address);
	return device->get_memory(address);
}

Memory* DataBus::determine_device_from_address(uint16_t address) {
	switch (address) {
	case 0x0000 ... 0x7FFF:
		return this->rom;
	case 0x8000 ... 0x9FFF:
		return this->video_ram;
	case 0xA000 ... 0xBFFF:
		return this->external_ram;
	case 0xC000 ... 0xFDFF:
		return this->work_ram;
	case 0xFE00 ... 0xFE9F:
		return this->object_attribute_memory;
	case 0xFEA0 ... 0xFEFF:
		// Need to figure out what to do with prohibited memory
		return nullptr;
	case 0xFF00 ... 0xFF7F:
		return this->io_registers;
	case 0xFF80 ... 0xFFFE:
		return this->high_ram;
	case 0xFFFF:
		return this->io_registers;
	}
};
Rom* DataBus::get_rom() {
	return this->rom;
}

std::array<uint8_t, 0xA0> DataBus::get_dma_oam_data(uint16_t starting_address) {

};