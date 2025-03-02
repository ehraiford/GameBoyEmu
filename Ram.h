#ifndef RAM_H
#define RAM_H
#include <iostream>

class Ram {
private:
    uint8_t memory[0xFFFF] = {};
public: 
    Ram();
    ~Ram();
    uint8_t get_memory(uint16_t address);
    void set_memory(uint16_t address);
};

#endif