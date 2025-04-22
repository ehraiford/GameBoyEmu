#include "../memory/Cartridge.h"
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
	Cartridge cartridge;
	VideoRam video_ram;
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
		: data_bus(cartridge.get_rom(), &video_ram, cartridge.get_external_ram(), &work_ram, &object_attribute_memory,
				   &io_registers, &high_ram),
		  cartridge(), video_ram(), work_ram(), object_attribute_memory(), io_registers(), high_ram(), cpu(&data_bus),
		  ppu(&video_ram, &object_attribute_memory) {};

	void tick_machine_cycle();
	void run_bootrom();
	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	void queue_event(GameBoyEvent event);
	DataBus* get_databus();
};
