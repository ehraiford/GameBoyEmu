#include "Cpu.h"
#include "Ram.h"
#include <tuple>
#include <vector>

class Ppu;

struct Memory {
	virtual void set_memory(uint16_t address, uint8_t value) = 0;
	virtual uint8_t get_memory(uint16_t address);
	virtual std::vector<std::tuple<uint16_t, uint16_t>> get_address_ranges() = 0;
};

class DataBus : public Memory {
	Cpu *cpu;
	Ram *ram;
	Ppu *ppu;
	std::optional<Memory *> determine_device_from_address(uint16_t address);

  public:
	Cpu *get_cpu();
	Ram *get_ram();
	Ppu *get_ppu();
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t get_memory(uint16_t address) override;
	std::vector<std::tuple<uint16_t, uint16_t>> get_address_ranges() override;
	std::array<uint8_t, 0xA0> get_dma_oam_data(uint16_t starting_address);
};
