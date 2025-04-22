#pragma once
#include <iostream>
#include <vector>

struct Memory {
	virtual void set_memory(uint16_t address, uint8_t value) = 0;
	virtual uint8_t get_memory(uint16_t address) = 0;
	virtual uint8_t* get_memory_ptr(uint16_t address) = 0;
	virtual std::array<uint8_t, 3> get_instruction(uint16_t address) = 0;
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
