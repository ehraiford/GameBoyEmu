#include "GameBoy.h"
#include "../memory/Memory.h"
#include "Cpu.h"

void GameBoy::load_buffer_as_cartridge(std::vector<uint8_t> buffer) {
	this->rom.load_data(buffer);
	this->cpu.point_pc_at_start_of_memory();
}
DataBus* GameBoy::get_databus() {
	return &this->data_bus;
}
void GameBoy::queue_event(GameBoyEvent event) {
	this->unprocessed_events.push(event);
}

void GameBoy::process_new_events() {
	while (!this->unprocessed_events.empty()) {
		GameBoyEvent event = this->unprocessed_events.front();
		this->unprocessed_events.pop();
		switch (event) {
		case OamDmaTransfer:
			// Handle OAM DMA transfer
			break;
		case Stop:
			// Handle Stop Event
			break;
		case Halt:
			// Handle Halt Event
			break;
		default:
			std::cout << "An Unknown Event made it to the CPU" << std::endl;
			break;
		}
	}
}

void GameBoy::tick_machine_cycle() {
	this->process_new_events();
	this->cpu.tick_machine_cycle();
	this->ppu.temp_track_tiles();
}