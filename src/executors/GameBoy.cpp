#include "GameBoy.h"
#include "../memory/Memory.h"
#include "Cpu.h"

void GameBoy::load_buffer_as_cartridge(std::vector<uint8_t> buffer) {
	this->rom.load_data(buffer);
}
Rom* GameBoy::get_rom() {
	return &this->rom;
}
