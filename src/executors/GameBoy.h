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
	Rom rom;
	VideoRam video_ram;
	ExternalRam external_ram;
	WorkRam work_ram;
	ObjectAttributeMemory object_attribute_memory;
	IORegisters io_registers;
	HighRam high_ram;
	DataBus data_bus;
	Cpu cpu;
	std::queue<GameBoyEvent> unprocessed_events;

	void process_new_events();

  public:
	void tick_machine_cycle();
	GameBoy()
		: data_bus(&rom, &video_ram, &external_ram, &work_ram, &object_attribute_memory, &io_registers, &high_ram),
		  rom(), video_ram(), external_ram(), work_ram(), object_attribute_memory(), io_registers(), high_ram(),
		  cpu(&data_bus) {};

	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	void queue_event(GameBoyEvent event);
	DataBus* get_databus();
};
