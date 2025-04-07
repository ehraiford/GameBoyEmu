#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <vector>

struct Memory {
	virtual void set_memory(uint16_t address, uint8_t value) = 0;
	virtual uint8_t get_memory(uint16_t address) = 0;
};

class Rom : public Memory {
  private:
	uint8_t bank_0[0x4000] = {};
	uint8_t bank_1[0x4000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
	void load_data(const std::vector<uint8_t>& data);
};

class VideoRam : public Memory {
  private:
	uint8_t memory[0x2000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
};

class ExternalRam : public Memory {
  private:
	uint8_t memory[0x2000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
};

class WorkRam : public Memory {
  private:
	uint8_t bank_0[0x1000] = {};
	uint8_t bank_1[0x1000] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
};

class ObjectAttributeMemory : public Memory {
  private:
	uint8_t memory[0xA0] = {};

  public:
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
};

class IORegisters : public Memory {
  private:
	uint8_t memory[0x80] = {};
};

class HighRam : public Memory {
  private:
	uint8_t memory[0x7F] = {};
};

#endif