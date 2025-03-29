#ifndef RAM_H
#define RAM_H
#include <mutex>
#include <iostream>

class Ram
{
private:
    uint8_t memory[0xFFFF] = {};
    std::mutex mtx;

public:
    Ram();
    ~Ram();
    uint8_t get_memory(uint16_t address);
    std::array<uint8_t, 3> get_instruction(uint16_t address);
    void set_memory(uint16_t address, uint8_t value);
    uint8_t *get_mem_pointer(uint16_t address);
};

#endif