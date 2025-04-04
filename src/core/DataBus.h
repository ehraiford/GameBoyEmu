#include "Cpu.h"
#include "Ram.h"

// Forward declaration of Ppu to avoid circular dependency
class Ppu;

class DataBus {
	Cpu *cpu;
	Ram *ram;
	Ppu *ppu;

  public:
	Cpu *get_cpu();
	Ram *get_ram();
	Ppu *get_ppu();
	void write_memory(uint16_t address, uint8_t value);
	uint8_t get_memory(uint16_t address);
	// uint8_t (*memory_map(uint16_t address))(uint16_t);
};