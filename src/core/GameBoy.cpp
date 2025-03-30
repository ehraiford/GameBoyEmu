#include "GameBoy.h"
#include "Cpu.h"
#include "Ram.h"

void GameBoy::load_buffer_as_cartridge(std::vector<uint8_t> buffer) {
	this->ram.load_data(buffer);
}