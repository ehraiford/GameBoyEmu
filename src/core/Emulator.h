#include "GameBoy.h"
#include <fstream>
class Emulator {
	GameBoy gameboy;

  public:
	void load_rom(const std::string &file_path);
	Emulator();
};