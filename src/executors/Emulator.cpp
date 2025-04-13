#include "Emulator.h"
#include "../instructions/FetchDecode.h"

Emulator::Emulator() : gameboy() {};
Emulator::Emulator(const std::string& file_path) : gameboy() {
	this->load_rom(file_path);
}

void Emulator::load_rom(const std::string& file_path) {

	std::ifstream file(file_path, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open binary file: " << file_path << std::endl;
		return;
	}

	std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	this->gameboy.load_buffer_as_cartridge(buffer);
	file.close();
};

Fetcher Emulator::create_instruction_fetcher() {
	return Fetcher(this->gameboy.get_databus());
};

void Emulator::tick() {
	this->gameboy.tick_machine_cycle();
};
