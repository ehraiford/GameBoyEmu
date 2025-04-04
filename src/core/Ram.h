#pragma once
#ifndef RAM_H
#define RAM_H
#include <iostream>
#include <mutex>
#include <vector>

class Ram {
  private:
	uint8_t memory[0xFFFF] = {};
	std::mutex mtx;

  public:
	Ram();
	~Ram();
	uint8_t get_memory(uint16_t address);
	std::array<uint8_t, 3> get_instruction(uint16_t address);
	void set_memory(uint16_t address, uint8_t value);
	void load_data(const std::vector<uint8_t> &data) {
		for (size_t i = 0; i < data.size(); ++i) {
			this->set_memory(i, data[i]);
		}
	}
};

#endif