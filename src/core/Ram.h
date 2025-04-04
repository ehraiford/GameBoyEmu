#pragma once
#ifndef RAM_H
#define RAM_H
#include "DataBus.h"
#include <iostream>
#include <mutex>
#include <vector>

class Ram : public Memory {
  private:
	uint8_t memory[0xFFFF] = {};
	std::mutex mtx;

  public:
	Ram();
	~Ram();
	uint8_t get_memory(uint16_t address) override;
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value) override;
	std::vector<std::tuple<uint16_t, uint16_t>> get_address_ranges() override;
	void load_data(const std::vector<uint8_t> &data);
};

#endif