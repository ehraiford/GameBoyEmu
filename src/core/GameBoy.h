#include "Cpu.h"
#include "Ram.h"
class GameBoy {
	Cpu cpu;
	Ram ram;

  public:
	GameBoy() : cpu(), ram() {};

	void load_buffer_as_cartridge(std::vector<uint8_t> data);
	Ram *get_ram();
};