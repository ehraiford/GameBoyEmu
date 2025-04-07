#ifndef DATABUS_H
#define DATABUS_H

#include "Memory.h"
#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

class DataBus {
	Rom* rom;
	VideoRam* video_ram;
	ExternalRam* external_ram;
	WorkRam* work_ram;
	ObjectAttributeMemory* object_attribute_memory;
	IORegisters* io_registers;
	HighRam* high_ram;

	Memory* determine_device_from_address(uint16_t address);

  public:
	Rom* get_rom();
	void set_memory(uint16_t address, uint8_t value);
	uint8_t get_memory(uint16_t address);
	std::array<uint8_t, 0xA0> get_dma_oam_data(uint16_t starting_address);
};

#endif // DATABUS_H
