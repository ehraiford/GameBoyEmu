#include "GameBoy.h"
#include "../memory/Memory.h"
#include "Cpu.h"

void GameBoy::load_buffer_as_cartridge(std::vector<uint8_t> buffer) {
	this->rom.load_data(buffer);
}
DataBus* GameBoy::get_databus() {
	return &this->data_bus;
}
void GameBoy::queue_event(GameBoyEvent event) {
	this->unprocessed_events.push(event);
}

void GameBoy::run_bootrom() {
	// This is the custom bootrom available at https://github.com/Hacktix/Bootix under the CC0-1.0 License.
	//  This does not contain any copyrighted Nintendo data.
	std::array<uint8_t, 256> bootrom = {
		0x31, 0xfe, 0xff, 0x21, 0xff, 0x9f, 0xaf, 0x32, 0xcb, 0x7c, 0x20, 0xfa, 0x0e, 0x11, 0x21, 0x26, 0xff, 0x3e,
		0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3, 0x32, 0xe2, 0x0c, 0x3e, 0x77, 0x32, 0xe2, 0x11, 0x04, 0x01, 0x21, 0x10,
		0x80, 0x1a, 0xcd, 0xb8, 0x00, 0x1a, 0xcb, 0x37, 0xcd, 0xb8, 0x00, 0x13, 0x7b, 0xfe, 0x34, 0x20, 0xf0, 0x11,
		0xcc, 0x00, 0x06, 0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9, 0x21, 0x04, 0x99, 0x01, 0x0c, 0x01, 0xcd,
		0xb1, 0x00, 0x3e, 0x19, 0x77, 0x21, 0x24, 0x99, 0x0e, 0x0c, 0xcd, 0xb1, 0x00, 0x3e, 0x91, 0xe0, 0x40, 0x06,
		0x10, 0x11, 0xd4, 0x00, 0x78, 0xe0, 0x43, 0x05, 0x7b, 0xfe, 0xd8, 0x28, 0x04, 0x1a, 0xe0, 0x47, 0x13, 0x0e,
		0x1c, 0xcd, 0xa7, 0x00, 0xaf, 0x90, 0xe0, 0x43, 0x05, 0x0e, 0x1c, 0xcd, 0xa7, 0x00, 0xaf, 0xb0, 0x20, 0xe0,
		0xe0, 0x43, 0x3e, 0x83, 0xcd, 0x9f, 0x00, 0x0e, 0x27, 0xcd, 0xa7, 0x00, 0x3e, 0xc1, 0xcd, 0x9f, 0x00, 0x11,
		0x8a, 0x01, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x1b, 0x7a, 0xb3, 0x20, 0xf5, 0x18, 0x49, 0x0e, 0x13, 0xe2,
		0x0c, 0x3e, 0x87, 0xe2, 0xc9, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20, 0xf7, 0xc9, 0x78, 0x22, 0x04,
		0x0d, 0x20, 0xfa, 0xc9, 0x47, 0x0e, 0x04, 0xaf, 0xc5, 0xcb, 0x10, 0x17, 0xc1, 0xcb, 0x10, 0x17, 0x0d, 0x20,
		0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9, 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c, 0x00, 0x54, 0xa8, 0xfc,
		0x42, 0x4f, 0x4f, 0x54, 0x49, 0x58, 0x2e, 0x44, 0x4d, 0x47, 0x20, 0x76, 0x31, 0x2e, 0x32, 0x00, 0x3e, 0xff,
		0xc6, 0x01, 0x0b, 0x1e, 0xd8, 0x21, 0x4d, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x3e, 0x01, 0xe0, 0x50,
	};
	this->rom.load_data(std::vector<uint8_t>(bootrom.begin(), bootrom.end()));
	this->cpu.point_pc_at_start_of_memory();

	for (int i = 0; i < 0x198; i++) {
		this->tick_machine_cycle();
	}
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