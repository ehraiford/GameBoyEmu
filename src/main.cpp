#include "../gui/fast_emu_gui/fast_emu_gui.h"
#include "core/Emulator.h"
#include "instructions/FetchDecode.h"
#include "instructions/Opcodes.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

void emulator(const std::string &file_path) {
	Emulator emulator = Emulator();

	emulator.load_rom(file_path);
	Fetcher fetcher = emulator.create_instruction_fetcher();
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 1; j++) {
			FetchedInstruction entry = fetcher.get_next_instruction_to_execute();
			std::cout << entry.get_disassembly() << ",\t";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <path_to_binary_file>" << std::endl;
		return 1;
	}

	std::string file_path = argv[1];
	std::thread emu_thread(emulator, file_path);
	// start_fast_emu_gui();
	emu_thread.join();
	return 0;
};