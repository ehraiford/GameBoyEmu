#include "../gui/fast_emu_gui/fast_emu_gui.h"
#include "Cpu.h"
#include "FetchDecode.h"
#include "Opcodes.h"
#include "Ram.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

void load_binary_to_ram(Ram &ram, const std::string &file_path) {
  std::ifstream file(file_path, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Failed to open binary file: " << file_path << std::endl;
    return;
  }

  std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  ram.load_data(buffer);
  file.close();
}

void emulator(const std::string &file_path) {
  Cpu cpu = Cpu();
  Ram ram = Ram();

  load_binary_to_ram(ram, file_path);
  Fetcher fetcher = Fetcher(&ram);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 1; j++) {
      FetchedInstruction entry = fetcher.get_next_entry();
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