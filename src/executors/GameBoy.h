#include "../memory/DataBus.h"
#include "../memory/Memory.h"
#include "Cpu.h"
#include <queue>

enum GameBoyEvent {
	OamDmaTransfer,
	Stop,
	Halt,
};
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
	std::queue<GameBoyEvent> unprocessed_events;

	void tick();
	void process_new_events();

  public:
	GameBoy()
		: cpu(&data_bus),
		  data_bus(&rom, &video_ram, &external_ram, &work_ram, &object_attribute_memory, &io_registers, &high_ram),
		  rom(), video_ram(), external_ram(), work_ram(), object_attribute_memory(), io_registers(), high_ram() {};

	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	void queue_event(GameBoyEvent event);
	DataBus* get_databus();
};
