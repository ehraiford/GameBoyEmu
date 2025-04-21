#include "../memory/DataBus.h"
#include "../memory/Memory.h"
#include "Cpu.h"
#include "Ppu.h"
#include <queue>

enum GameBoyEvent {
	OamDmaTransfer,
	Stop,
	Halt,
};
class GameBoy {
	Cartridge rom;
	VideoRam video_ram;
	ExternalRam external_ram;
	WorkRam work_ram;
	ObjectAttributeMemory object_attribute_memory;
	IORegisters io_registers;
	HighRam high_ram;
	DataBus data_bus;
	Cpu cpu;
	Ppu ppu;
	std::queue<GameBoyEvent> unprocessed_events;

	void process_new_events();

  public:
	GameBoy()
		: data_bus(&rom, &video_ram, &external_ram, &work_ram, &object_attribute_memory, &io_registers, &high_ram),
		  rom(), video_ram(), external_ram(), work_ram(), object_attribute_memory(), io_registers(), high_ram(),
		  cpu(&data_bus), ppu(&video_ram, &object_attribute_memory) {};

	void tick_machine_cycle();
	void run_bootrom();
	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	void queue_event(GameBoyEvent event);
	DataBus* get_databus();
};
