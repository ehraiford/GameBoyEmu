#include "Cpu.h"
#include <iostream>

uint8_t Cpu::get_8bit_register(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return this->reg_b;
        case 1:
            return this->reg_c;
        case 2:
            return this->reg_d;
        case 3:
            return this->reg_e;
        case 4:
            return this->reg_f;
        case 5:
            return this->reg_h;
        case 6:
            return this->ram->get_memory((this->reg_h << 8) | this->reg_l);
        case 7:
            return this->reg_a;
    };
};
uint16_t Cpu::get_16bit_register(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return (this->reg_b << 8) | this->reg_c;
        case 1:
            return (this->reg_d << 8) | this->reg_e;
        case 2:
            return (this->reg_h << 8) | this->reg_l;
        case 3:
            return this->reg_sp;
    };
};

void Cpu::set_8bit_register(uint8_t register_number, uint8_t value) {
    switch (register_number) {
        case 7:
            this->reg_a = value;
            break;
        case 0:
            this->reg_b = value;
            break;
        case 1:
            this->reg_c = value;
            break;
        case 2:
            this->reg_d = value;
            break;
        case 3:
            this->reg_e = value;
            break;
        case 4:
            this->reg_f = value;
            break;
        case 5:
            this->reg_h = value;
            break;
        case 6:
            this->ram->set_memory((this->reg_h << 8) | this->reg_l, value);
            break;
    };
};

void Cpu::set_16bit_register(uint8_t register_number, uint16_t value) {
    switch (register_number) {
        case 0:
            this->reg_b = (value >> 8);
            this->reg_c = value & 0x00FF;
        case 1:
            this->reg_d = (value >> 8);
            this->reg_e = value & 0x00FF;
        case 2:
            this->reg_h = (value >> 8);
            this->reg_l = value & 0x00FF;
        case 3:
            this->reg_sp = value;
    };
};

Cpu::Cpu() {
    this->reg_a = 0;
    this->reg_c = 0;
    this->reg_e = 0;
    this->reg_h = 0;
    this->reg_sp = 0;    
    this->reg_b = 0;
    this->reg_d = 0;
    this->reg_f = 0;
    this->reg_l = 0;       
};
Cpu::~Cpu() {};
