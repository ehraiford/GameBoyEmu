#include "Cpu.h"
#include "Memory.h"
class GameBoy {
	Cpu cpu;
	Rom ram;

  public:
	GameBoy() : cpu(), ram() {};

	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	Rom *get_rom();
};