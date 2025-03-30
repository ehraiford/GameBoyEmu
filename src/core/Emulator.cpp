#include "Emulator.h"

void Emulator::load_rom(const std::string &file_path) {

	std::ifstream file(file_path, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Failed to open binary file: " << file_path << std::endl;
		return;
	}

	std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	this->gameboy.load_buffer_as_cartridge(buffer);
	file.close();
};