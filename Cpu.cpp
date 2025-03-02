#include "Cpu.h"
#include <iostream>

enum EightBitRegs {
    A, B, C, D, E, F, H, L,
};
enum SixteenBitRegs {
    AB, CD, EF, HL, SP,
};


bool is_little_endian() {
    uint16_t value = 0x0001;
    const uint8_t* pointer = reinterpret_cast<uint8_t*>(&value);
    return pointer[0] == 0x01;
}


class Cpu {
private:
    uint16_t reg_ab;
    uint16_t reg_cd;
    uint16_t reg_ef;
    uint16_t reg_hl;
    uint16_t reg_sp;
    
    // These two exist because of endianness. One is zero and the other is one. It lets us go from a 16-bit reg to an 8-bit one.
    // Whichever comes second should be one. (e.g., Big Endian, second_byte_offset would be 0)
    uint8_t first_byte_offset;
    uint8_t second_byte_offset;

    uint8_t* get_register(EightBitRegs reg) {
        switch (reg) {
            case EightBitRegs::A:
                return reinterpret_cast<uint8_t*>(&this->reg_ab) + this->first_byte_offset;
            case EightBitRegs::B:
                return reinterpret_cast<uint8_t*>(&this->reg_ab) + this->second_byte_offset;
            case EightBitRegs::C:
                return reinterpret_cast<uint8_t*>(&this->reg_cd) + this->first_byte_offset;
            case EightBitRegs::D:
                return reinterpret_cast<uint8_t*>(&this->reg_cd) + this->second_byte_offset;
            case EightBitRegs::E:
                return reinterpret_cast<uint8_t*>(&this->reg_ef) + this->first_byte_offset;
            case EightBitRegs::F:
                return reinterpret_cast<uint8_t*>(&this->reg_ef) + this->second_byte_offset;
            case EightBitRegs::H:
                return reinterpret_cast<uint8_t*>(&this->reg_hl) + this->first_byte_offset;
            case EightBitRegs::L:
                return reinterpret_cast<uint8_t*>(&this->reg_ef) + this->second_byte_offset;
        };
    };
    uint16_t* get_register(SixteenBitRegs reg) {
        switch (reg) {
            case SixteenBitRegs::AB:
                return &this->reg_ab;
            case SixteenBitRegs::CD:
                return &this->reg_cd;
            case SixteenBitRegs::EF:
                return &this->reg_ef;
            case SixteenBitRegs::HL:
                return &this->reg_hl;
            case SixteenBitRegs::SP:
                return &this->reg_sp;
        };
    };

public: 
    Cpu() {
        if (is_little_endian()) {
            this->second_byte_offset = 0;
            this->first_byte_offset = 1;
        } else {
            this->second_byte_offset = 1;
            this->first_byte_offset = 0;
        }
        this->reg_ab = 0;
        this->reg_cd = 0;
        this->reg_ef = 0;
        this->reg_hl = 0;
        this->reg_sp = 0;        
    };
    ~Cpu() {};
}; 
