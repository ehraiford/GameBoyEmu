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

bool Cpu::get_flag(Flag flag) {
    return this->f & flag;
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

void Cpu::set_flag(Flag flag, bool value) {
    this->f = value ? (this->f | flag) : (this->f & ~flag);
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


// opcodes
// LD r8,r8
void Cpu::copy(void* args) {
    uint8_t* dest = reinterpret_cast<uint8_t*>(args);
    uint8_t val = reinterpret_cast<uint8_t>(args + sizeof(uint8_t*));
    *dest = val;
};
// LD r8,n8
void Cpu::load_immediate_8bit(void* args) {
    uint8_t* dest = reinterpret_cast<uint8_t*>(args);
    uint8_t val = reinterpret_cast<uint8_t>(args + sizeof(uint8_t*));
    *dest = val;
};
// LD r16,n16
void Cpu::load_immediate_16bit(void* args) {
    uint16_t* dest = reinterpret_cast<uint16_t*>(args);
    uint16_t val = reinterpret_cast<uint16_t>(args + sizeof(uint16_t*));
    *dest = val;
};
// LD [HL],r8
void Cpu::store_at_hl_address(void* args) {
    uint8_t val = reinterpret_cast<uint8_t>(args);
    this->ram->set_memory((this->h << 8) | this->l, val);
};
// LD [HL],n8
void Cpu::store_immediate_at_hl_address(void* args) {
    uint8_t val = reinterpret_cast<uint8_t>(args);
    this->ram->set_memory((this->h << 8) | this->l, val);
};
// LD r8,[HL]
void Cpu::load_from_hl_address(void* args) {
    uint8_t* dest = reinterpret_cast<uint8_t*>(args);
    *dest = this->ram->get_memory((this->h << 8) | this->l);
};
// LD [r16],A
void Cpu::store_a_at_register_address(void* args) {
    uint16_t address = reinterpret_cast<uint16_t>(args);
    this->ram->set_memory(address, this->a);
};
// LD [n16],A
void Cpu::store_a_at_immediate_address(void* args) {
    uint16_t address = reinterpret_cast<uint16_t>(args);
    this->ram->set_memory(address, this->a);
};
// LDH [n16],A
void Cpu::store_a_at_immediate_hardware_address(void* args) {
    uint8_t addr_low = reinterpret_cast<uint8_t>(args);
    this->ram->set_memory(0xFF00 | addr_low, this->a);
};
// LDH [C],A
void Cpu::store_a_at_hardware_address_offset_by_c(void* args) {
    this->ram->set_memory(0xFF00 | this->c, this->a);
};
// LD A,[r16]
void Cpu::load_a_from_register_address(void* args) {
    uint16_t address = reinterpret_cast<uint16_t>(args);
    this->a = this->ram->get_memory(address);
};
// LD A,[r16]
void Cpu::load_a_from_immediate_address(void* args) {
    uint16_t address = reinterpret_cast<uint16_t>(args);
    this->a = this->ram->get_memory(address);
};
// LDH A,[n16]
void Cpu::load_a_from_immediate_hardware_address(void* args) {
    uint8_t addr_low = reinterpret_cast<uint8_t>(args);
    this->a = this->ram->get_memory(0xFF00 | addr_low);
};
// LDH A,[C]
void Cpu::load_a_from_hardware_address_offset_by_c(void* args) {
    this->a = this->ram->get_memory(0xFF00 | this->c);
};
// LD [HLI],A
void Cpu::store_a_at_hl_address_increment(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->ram->set_memory(hl, this->a);
    hl++;
    this->h = hl >> 8;
    this->l = hl & 0x00FF;
};
// LD [HLD],A
void Cpu::store_a_at_hl_address_decrement(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->ram->set_memory(hl, this->a);
    hl--;
    this->h = hl >> 8;
    this->l = hl & 0x00FF;
};
// LD A,[HLI]
void Cpu::load_a_from_hl_address_increment(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->a = this->ram->get_memory(hl);
    hl++;
    this->h = hl >> 8;
    this->l = hl & 0x00FF;
};
// LD A,[HLD]
void Cpu::load_a_from_hl_address_decrement(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->a = this->ram->get_memory(hl);
    hl--;
    this->h = hl >> 8;
    this->l = hl & 0x00FF;
};

// 8-bit arithmetic instructions
// ADC A,r8
void Cpu::add_with_carry_register_to_a(void* args) {

};