#pragma once
#include <iostream>
#include <vector>

struct Memory {
	virtual void set_memory(uint16_t address, uint8_t value) = 0;
	virtual uint8_t get_memory(uint16_t address) = 0;
	virtual uint8_t* get_memory_ptr(uint16_t address) = 0;
	virtual std::array<uint8_t, 3> get_instruction(uint16_t address) = 0;
};

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

	CartridgeHeader(uint8_t* header_ptr);
	void print_cartridge_data();
};

class Rom : public Memory {
  private:
	uint8_t bank_0[0x4000] = {};
	uint8_t bank_1[0x4000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
	void load_data_as_cartridge(const std::vector<uint8_t>& data);
};

class VideoRam : public Memory {
  private:
	uint8_t memory[0x2000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class ExternalRam : public Memory {
  private:
	uint8_t memory[0x2000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class WorkRam : public Memory {
  private:
	uint8_t bank_0[0x1000] = {};
	uint8_t bank_1[0x1000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class ObjectAttributeMemory : public Memory {
  private:
	uint8_t memory[0xA0] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class IORegisters : public Memory {
  private:
	uint8_t memory[0x80] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};

class HighRam : public Memory {
  private:
	uint8_t memory[0x7F] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address) override;
	void set_memory(uint16_t address, uint8_t value) override;
	uint8_t* get_memory_ptr(uint16_t address) override;
};
