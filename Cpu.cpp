#include "Cpu.h"
#include <iostream>

uint8_t Cpu::get_r8(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return this->b;
        case 1:
            return this->c;
        case 2:
            return this->d;
        case 3:
            return this->e;
        case 4:
            return this->f;
        case 5:
            return this->h;
        case 6:
            return this->ram->get_memory((this->h << 8) | this->l);
        case 7:
            return this->a;
        default:
            std::cout << "This shouldn't be called with anything 7";
            return 0;
    };
};

uint16_t Cpu::get_r16(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return (this->b << 8) | this->c;
        case 1:
            return (this->d << 8) | this->e;
        case 2:
            return (this->h << 8) | this->l;
        case 3:
            return this->sp;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
            return 0;
    };
};

uint16_t Cpu::get_r16_stk(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return (this->b << 8) | this->c;
        case 1:
            return (this->d << 8) | this->e;
        case 2:
            return (this->h << 8) | this->l;
        case 3:
            return (this->a << 8) | this->f;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
            return 0;
    };
};

uint16_t Cpu::get_r16_mem(uint8_t register_number) {
    uint16_t hl;  
    uint16_t incremented_hl, decremented_hl;

    switch (register_number) {
        case 0:
            return (this->b << 8) | this->c;
        case 1:
            return (this->d << 8) | this->e;
        case 2:
            hl = (this->h << 8) | this->l;
            incremented_hl = hl + 1;
            this->h = incremented_hl >> 8;
            this->l = incremented_hl & 0x00FF;
            return hl;
        case 3:
            hl = (this->h << 8) | this->l;
            decremented_hl = hl - 1;
            this->h = decremented_hl >> 8;
            this->l = decremented_hl & 0x00FF;
            return hl;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
            return 0;
    }
};



bool Cpu::get_flag(uint8_t flag_number) {
    switch (flag_number) {
        case 0:
            // NOT Zero
            return (this->f >> 7 ) == 0;
        case 1:
            // Zero
            return (this->f >> 7 ) == 1; 
        case 2:
            // NOT Carry 
            return (this->f >> 4 ) == 0;
        case 3:
            // Carry
            return (this->f >> 4 ) == 1;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
            return false;
    };
};

void Cpu::set_r8(uint8_t register_number, uint8_t value) {
    switch (register_number) {
        case 7:
            this->a = value;
            break;
        case 0:
            this->b = value;
            break;
        case 1:
            this->c = value;
            break;
        case 2:
            this->d = value;
            break;
        case 3:
            this->e = value;
            break;
        case 4:
            this->f = value;
            break;
        case 5:
            this->h = value;
            break;
        case 6:
            this->ram->set_memory((this->h << 8) | this->l, value);
            break;
        default:
            std::cout << "This shouldn't be called with anything higher than 7";
    };
};

void Cpu::set_r16(uint8_t register_number, uint16_t value) {
    switch (register_number) {
        case 0:
            this->b = (value >> 8);
            this->c = value & 0x00FF;
        case 1:
            this->d = (value >> 8);
            this->e = value & 0x00FF;
        case 2:
            this->h = (value >> 8);
            this->l = value & 0x00FF;
        case 3:
            this->sp = value;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
    };
};

void Cpu::set_r16_stk(uint8_t register_number, uint16_t value) {
    switch (register_number) {
        case 0:
            this->b = (value >> 8);
            this->c = value & 0x00FF;
        case 1:
            this->d = (value >> 8);
            this->e = value & 0x00FF;
        case 2:
            this->h = (value >> 8);
            this->l = value & 0x00FF;
        case 3:
            this->a = (value >> 8);
            this->f = value & 0x00FF;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
    };
};

Cpu::Cpu() {
    this->a = 0;
    this->c = 0;
    this->e = 0;
    this->h = 0;
    this->b = 0;
    this->d = 0;
    this->f = 0;
    this->l = 0;   
    this->sp = 0;    
    this->pc = 0;    
};
Cpu::~Cpu() {};
