#include "Cpu.h"
#include <iostream>

uint16_t Cpu::get_hl() {
	return (this->h << 8) | this->l;
};
void Cpu::set_hl(uint16_t value) {
	this->h = value >> 8;
	this->l = value;
};

bool Cpu::get_flag(Flag flag) {
	return this->f & flag;
};

void Cpu::push_to_stack(uint16_t value) {
	this->sp -= 1;
	this->ram->set_memory(this->sp, value >> 8);
	this->sp -= 1;
	this->ram->set_memory(this->sp, value);
};
uint16_t Cpu::pop_from_stack() {
	uint16_t value = this->ram->get_memory(this->sp);
	this->sp += 1;
	value <<= 8;
	value |= this->ram->get_memory(this->sp);
	this->sp += 1;
	return value;
}

void Cpu::set_flag(Flag flag, bool value) {
	this->f = value ? (this->f | flag) : (this->f & ~flag);
};
// Sets the flags in the standard way for a standard addition operation.
void Cpu::set_flags_addition(uint16_t op0, uint16_t op1, uint16_t result) {
	this->set_flag(Flag::Z_FLAG, (result & 0x00FF));
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, (op0 & 0x0F) + (op1 & 0x0F) > 0x0F);
	this->set_flag(Flag::C_FLAG, result > 0xFF);
};
// Sets the flags in the standard way for a standard subtraction operation.
void Cpu::set_flags_subtraction(uint16_t op0, uint16_t op1, uint16_t result) {
	this->set_flag(Flag::Z_FLAG, (result & 0x00FF));
	this->set_flag(Flag::N_FLAG, true);
	this->set_flag(Flag::H_FLAG, (op0 & 0x0F) < (op1 & 0x0F));
	this->set_flag(Flag::C_FLAG, op0 < op1);
};
bool Cpu::condition_is_met(Condition condition) {
	switch (condition) {
	case NZ:
		return this->get_flag(Flag::Z_FLAG) == false;
	case Z:
		return this->get_flag(Flag::Z_FLAG) == true;
	case NC:
		return this->get_flag(Flag::C_FLAG) == false;
	default:
		return this->get_flag(Flag::C_FLAG) == true;
	};
}

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
	this->interrupts_enabled = false;
};
Cpu::~Cpu() {};

uint8_t *Cpu::get_b_pointer() {
	return &this->b;
};
uint8_t *Cpu::get_c_pointer() {
	return &this->c;
};
uint8_t *Cpu::get_d_pointer() {
	return &this->d;
};
uint8_t *Cpu::get_e_pointer() {
	return &this->e;
};
uint8_t *Cpu::get_f_pointer() {
	return &this->f;
};
uint8_t *Cpu::get_a_pointer() {
	return &this->a;
};
uint8_t *Cpu::get_h_pointer() {
	return &this->h;
};
uint8_t *Cpu::get_l_pointer() {
	return &this->l;
};

uint16_t *Cpu::get_bc_pointer() {
	return reinterpret_cast<uint16_t *>(&this->b);
}
uint16_t *Cpu::get_de_pointer() {
	return reinterpret_cast<uint16_t *>(&this->d);
}
uint16_t *Cpu::get_af_pointer() {
	return reinterpret_cast<uint16_t *>(&this->a);
}
uint16_t *Cpu::get_hl_pointer() {
	return reinterpret_cast<uint16_t *>(&this->h);
}
uint16_t *Cpu::get_sp_pointer() {
	return &this->sp;
}

// OPCODES

// LD r8,r8
void Cpu::copy(void *args) {
	uint8_t *dest = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *(reinterpret_cast<uint8_t *>(args) + sizeof(uint8_t *));
	*dest = value;
};
// LD r8,n8
void Cpu::load_immediate_8bit(void *args) {
	uint8_t *dest = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *(reinterpret_cast<uint8_t *>(args) + sizeof(uint8_t *));
	*dest = value;
};
// LD r16,n16
void Cpu::load_immediate_16bit(void *args) {
	uint16_t *dest = reinterpret_cast<uint16_t *>(args);
	uint16_t value = *(reinterpret_cast<uint16_t *>(args) + sizeof(uint16_t *));
	*dest = value;
};
// LD [HL],r8
void Cpu::store_at_hl_address(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->ram->set_memory(this->get_hl(), value);
};
// LD [HL],n8
void Cpu::store_immediate_at_hl_address(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->ram->set_memory(this->get_hl(), value);
};
// LD r8,[HL]
void Cpu::load_from_hl_address(void *args) {
	uint8_t *dest = reinterpret_cast<uint8_t *>(args);
	*dest = this->ram->get_memory(this->get_hl());
};
// LD [r16],A
void Cpu::store_a_at_register_address(void *args) {
	uint16_t address = *reinterpret_cast<uint16_t *>(args);
	this->ram->set_memory(address, this->a);
};
// LD [n16],A
void Cpu::store_a_at_immediate_address(void *args) {
	uint16_t address = *reinterpret_cast<uint16_t *>(args);
	this->ram->set_memory(address, this->a);
};
// LDH [n16],A
void Cpu::store_a_at_immediate_hardware_address(void *args) {
	uint8_t addr_low = *reinterpret_cast<uint8_t *>(args);
	this->ram->set_memory(0xFF00 | addr_low, this->a);
};
// LDH [C],A
void Cpu::store_a_at_hardware_address_offset_by_c(void *args) {
	this->ram->set_memory(0xFF00 | this->c, this->a);
};
// LD A,[r16]
void Cpu::load_a_from_register_address(void *args) {
	uint16_t address = *reinterpret_cast<uint16_t *>(args);
	this->a = this->ram->get_memory(address);
};
// LD A,[r16]
void Cpu::load_a_from_immediate_address(void *args) {
	uint16_t address = *reinterpret_cast<uint16_t *>(args);
	this->a = this->ram->get_memory(address);
};
// LDH A,[n16]
void Cpu::load_a_from_immediate_hardware_address(void *args) {
	uint8_t *addr_low = reinterpret_cast<uint8_t *>(args);
	this->a = this->ram->get_memory(0xFF00 | *addr_low);
};
// LDH A,[C]
void Cpu::load_a_from_hardware_address_offset_by_c(void *args) {
	this->a = this->ram->get_memory(0xFF00 | this->c);
};
// LD [HLI],A
void Cpu::store_a_at_hl_address_increment(void *args) {
	uint16_t hl = this->get_hl();
	this->ram->set_memory(hl, this->a);
	hl++;
	this->h = hl >> 8;
	this->l = hl;
};
// LD [HLD],A
void Cpu::store_a_at_hl_address_decrement(void *args) {
	uint16_t hl = this->get_hl();
	this->ram->set_memory(hl, this->a);
	hl--;
	this->h = hl >> 8;
	this->l = hl;
};
// LD A,[HLI]
void Cpu::load_a_from_hl_address_increment(void *args) {
	uint16_t hl = this->get_hl();
	this->a = this->ram->get_memory(hl);
	hl++;
	this->h = hl >> 8;
	this->l = hl;
};
// LD A,[HLD]
void Cpu::load_a_from_hl_address_decrement(void *args) {
	uint16_t hl = this->get_hl();
	this->a = this->ram->get_memory(hl);
	hl--;
	this->h = hl >> 8;
	this->l = hl;
};

// 8-bit arithmetic instructions
// ADC A,r8
void Cpu::add_with_carry_register_to_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args) + ((this->get_flag(Flag::C_FLAG) << 8));
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};

// ADC A,[HL]
void Cpu::add_with_carry_from_hl_address_to_a(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};

// ADC A,n8
void Cpu::add_with_carry_immediate_to_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args) + (this->get_flag(Flag::C_FLAG) << 8);
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};

// ADD A,r8
void Cpu::add_register_to_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};
// ADD A,[HL]
void Cpu::add_value_at_hl_address_to_a(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};
// ADD A,n8
void Cpu::add_immediate_to_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint16_t result = this->a + value;

	this->set_flags_addition(this->a, value, result);
	this->a = result;
};
// CP A,r8
void Cpu::compare_a_with_register(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
};
// CP A,[HL]
void Cpu::compare_a_with_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory((this->h << 8) | this->l);
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
};
// CP A,n8
void Cpu::compare_a_with_immediate(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
};
// DEC r8
void Cpu::decrement_register(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t result = *reg - 1;

	this->set_flag(Flag::Z_FLAG, result == 0);
	this->set_flag(Flag::N_FLAG, true);
	this->set_flag(Flag::H_FLAG, (*reg & 0x0F) == 0);
	*reg = result;
};
// DEC [HL]
void Cpu::decrement_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	uint8_t result = value - 1;

	this->set_flag(Flag::Z_FLAG, result == 0);
	this->set_flag(Flag::N_FLAG, true);
	this->set_flag(Flag::H_FLAG, (value & 0x0F) == 0);
	this->ram->set_memory(this->get_hl(), result);
};
// INC r8
void Cpu::increment_register(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t result = *reg + 1;

	this->set_flag(Flag::Z_FLAG, result == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, (*reg & 0x0F) == 0x0F);
	*reg = result;
};
// INC [HL]
void Cpu::increment_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	uint8_t result = value + 1;

	this->set_flag(Flag::Z_FLAG, result == 0);
	this->set_flag(Flag::N_FLAG, true);
	this->set_flag(Flag::H_FLAG, (value & 0x0F) == 0x0F);
	this->ram->set_memory(this->get_hl(), result);
};
// SBC A,r8
void Cpu::subtract_with_carry_register_from_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args) + ((this->get_flag(Flag::C_FLAG) << 8));
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};
// SBC A,[HL]
void Cpu::subtract_with_carry_value_at_hl_address_from_a(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl()) + ((this->get_flag(Flag::C_FLAG) << 8));
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};
// SBC A,n8
void Cpu::subtract_with_carry_immediate_from_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args) + ((this->get_flag(Flag::C_FLAG) << 8));
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};
// SUB A,r8
void Cpu::subtract_register_from_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};
// SUB A,[HL]
void Cpu::subtract_value_at_hl_address_from_a(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};
// SUB A,n8
void Cpu::subtract_immediate_from_a(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	uint8_t result = this->a - value;

	this->set_flags_subtraction(this->a, value, result);
	this->a = result;
};

// 16-bit arithmetic operations
// ADD HL,r16
void Cpu::add_16bit_register_to_HL(void *args) {
	uint16_t value = *reinterpret_cast<uint16_t *>(args);
	uint32_t result = this->get_hl() + value;

	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, ((this->get_hl() & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);
	this->set_flag(Flag::C_FLAG, result > 0xFFFF);
	this->set_hl(result);
};
// DEC r16
void Cpu::decrement_16bit_register(void *args) {
	uint16_t *reg = reinterpret_cast<uint16_t *>(args);
	*reg -= 1;
};
// INC r16
void Cpu::increment_16bit_register(void *args) {
	uint16_t *reg = reinterpret_cast<uint16_t *>(args);
	*reg += 1;
};

// Bitwise logic instructions
// AND A,r8
void Cpu::and_a_with_register(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a &= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, true);
	this->set_flag(Flag::C_FLAG, false);
};
// AND A,[HL]
void Cpu::and_a_with_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	this->a &= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, true);
	this->set_flag(Flag::C_FLAG, false);
};
// AND A,n8
void Cpu::and_a_with_immediate(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a &= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, true);
	this->set_flag(Flag::C_FLAG, false);
};
// CPL
void Cpu::invert_a(void *args) {
	this->a = ~this->a;

	this->set_flag(Flag::N_FLAG, true);
	this->set_flag(Flag::H_FLAG, true);
};
// OR A,r8
void Cpu::or_a_with_register(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a |= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};
// OR A,[HL]
void Cpu::or_a_with_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	this->a |= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};
// OR A,n8
void Cpu::or_a_with_immediate(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a |= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};
// XOR A,r8
void Cpu::xor_a_with_register(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a ^= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};
// XOR A,[HL]
void Cpu::xor_a_with_value_at_hl_address(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	this->a ^= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};
// XOR A,n8
void Cpu::xor_a_with_immediate(void *args) {
	uint8_t value = *reinterpret_cast<uint8_t *>(args);
	this->a ^= value;

	this->set_flag(Flag::Z_FLAG, this->a == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, false);
};

// Bitflag instructions
// BIT u3,r8
void Cpu::set_zflag_if_register_bit_not_set(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t reg_value = *(reinterpret_cast<uint8_t *>(args) + sizeof(uint8_t));
	this->set_flag(Flag::Z_FLAG, (reg_value & (1 << bit_position)) == 0);

	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, true);
};
// BIT u3,[HL]
void Cpu::set_zflag_if_value_at_hl_address_bit_not_set(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t value = this->ram->get_memory(this->get_hl());

	this->set_flag(Flag::Z_FLAG, (value & (1 << bit_position)) == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, true);
};
// RES u3,r8
void Cpu::clear_register_bit(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t *reg = reinterpret_cast<uint8_t *>(args) + sizeof(uint8_t *);
	*reg &= ~(1 << bit_position);
};
// RES u3,[HL]
void Cpu::clear_value_at_hl_address_bit(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t value = this->ram->get_memory(this->get_hl());
	value &= ~(1 << bit_position);
	this->ram->set_memory(this->get_hl(), value);
};
// SET u3,r8
void Cpu::set_register_bit(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t *reg = reinterpret_cast<uint8_t *>(args) + sizeof(uint8_t);
	*reg |= 1 << bit_position;
};
// SET u3,[HL]
void Cpu::set_value_at_hl_address_bit(void *args) {
	uint8_t bit_position = *reinterpret_cast<uint8_t *>(args);
	uint8_t value = this->ram->get_memory(this->get_hl());
	value |= 1 << bit_position;
	this->ram->set_memory(this->get_hl(), value);
};

// Bit shift instructions
// RL r8
void Cpu::rotate_register_left(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;
	bool new_carry = value & 0b10000000;

	value <<= 1;
	value &= 0b11111110;
	value |= this->get_flag(Flag::C_FLAG);

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// RL [HL]
void Cpu::rotate_value_at_hl_address_left(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	bool new_carry = value & 0b10000000;

	value <<= 1;
	value &= 0b11111110;
	value |= this->get_flag(Flag::C_FLAG);

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// RLA
void Cpu::rotate_a_left(void *args) {
	uint8_t a = this->a;

	bool new_carry = this->a & 0b10000000;
	a <<= 1;
	a &= 0b11111110;
	a |= this->get_flag(Flag::C_FLAG);

	this->set_flag(Flag::Z_FLAG, false);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->a = a;
};
// RLC r8
void Cpu::rotate_register_left_with_carry(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;
	bool new_carry = value & 0b10000000;

	value <<= 1;
	value &= 0b11111110;
	value |= new_carry;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// RLC [HL]
void Cpu::rotate_value_at_hl_address_left_with_carry(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	bool new_carry = value & 0b10000000;

	value <<= 1;
	value &= 0b11111110;
	value |= new_carry;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// RLCA
void Cpu::rotate_a_left_with_carry(void *args) {
	uint8_t a = this->a;

	bool new_carry = this->a & 0b10000000;
	a <<= 1;
	a &= 0b11111110;
	a |= new_carry;

	this->set_flag(Flag::Z_FLAG, false);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->a = a;
};
// RR r8
void Cpu::rotate_register_right(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;
	bool new_carry = value & 0b1;

	value >>= 1;
	value &= 0b01111111;
	value |= this->get_flag(Flag::C_FLAG) << 7;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// RR [HL]
void Cpu::rotate_value_at_hl_address_right(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	bool new_carry = value & 0b1;

	value >>= 1;
	value &= 0b01111111;
	value |= this->get_flag(Flag::C_FLAG) << 7;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// RRA
void Cpu::rotate_a_right(void *args) {
	uint8_t a = this->a;

	bool new_carry = this->a & 0b1;
	a >>= 1;
	a &= 0b01111111;
	a |= this->get_flag(Flag::C_FLAG) << 7;

	this->set_flag(Flag::Z_FLAG, false);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->a = a;
};
// RRC r8
void Cpu::rotate_register_right_with_carry(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;
	bool new_carry = value & 0b1;

	value >>= 1;
	value &= 0b01111111;
	value |= new_carry << 7;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// RRC [HL]
void Cpu::rotate_value_at_hl_address_right_with_carry(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());
	bool new_carry = value & 0b1;

	value >>= 1;
	value &= 0b01111111;
	value |= new_carry << 7;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// RRCA
void Cpu::rotate_a_right_with_carry(void *args) {
	uint8_t a = this->a;

	bool new_carry = this->a & 0b1;
	a >>= 1;
	a &= 0b01111111;
	a |= new_carry << 7;

	this->set_flag(Flag::Z_FLAG, false);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->a = a;
};
// SLA r8
void Cpu::shift_register_left_arithmetically(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;

	bool new_carry = value & 0b10000000;
	value <<= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// SLA [HL]
void Cpu::shift_value_at_hl_address_left_arithmetically(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());

	bool new_carry = value & 0b10000000;
	value <<= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// SRA r8
void Cpu::shift_register_right_arithmetically(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	int8_t value = *reg;

	bool new_carry = value & 0b1;
	value >>= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// SRA [HL]
void Cpu::shift_value_at_hl_address_right_arithmetically(void *args) {
	int8_t value = this->ram->get_memory(this->get_hl());

	bool new_carry = value & 0b1;
	value >>= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// SRL r8
void Cpu::shift_register_right_logically(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;

	bool new_carry = value & 0b1;
	value >>= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	*reg = value;
};
// SRL [HL]
void Cpu::shift_value_at_hl_address_right_logically(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());

	bool new_carry = value & 0b1;
	value >>= 1;

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, new_carry);
	this->ram->set_memory(this->get_hl(), value);
};
// SWAP r8
void Cpu::swap_register_nibbles(void *args) {
	uint8_t *reg = reinterpret_cast<uint8_t *>(args);
	uint8_t value = *reg;

	value = (value << 4) | (value >> 4);

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, 0);
	this->set_flag(Flag::H_FLAG, 0);
	this->set_flag(Flag::C_FLAG, 0);
};
// SWAP [HL]
void Cpu::swap_value_at_hl_address_nibbles(void *args) {
	uint8_t value = this->ram->get_memory(this->get_hl());

	value = (value << 4) | (value >> 4);

	this->set_flag(Flag::Z_FLAG, value == 0);
	this->set_flag(Flag::N_FLAG, 0);
	this->set_flag(Flag::H_FLAG, 0);
	this->set_flag(Flag::C_FLAG, 0);
	this->ram->set_memory(this->get_hl(), value);
};

// Jump and Subroutine instructions
// CALL n16
void Cpu::call(void *args) {
	uint16_t call_address = *reinterpret_cast<uint16_t *>(args);
	uint16_t pc = this->pc;

	this->push_to_stack(pc);
	this->pc = call_address;
};
// CALL cc,n16
void Cpu::call_conditionally(void *args) {
	uint8_t cond_int = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(args));
	Condition condition = static_cast<Condition>(cond_int);

	if (this->condition_is_met(condition)) {
		this->call(reinterpret_cast<int16_t *>(args) + sizeof(Condition));
	}
};
// JP HL
void Cpu::jump_to_value_at_hl_address(void *args) {
	this->pc = this->get_hl();
};
// JP n16
void Cpu::jump_to_immediate(void *args) {
	uint16_t value = *reinterpret_cast<uint16_t *>(args);
	this->pc = value;
};
// JP cc,n16
void Cpu::jump_to_immediate_conditionally(void *args) {
	uint8_t cond_int = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(args));
	Condition condition = static_cast<Condition>(cond_int);

	if (this->condition_is_met(condition)) {
		this->jump_to_immediate(reinterpret_cast<int16_t *>(args) + sizeof(Condition));
	}
};
// JR n16
void Cpu::jump_relative_to_immediate(void *args) {
	int16_t offset = *reinterpret_cast<int8_t *>(args);
	this->pc += offset;
};
// JR cc,n16
void Cpu::jump_relative_to_immediate_conditionally(void *args) {
	uint8_t cond_int = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(args));
	Condition condition = static_cast<Condition>(cond_int);

	if (this->condition_is_met(condition)) {
		this->jump_relative_to_immediate(reinterpret_cast<int8_t *>(args) + sizeof(Condition));
	}
};
// RET
void Cpu::return_from_subroutine(void *args) {
	this->pc = this->pop_from_stack();
};
// RET cc
void Cpu::return_from_subroutine_conditionally(void *args) {
	uint8_t cond_int = static_cast<std::uint8_t>(reinterpret_cast<std::uintptr_t>(args));
	Condition condition = static_cast<Condition>(cond_int);

	if (this->condition_is_met(condition)) {
		this->return_from_subroutine(nullptr);
	}
};
// RETI
void Cpu::return_from_interrupt_subroutine(void *args) {
	// TODO: change emulator state to pending interrupt enable
	this->return_from_subroutine(args);
};
// RST vec
void Cpu::call_vec(void *args) {
	uint8_t address = *reinterpret_cast<uint8_t *>(args);
	uint16_t pc = this->pc;

	this->push_to_stack(pc);
	this->pc = address;
};

// Carry Flag Instructions
// CCF
void Cpu::invert_carry_flag(void *args) {
	this->set_flag(Flag::C_FLAG, ~this->get_flag(Flag::C_FLAG));
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
};
// SCF
void Cpu::set_carry_flag(void *args) {
	this->set_flag(Flag::C_FLAG, true);
	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, false);
};

// Stack instructions
// ADD HL,SP
void Cpu::add_sp_to_hl(void *args) {
	uint16_t value = this->sp;
	uint32_t result = this->get_hl() + value;

	this->set_flag(Flag::N_FLAG, false);
	this->set_flag(Flag::H_FLAG, ((this->get_hl() & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF);
	this->set_flag(Flag::C_FLAG, result > 0xFFFF);
	this->set_hl(result);
};
// ADD SP,e8
void Cpu::add_signed_immediate_to_sp(void *args) {
	int8_t immediate = *reinterpret_cast<int8_t *>(args);
	uint16_t result = this->sp + immediate;

	this->set_flags_addition(this->sp, immediate, result);
	this->sp = result;
};
// DEC SP
void Cpu::decrement_sp(void *args) {
	this->sp -= 1;
};
// INC SP
void Cpu::increment_sp(void *args) {
	this->sp += 1;
};
// LD SP,n16
void Cpu::load_sp_from_immediate_16bit(void *args) {
	uint16_t value = *reinterpret_cast<uint16_t *>(args);
	this->sp = value;
};
// LD [n16],SP
void Cpu::store_sp_at_immediate_address(void *args) {
	uint16_t address = *reinterpret_cast<uint16_t *>(args);
	this->ram->set_memory(address, this->sp);
	this->ram->set_memory(address + 1, this->sp >> 8);
};
// LD HL,SP+e8
void Cpu::load_hl_from_sp_plus_signed_immediate(void *args) {
	int8_t value = *reinterpret_cast<int8_t *>(args);
	uint16_t result = this->sp + value;

	this->set_flags_addition(this->sp, value, result);
	this->set_hl(result);
};
// LD SP,HL
void Cpu::copy_hl_to_sp(void *args) {
	this->sp = this->get_hl();
};
// POP AF
void Cpu::pop_stack_to_af(void *args) {
	uint16_t value = this->pop_from_stack();
	this->a = value >> 8;
	this->f = value & 0xF0;
};
// POP r16
void Cpu::pop_stack_to_16bit_register(void *args) {
	uint16_t *dest = reinterpret_cast<uint16_t *>(args);
	uint16_t value = this->pop_from_stack();
	*dest = value;
};
// PUSH AF
void Cpu::push_af_to_stack(void *args) {
	uint16_t value = (this->a << 8) | this->f;
	this->push_to_stack(value);
};
// PUSH r16
void Cpu::push_16bit_register_to_stack(void *args) {
	uint16_t *reg = reinterpret_cast<uint16_t *>(args);
	this->push_to_stack(*reg);
};

// Interrupt Instructions
// DI
void Cpu::disable_interrupts(void *args) {
	// TODO
};
// EI
void Cpu::enable_interrupts(void *args) {
	// TODO
};
// HALT
void Cpu::halt(void *args) {
	// TODO
};

// Miscellaneous
// DAA
void Cpu::decimal_adjust_accumulator(void *args) {
	uint8_t adjustment = 0;
	uint16_t result = 0;
	if (this->get_flag(Flag::N_FLAG)) {
		if (this->get_flag(Flag::H_FLAG)) {
			adjustment += 0x6;
		}
		if (this->get_flag(Flag::C_FLAG)) {
			adjustment += 0x60;
		}
		result = this->a - adjustment;
	} else {
		if (this->get_flag(Flag::H_FLAG) || (this->a & 0xF) > 0x9) {
			adjustment += 0x6;
		}
		if (this->get_flag(Flag::C_FLAG) || this->a > 0x99) {
			adjustment += 0x60;
		}
		result = this->a + adjustment;
	}

	this->set_flag(Flag::Z_FLAG, result == 0);
	this->set_flag(Flag::H_FLAG, false);
	this->set_flag(Flag::C_FLAG, result > 0xFF);
	this->a = result;
};
// NOP
void Cpu::nop(void *args) {};
// STOP
void Cpu::stop(void *args) {
	// TODO
};
void Cpu::unsupported_op(void *args) {};