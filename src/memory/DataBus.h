#ifndef DATABUS_H
#define DATABUS_H

#include "Memory.h"
#include <array>
#include <cstdint>
#include <tuple>
#include <vector>

class DataBus : public Memory {
	Rom* rom;
	VideoRam* video_ram;
	ExternalRam* external_ram;
	WorkRam* work_ram;
	ObjectAttributeMemory* object_attribute_memory;
	IORegisters* io_registers;
	HighRam* high_ram;

	std::tuple<Memory*, uint16_t> determine_device_from_address(uint16_t address);

  public:
	DataBus(Rom* rom, VideoRam* video_ram, ExternalRam* external_ram, WorkRam* work_ram,
			ObjectAttributeMemory* object_attribute_memory, IORegisters* io_registers, HighRam* high_ram)
		: rom(rom), video_ram(video_ram), external_ram(external_ram), work_ram(work_ram),
		  object_attribute_memory(object_attribute_memory), io_registers(io_registers), high_ram(high_ram) {};
	Rom* get_databus();
	void set_memory(uint16_t address, uint8_t value);
	uint8_t get_memory(uint16_t address);
	std::array<uint8_t, 3> get_instruction(uint16_t address);
};

#endif // DATABUS_H
