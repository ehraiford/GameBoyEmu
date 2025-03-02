#ifndef CPU_H  
#define CPU_H
#include <iostream>

enum EightBitRegs {
    A, B, C, D, E, F, H, L,
};
enum SixteenBitRegs {
    AB, CD, EF, HL, SP,
};

class Cpu {
private:
    uint16_t reg_ab;
    uint16_t reg_cd;
    uint16_t reg_ef;
    uint16_t reg_hl;
    uint16_t reg_sp;
    uint8_t first_byte_offset;
    uint8_t second_byte_offset;
    uint8_t* get_register(EightBitRegs reg);
    uint16_t* get_register(SixteenBitRegs reg);

public:
    Cpu();      
    ~Cpu();
    
};

#endif
