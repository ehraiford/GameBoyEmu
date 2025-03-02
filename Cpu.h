#ifndef CPU_H  
#define CPU_H
#include <iostream>
#include "Ram.h"

enum EightBitRegs {
    B, C, D, E, F, H, L, A
};
enum SixteenBitRegs {
    BC, DE, HL, SP,
};



class Cpu {
private:
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    Ram* ram;


    uint8_t get_r8(uint8_t register_number);
    uint16_t get_r16(uint8_t register_number);
    uint16_t get_r16_stk(uint8_t register_number);
    uint16_t get_r16_mem(uint8_t register_number);
    bool get_flag(uint8_t flag_number);
    
    void set_r8(uint8_t register_number, uint8_t value);
    void set_r16(uint8_t register_number, uint16_t value);
    void set_r16_stk(uint8_t register_number, uint16_t value);

public:
    Cpu();      
    ~Cpu();
    
};

#endif
