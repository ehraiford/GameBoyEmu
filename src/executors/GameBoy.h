#include "../memory/DataBus.h"
#include "../memory/Memory.h"
#include "Cpu.h"
class GameBoy {
	Cpu cpu;
	DataBus data_bus;
	Rom rom;
	VideoRam video_ram;
	ExternalRam external_ram;
	WorkRam work_ram;
	ObjectAttributeMemory object_attribute_memory;
	IORegisters io_registers;
	HighRam high_ram;

	void tick();

  public:
	GameBoy()
		: cpu(),
		  data_bus(&rom, &video_ram, &external_ram, &work_ram, &object_attribute_memory, &io_registers, &high_ram),
		  rom(), video_ram(), external_ram(), work_ram(), object_attribute_memory(), io_registers(), high_ram() {};

	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	DataBus* get_databus();
};

enum EmulatorState {
	STOPPED,
	RUNNING,
	PAUSED,
	RESET,
};