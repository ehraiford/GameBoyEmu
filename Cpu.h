#ifndef CPU_H  
#define CPU_H
#include <iostream>
#include "Ram.h"

enum EightBitRegs {
    A, B, C, D, E, F, H, L,
};
enum SixteenBitRegs {
    BC, DE, HL, SP,
};



class Cpu {
private:
    uint8_t reg_a;
    uint8_t reg_b;
    uint8_t reg_c;
    uint8_t reg_d;
    uint8_t reg_e;
    uint8_t reg_f;
    uint8_t reg_h;
    uint8_t reg_l;
    uint16_t reg_sp;
    Ram* ram;


    uint8_t get_8bit_register(uint8_t register_number);
    uint16_t get_16bit_register(uint8_t register_number);

    void set_8bit_register(uint8_t register_number, uint8_t value);
    void set_16bit_register(uint8_t register_number, uint16_t value);

public:
    Cpu();      
    ~Cpu();
    
};

#endif
