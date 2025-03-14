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
            return this->ram->get_memory(this->get_hl());
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
            return this->get_hl();
        case 3:
            return this->sp;
        default:
            std::cout << "This shouldn't be called with anything higher than 3";
            return 0;
    };
};

uint16_t Cpu::get_hl() {
    return (this->h << 8) | this->l;
};
void Cpu::set_hl(uint16_t value) {
    this->h = value >> 8;
    this->l = value;
};

uint16_t Cpu::get_r16_stk(uint8_t register_number) {
    switch (register_number) {
        case 0:
            return (this->b << 8) | this->c;
        case 1:
            return (this->d << 8) | this->e;
        case 2:
            return this->get_hl();
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
            hl = this->get_hl();
            incremented_hl = hl + 1;
            this->h = incremented_hl >> 8;
            this->l = incremented_hl & 0x00FF;
            return hl;
        case 3:
            hl = this->get_hl();
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
            this->ram->set_memory(this->get_hl(), value);
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
// Sets the flags in the standard way for an addition operation.
void Cpu::set_flags_addition(uint16_t op0, uint16_t op1, uint16_t result) {
    this->set_flag(Flag::Z, (result & 0x00FF) == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, (op0 & 0x0F) + (op1 & 0x0F) > 0x0F);
    this->set_flag(Flag::C, result > 0xFF);
};
// Sets the flags in the standard way for a subtraction operation.
void Cpu::set_flags_subtraction(uint16_t op0, uint16_t op1, uint16_t result) {
    this->set_flag(Flag::Z, (result & 0x00FF) == 0);
    this->set_flag(Flag::N, true);
    this->set_flag(Flag::H, (op0 & 0x0F) < (op1 & 0x0F));
    this->set_flag(Flag::C, op0 < op1);
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
    this->ram->set_memory(this->get_hl(), val);
};
// LD [HL],n8
void Cpu::store_immediate_at_hl_address(void* args) {
    uint8_t val = reinterpret_cast<uint8_t>(args);
    this->ram->set_memory(this->get_hl(), val);
};
// LD r8,[HL]
void Cpu::load_from_hl_address(void* args) {
    uint8_t* dest = reinterpret_cast<uint8_t*>(args);
    *dest = this->ram->get_memory(this->get_hl());
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
    uint16_t hl = this->get_hl();
    this->ram->set_memory(hl, this->a);
    hl++;
    this->h = hl >> 8;
    this->l = hl;
};
// LD [HLD],A
void Cpu::store_a_at_hl_address_decrement(void* args) {
    uint16_t hl = this->get_hl();
    this->ram->set_memory(hl, this->a);
    hl--;
    this->h = hl >> 8;
    this->l = hl;
};
// LD A,[HLI]
void Cpu::load_a_from_hl_address_increment(void* args) {
    uint16_t hl = this->get_hl();
    this->a = this->ram->get_memory(hl);
    hl++;
    this->h = hl >> 8;
    this->l = hl;
};
// LD A,[HLD]
void Cpu::load_a_from_hl_address_decrement(void* args) {
    uint16_t hl = this->get_hl();
    this->a = this->ram->get_memory(hl);
    hl--;
    this->h = hl >> 8;
    this->l = hl;
};

// 8-bit arithmetic instructions
// ADC A,r8
void Cpu::add_with_carry_register_to_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args) + ((this->get_flag(Flag::C) << 8));
    uint16_t result = this->a + value;
    
    this->set_flags_addition(this->a, value, result);
    this->a = result;
};

// ADC A,[HL]
void Cpu::add_with_carry_from_hl_address_to_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args) + (this->get_flag(Flag::C) << 8);
    uint16_t result = this->a + value;
    
    this->set_flags_addition(this->a, value, result);
    this->a = result;
};

// ADC A,n8
void Cpu::add_with_carry_immediate_to_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args) + (this->get_flag(Flag::C) << 8);
    uint16_t result = this->a + value;
    
    this->set_flags_addition(this->a, value, result);
    this->a = result;
};

// ADD A,r8
void Cpu::add_register_to_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint16_t result = this->a + value;

    this->set_flags_addition(this->a, value, result);
    this->a = result;
};
// ADD A,[HL]
void Cpu::add_value_at_hl_address_to_a(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    uint16_t result = this->a + value;

    this->set_flags_addition(this->a, value, result);
    this->a = result;
};
// ADD A,n8
void Cpu::add_immediate_to_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint16_t result = this->a + value;

    this->set_flags_addition(this->a, value, result);
    this->a = result;
};
// CP A,r8
void Cpu::compare_a_with_register(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
};
// CP A,[HL]
void Cpu::compare_a_with_value_at_hl_address(void* args) {
    uint8_t value =  this->ram->get_memory((this->h <<8) | this->l);
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
};
// CP A,n8
void Cpu::compare_a_with_immediate(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
};
// DEC r8
void Cpu::decrement_register(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t result = *reg - 1;

    this->set_flag(Flag::Z, result == 0);
    this->set_flag(Flag::N, true);
    this->set_flag(Flag::H, *reg & 0x0F == 0);
    *reg = result;
};
// DEC [HL]
void Cpu::decrement_value_at_hl_address(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    uint8_t result = value - 1;

    this->set_flag(Flag::Z, result == 0);
    this->set_flag(Flag::N, true);
    this->set_flag(Flag::H, value & 0x0F == 0);
    this->ram->set_memory(this->get_hl(), result);
};
// INC r8
void Cpu::increment_register(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t result = *reg + 1;

    this->set_flag(Flag::Z, result == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, *reg & 0x0F == 0x0F);
    *reg = result;
};
// INC [HL]
void Cpu::increment_value_at_hl_address(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    uint8_t result = value + 1;

    this->set_flag(Flag::Z, result == 0);
    this->set_flag(Flag::N, true);
    this->set_flag(Flag::H, value & 0x0F == 0x0F);
    this->ram->set_memory(this->get_hl(), result);
};
// SBC A,r8
void Cpu::subtract_with_carry_register_from_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args) + ((this->get_flag(Flag::C) << 8));
    uint8_t result = this->a - value;
    
    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};
// SBC A,[HL]
void Cpu::subtract_with_carry_value_at_hl_address_from_a(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl()) + ((this->get_flag(Flag::C) << 8));
    uint8_t result = this->a - value;
    
    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};
// SBC A,n8
void Cpu::subtract_with_carry_immediate_from_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args) + ((this->get_flag(Flag::C) << 8));
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};
// SUB A,r8
void Cpu::subtract_register_from_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint8_t result = this->a - value; 

    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};
// SUB A,[HL]
void Cpu::subtract_value_at_hl_address_from_a(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};
// SUB A,n8
void Cpu::subtract_immediate_from_a(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    uint8_t result = this->a - value;

    this->set_flags_subtraction(this->a, value, result);
    this->a = result;
};

// 16-bit arithmetic operations
// ADD HL,r16
void Cpu::add_16bit_register_to_HL(void* args) {
    uint16_t value = reinterpret_cast<uint16_t>(args);
    uint32_t result = this->get_hl() + value;

    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, ((this->get_hl() & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);
    this->set_flag(Flag::C, result > 0xFFFF);
    this->set_hl(result);
};
// DEC r16
void Cpu::decrement_16bit_register(void* args) {
    uint16_t* reg = reinterpret_cast<uint16_t*>(args);
    *reg -= 1;
};
// INC r16
void Cpu::increment_16bit_register(void* args) {
    uint16_t* reg = reinterpret_cast<uint16_t*>(args);
    *reg += 1;
};

// Bitwise logic instructions
// AND A,r8
void Cpu::and_a_with_register(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a &= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, true);
    this->set_flag(Flag::C, false);
};
// AND A,[HL]
void Cpu::and_a_with_value_at_hl_address(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    this->a &= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, true);
    this->set_flag(Flag::C, false);
};
// AND A,n8
void Cpu::and_a_with_immediate(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a &= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, true);
    this->set_flag(Flag::C, false);
};
// CPL
void Cpu::invert_a(void* args) {
    this->a = ~this->a;

    this->set_flag(Flag::N, true);
    this->set_flag(Flag::H, true);
};
// OR A,r8
void Cpu::or_a_with_register(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a |= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};
// OR A,[HL]
void Cpu::or_a_with_value_at_hl_address(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    this->a |= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};
// OR A,n8
void Cpu::or_a_with_immediate(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a |= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};
// XOR A,r8
void Cpu::xor_a_with_register(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a ^= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};
// XOR A,[HL]
void Cpu::xor_a_with_value_at_hl_address(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    this->a ^= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};
// XOR A,n8
void Cpu::xor_a_with_immediate(void* args) {
    uint8_t value = reinterpret_cast<uint8_t>(args);
    this->a ^= value;

    this->set_flag(Flag::Z, this->a == 0);
    this->set_flag(Flag::N, false);    
    this->set_flag(Flag::H, false);    
    this->set_flag(Flag::C, false);
};

// Bitflag instructions
// BIT u3,r8
void Cpu::set_zflag_if_register_bit_not_set(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t reg_value = reinterpret_cast<uint8_t>(args + sizeof(uint8_t));
    this->set_flag(Flag::Z, (reg_value & (1 << bit_position)) == 0);

    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, true);
};
// BIT u3,[HL]
void Cpu::set_zflag_if_value_at_hl_address_bit_not_set(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t value = this->ram->get_memory(this->get_hl());

    this->set_flag(Flag::Z, (value & (1 << bit_position)) == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, true);
};
// RES u3,r8
void Cpu::clear_register_bit(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t* reg = reinterpret_cast<uint8_t*>(args + sizeof(uint8_t));
    *reg &= ~(1 << bit_position);
};
// RES u3,[HL]
void Cpu::clear_value_at_hl_address_bit(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t value = this->ram->get_memory(this->get_hl());
    value &= ~(1 << bit_position);
    this->ram->set_memory(this->get_hl(), value);
};
// SET u3,r8
void Cpu::set_register_bit(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t* reg = reinterpret_cast<uint8_t*>(args + sizeof(uint8_t));
    *reg |= 1 << bit_position;
};
// SET u3,[HL]
void Cpu::set_value_at_hl_address_bit(void* args) {
    uint8_t bit_position = reinterpret_cast<uint8_t>(args);
    uint8_t value = this->ram->get_memory(this->get_hl());
    value |= 1 << bit_position;
    this->ram->set_memory(this->get_hl(), value);
};

// Bit shift instructions
// RL r8
void Cpu::rotate_register_left(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t value = *reg;
    bool new_carry = value & 0b10000000;

    value <<= 1;
    value &= 0b11111110;
    value |= this->get_flag(Flag::C);
    
    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false); 
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    *reg = value;
};
// RL [HL]
void Cpu::rotate_value_at_hl_address_left(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    bool new_carry = value & 0b10000000;

    value <<= 1;
    value &= 0b11111110;
    value |= this->get_flag(Flag::C);

    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->ram->set_memory(this->get_hl(), value);
};
// RLA
void Cpu::rotate_a_left(void* args) {
    uint8_t a = this->a;

    bool new_carry = this->a & 0b10000000;
    a <<= 1;
    a &= 0b11111110;
    a |= this->get_flag(Flag::C);

    this->set_flag(Flag::Z, false);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->a = a;
};
// RLC r8
void Cpu::rotate_register_left_carry(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t value = *reg;
    bool new_carry = value & 0b10000000;

    value <<= 1;
    value &= 0b11111110;
    value |= new_carry;
    
    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false); 
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    *reg = value;
};
// RLC [HL]
void Cpu::rotate_value_at_hl_address_left_carry(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    bool new_carry = value & 0b10000000;

    value <<= 1;
    value &= 0b11111110;
    value |= new_carry;

    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->ram->set_memory(this->get_hl(), value);
};
// RLCA
void Cpu::rotate_a_left_carry(void* args) {
    uint8_t a = this->a;

    bool new_carry = this->a & 0b10000000;
    a <<= 1;
    a &= 0b11111110;
    a |= new_carry;

    this->set_flag(Flag::Z, false);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->a = a;
};
// RR r8
void Cpu::rotate_register_right(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t value = *reg;
    bool new_carry = value & 0b1;

    value >>= 1;
    value &= 0b01111111;
    value |= this->get_flag(Flag::C) << 7;
    
    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false); 
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    *reg = value;
};
// RR [HL]
void Cpu::rotate_value_at_hl_address_right(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    bool new_carry = value & 0b1;

    value >>= 1;
    value &= 0b01111111;
    value |= this->get_flag(Flag::C) << 7;

    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->ram->set_memory(this->get_hl(), value);
};
// RRA
void Cpu::rotate_a_right(void* args) {
    uint8_t a = this->a;

    bool new_carry = this->a & 0b1;
    a >>= 1;
    a &= 0b01111111;
    a |= this->get_flag(Flag::C) << 7;

    this->set_flag(Flag::Z, false);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->a = a;
};
// RRC r8
void Cpu::rotate_register_right_with_carry(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t value = *reg;
    bool new_carry = value & 0b1;

    value >>= 1;
    value &= 0b01111111;
    value |= new_carry << 7;
    
    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false); 
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    *reg = value;
};
// RRC [HL]
void Cpu::rotate_value_at_hl_address_right_with_carry(void* args) {
    uint8_t value = this->ram->get_memory(this->get_hl());
    bool new_carry = value & 0b1;

    value >>= 1;
    value &= 0b01111111;
    value |= new_carry << 7;

    this->set_flag(Flag::Z, value == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->ram->set_memory(this->get_hl(), value);
};
// RRCA
void Cpu::rotate_a_right_with_carry(void* args) {
    uint8_t a = this->a;

    bool new_carry = this->a & 0b1;
    a >>= 1;
    a &= 0b01111111;
    a |= new_carry << 7;

    this->set_flag(Flag::Z, false);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, false);
    this->set_flag(Flag::C, new_carry);
    this->a = a;
};
// SLA r8
void Cpu::shift_register_left_arithmetically(void* args) {
    uint8_t* reg = reinterpret_cast<uint8_t*>(args);
    uint8_t value = *reg;
    
    bool new_carry = *reg & 0b1;
    value <<= 1;
};
// SLA [HL]
void Cpu::shift_value_at_hl_address_left_arithmetically(void* args) {
};
// SRA r8
void Cpu::shift_register_right_arithmetically(void* args) {
};
// SRA [HL]
void Cpu::shift_value_at_hl_address_right_arithmetically(void* args) {
};
// SRL r8
void Cpu::shift_register_right_logically(void* args) {
};
// SRL [HL]
void Cpu::shift_value_at_hl_address_right_logically(void* args) {
};
// SWAP r8
void Cpu::swap_register_nibbles(void* args) {
};
// SWAP [HL]
void Cpu::swap_value_at_hl_address_nibbles(void* args) {
};

// Jump and Subroutine instructions
// CALL n16
void Cpu::push_next_address_to_stack(void* args) {
};
// CALL cc,n16
void Cpu::push_next_address_to_stack_conditionally(void* args) {
};
// JP HL
void Cpu::jump_to_value_at_hl_address(void* args) {
};
// JP n16
void Cpu::jump_to_immediate(void* args) {
};
// JP cc,n16
void Cpu::jump_to_immediate_conditionally(void* args) {
};
// JR n16
void Cpu::jump_relative_to_immediate(void* args) {

};
// JR cc,n16
void Cpu::jump_relative_to_immediate_conditionally(void* args) {
};
// RET cc
void Cpu::return_from_subroutine_conditionally(void* args) {
};
// RET
void Cpu::return_from_subroutine(void* args) {
};
// RETI
void Cpu::return_from_interrupt_subroutine(void* args) {
};
// RST vec
void Cpu::call_address(void* args) {
};

// Carry Flag Instructions
// CCF
void Cpu::invert_carry_flag(void* args) {
};
// SCF
void Cpu::set_carry_flag(void* args) {
};

// Stack instructions
// ADD HL,SP
void Cpu::add_hl_to_sp(void* args) {
};
// ADD SP,e8
void Cpu::add_signed_immediate_to_sp(void* args) {

};
// DEC SP
void Cpu::decrement_sp(void* args) {
};
// INC SP
void Cpu::increment_sp(void* args) {
};
// LD SP,n16
void Cpu::load_sp_from_immediate_16bit(void* args) {
};
// LD [n16],SP
void Cpu::store_sp_at_immediate_address(void* args) {
};
// LD HL,SP+e8
void Cpu::load_hl_from_sp_plus_signed_immediate(void* args){

};
// LD SP,HL
void Cpu::copy_hl_to_sp(void* args) {
};
// POP AF
void Cpu::pop_stack_to_af(void* args) {
};
// POP r16
void Cpu::pop_stack_to_16bit_register(void* args) {
};
// PUSH AF
void Cpu::push_af_to_stack(void* args) {
};
// PUSH r16
void Cpu::push_16bit_register_to_stack(void* args) {
};

// Interrupt Instructions
// DI
void Cpu::disable_interrupts(void* args) {
};
// EI
void Cpu::enable_interrupts(void* args) {
};
// HALT
void Cpu::halt(void* args) {
};

// Miscellaneous
// DAA
void Cpu::decimal_adjust_accumulator(void* args) {

};
// NOP
void Cpu::nop(void* args) {

};
// STOP
void Cpu::stop(void* args) {

};
