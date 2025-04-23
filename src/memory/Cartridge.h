#pragma once
#include "Memory.h"
#include <iostream>
#include <vector>

struct CartridgeHeader {
	std::array<uint8_t, 48> logo;
	std::string title;
	std::string licensee_code;
	uint8_t cgb_flag;
	uint8_t sgb_flag;
	std::string cartridge_type;
	uint8_t num_rom_banks;
	uint8_t num_ram_banks;
	std::string destination;
	uint8_t version_number;
	uint8_t header_checksum;
	uint16_t global_checksum;

	CartridgeHeader();
	CartridgeHeader(uint8_t* header_ptr);
	void print_cartridge_data();
};

class Rom : public Memory {
  private:
	uint8_t* bank0_ptr;
	uint8_t* bank1_ptr;
	std::vector<std::array<uint8_t, 0x4000>> banks;

  public:
	Rom();
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	void load_data(const std::vector<uint8_t>& data);
	uint8_t* get_memory_ptr(uint16_t address) override;
	void initialize_from_cartridge_data(const std::vector<uint8_t>& data, uint8_t number_of_banks);
};

class ExternalRam : public Memory {
  private:
	uint8_t* bank_ptr;
	std::vector<std::array<uint8_t, 0x2000>> banks;

  public:
	ExternalRam();
	void initialize_banks(uint8_t number_of_banks);
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class Cartridge {
	CartridgeHeader header;
	ExternalRam ram;
	Rom rom;

  public:
	Cartridge();
	void initialize_cartridge_from_data(std::vector<uint8_t> data);
	ExternalRam* get_external_ram();
	Rom* get_rom();
};