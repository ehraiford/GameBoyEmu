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
void Cpu::set_flags_addition(uint16_t op0, uint16_t op1, uint16_t result) {
    this->set_flag(Flag::Z, (result & 0x00FF) == 0);
    this->set_flag(Flag::N, false);
    this->set_flag(Flag::H, (op0 & 0x0F) + (op1 & 0x0F) > 0x0F);
    this->set_flag(Flag::C, result > 0xFF);
};
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
    this->l = hl;
};
// LD [HLD],A
void Cpu::store_a_at_hl_address_decrement(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->ram->set_memory(hl, this->a);
    hl--;
    this->h = hl >> 8;
    this->l = hl;
};
// LD A,[HLI]
void Cpu::load_a_from_hl_address_increment(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
    this->a = this->ram->get_memory(hl);
    hl++;
    this->h = hl >> 8;
    this->l = hl;
};
// LD A,[HLD]
void Cpu::load_a_from_hl_address_decrement(void* args) {
    uint16_t hl = (this->h << 8) | this->l;
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
    uint8_t value = this->ram->get_memory((this->h << 8) | this->l);
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

};
// CP A,[HL]
void compare_a_with_value_at_hl_address(void* args) {
}
// CP A,n8
void compare_a_with_immediate(void* args) {
}
// DEC r8
void decrement_register(void* args) {
}
// DEC [HL]
void decrement_value_at_hl_address(void* args) {
}
// INC r8
void increment_register(void* args) {
}
// INC [HL]
void increment_value_at_hl_address(void* args) {
}
// SBC A,r8
void subtract_with_carry_register_from_a(void* args) {
}
// SBC A,[HL]
void subtract_with_carry_value_at_hl_address_from_a(void* args) {
}
// SBC A,n8
void subtract_with_carry_immediate_from_a(void* args) {
}
// SUB A,r8
void subtract_register_from_a(void* args) {
}
// SUB A,[HL]
void subtract_value_at_hl_address_from_a(void* args) {
}
// SUB A,n8
void subtract_immediate_from_a(void* args) {
}

// 16-bit arithmetic operations
// ADD HL,r16
void add_16bit_register_to_HL(void* args) {
}
// DEC r16
void decrement_16bit_register(void* args) {
}
// INC r16
void increment_16bit_register(void* args) {
}

// Bitwise logic instructions
// AND A,r8
void and_a_with_register(void* args) {
}
// AND A,[HL]
void and_a_with_value_at_hl_address(void* args) {
}
void and_a_with_immediate(void* args);// AND A,n8
// CPL
void invert_a(void* args) {
}
// OR A,r8
void or_a_with_register(void* args) {
}
// OR A,[HL]
void or_a_with_value_at_hl_address(void* args) {
}
// OR A,n8
void or_a_with_immediate(void* args) {
}
// XOR A,r8
void xor_a_with_register(void* args) {
}
// XOR A,[HL]
void xor_a_with_value_at_hl_address(void* args) {
}
// XOR A,n8
void xor_a_with_immediate(void* args) {
}

// Bitflag instructions
// BIT u3,r8
void set_zflag_if_register_bit_not_set(void* args) {
}
// BIT u3,[HL]
void set_zflag_if_value_at_hl_address_bit_not_set(void* args) {
}
// RES u3,r8
void clear_register_bit(void* args) {
}
// RES u3,[HL]
void clear_value_at_hl_address_bit(void* args) {
}
// SET u3,r8
void set_register_bit(void* args) {
}
// SET u3,[HL]
void set_value_at_hl_address_bit(void* args);

// Bit shift instructions
// RL r8
void rotate_register_left(void* args) {
}
// RL [HL]
void rotate_value_at_hl_address_left(void* args) {
}
// RLA
void rotate_a_left(void* args) {
}
// RLC r8
void rotate_register_left_carry(void* args);
// RLC [HL]
void rotate_value_at_hl_address_left_carry(void* args) {
}
// RLCA
void rotate_a_left_carry(void* args) {
}
// RR r8
void rotate_register_right(void* args) {
}
// RR [HL]
void rotate_value_at_hl_address_right(void* args) {
}
// RRA
void rotate_a_right(void* args) {
}
// RRC r8
void rotate_register_right_with_carry(void* args) {
}
// RRC [HL]
void rotate_value_at_hl_address_right_with_carry(void* args) {
}
// RRCA
void rotate_a_right_with_carry(void* args) {
}
// SLA r8
void shift_register_left_arithmetically(void* args) {
}
// SLA [HL]
void shift_value_at_hl_address_left_arithmetically(void* args) {
}
// SRA r8
void shift_register_right_arithmetically(void* args) {
}
// SRA [HL]
void shift_value_at_hl_address_right_arithmetically(void* args) {
}
// SRL r8
void shift_register_right_logically(void* args) {
}
// SRL [HL]
void shift_value_at_hl_address_right_logically(void* args) {
}
// SWAP r8
void swap_register_nibbles(void* args) {
}
// SWAP [HL]
void swap_value_at_hl_address_nibbles(void* args) {
}

// Jump and Subroutine instructions
// CALL n16
void push_next_address_to_stack(void* args) {
}
// CALL cc,n16
void push_next_address_to_stack_conditionally(void* args) {
}
// JP HL
void jump_to_value_at_hl_address(void* args) {
}
// JP n16
void jump_to_immediate(void* args) {
}
// JP cc,n16
void jump_to_immediate_conditionally(void* args) {
}
// JR n16
void jump_relative_to_immediate(void* args);
// JR cc,n16
void jump_relative_to_immediate_conditionally(void* args) {
}
// RET cc
void return_from_subroutine_conditionally(void* args) {
}
// RET
void return_from_subroutine(void* args) {
}
// RETI
void return_from_interrupt_subroutine(void* args) {
}
// RST vec
void call_address(void* args) {
}

// Carry Flag Instructions
// CCF
void invert_carry_flag(void* args) {
}
// SCF
void set_carry_flag(void* args) {
}

// Stack instructions
// ADD HL,SP
void add_hl_to_sp(void* args) {
}
// ADD SP,e8
void add_signed_immediate_to_sp(void* args);
// DEC SP
void decrement_sp(void* args) {
}
// INC SP
void increment_sp(void* args) {
}
// LD SP,n16
void load_sp_from_immediate_16bit(void* args) {
}
// LD [n16],SP
void store_sp_at_immediate_address(void* args) {
}
// LD HL,SP+e8
void load_hl_from_sp_plus_signed_immediate(void* args);
// LD SP,HL
void copy_hl_to_sp(void* args) {
}
// POP AF
void pop_stack_to_af(void* args) {
}
// POP r16
void pop_stack_to_16bit_register(void* args) {
}
// PUSH AF
void push_af_to_stack(void* args) {
}
// PUSH r16
void push_16bit_register_to_stack(void* args) {
}

// Interrupt Instructions
// DI
void disable_interrupts(void* args) {
}
// EI
void enable_interrupts(void* args) {
}
// HALT
void halt(void* args) {
}

// Miscellaneous
// DAA
void decimal_adjust_accumulator(void* args);
// NOP
void nop(void* args);
// STOP
void stop(void* args);
