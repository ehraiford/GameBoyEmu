#include "../instructions/FetchDecode.h"
#include "GameBoy.h"
#include <fstream>
class Emulator {
	GameBoy gameboy;

  public:
	Emulator();
	GameBoy get_gameboy();
	void load_rom(const std::string &file_path);
	Fetcher create_instruction_fetcher();
};