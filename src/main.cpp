#include "../gui/fast_emu_gui/fast_emu_gui.h"
#include "executors/GameBoy.h"
#include "instructions/Opcodes.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

std::unique_ptr<GameBoy> get_gameboy_with_loaded_rom(const std::string& file_path) {
	auto gameboy = std::make_unique<GameBoy>();
	std::ifstream file(file_path, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open binary file: " << file_path << std::endl;
		// todo: better handle when binaries aren't found
		return gameboy;
	}

	std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	gameboy->load_buffer_as_cartridge(buffer);
	gameboy->run_bootrom();
	return gameboy;
};

void emulator(const std::string& file_path) {
	std::unique_ptr<GameBoy> gameboy = get_gameboy_with_loaded_rom(file_path);
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1048576 * 4; i++) {
		gameboy->tick_machine_cycle();
	}
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "Time taken: " << duration.count() << " milliseconds\n";

	gameboy.get()->display_tiles();
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <path_to_binary_file>" << std::endl;
		return 1;
	}

	std::string file_path = argv[1];
	std::thread emu_thread(emulator, file_path);
	// start_fast_emu_gui();
	emu_thread.join();
	return 0;
};
