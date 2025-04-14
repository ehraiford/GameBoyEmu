#pragma once
#include "../executors/Cpu.h"
#include <array>
#include <tuple>
#include <variant>

typedef void (Cpu::*NoArgs)();
typedef void (Cpu::*OneU8)(uint8_t*);
typedef void (Cpu::*ImmU8)(uint8_t);
typedef void (Cpu::*ImmAndPtr)(uint8_t, uint8_t*);
typedef void (Cpu::*TwoU8)(uint8_t*, uint8_t*);
typedef void (Cpu::*OneU16)(uint16_t*);
typedef void (Cpu::*TwoU16)(uint16_t*, uint16_t*);
typedef void (Cpu::*ConU16)(Condition, uint16_t*);
typedef void (Cpu::*OneI8)(int8_t*);
typedef void (Cpu::*ConI8)(Condition, int8_t*);
typedef void (Cpu::*ConU8)(Condition, uint8_t*);
typedef void (Cpu::*Con)(Condition);

using OpFunc = std::variant<NoArgs, OneU8, TwoU8, ImmU8, ImmAndPtr, OneU16, TwoU16, ConU16, OneI8, ConI8, ConU8, Con>;

struct OpCode {
  public:
	OpFunc opfunc;
	uint8_t cycles;
	uint8_t bytes;
};

struct JumpTableEntry {
	void (*execute)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
	uint8_t cycles;
	uint8_t bytes;
};

struct CurrentOperation {
	void (*execute)(Cpu*, uint8_t*);
	uint8_t total_cycles;
	uint8_t remaining_cycles;
	uint8_t length;
	std::array<uint8_t, 3> bytes;
	std::string disassembly;
};

static OpCode copy = OpCode(&Cpu::copy, 1, 1);
static OpCode load_immediate_8bit = OpCode(&Cpu::load_immediate_8bit, 2, 2);
static OpCode load_immediate_16bit = OpCode(&Cpu::load_immediate_16bit, 3, 3);
static OpCode store_at_hl_address = OpCode(&Cpu::store_at_hl_address, 2, 1);
static OpCode store_immediate_at_hl_address = OpCode(&Cpu::store_immediate_at_hl_address, 3, 2);
static OpCode load_from_hl_address = OpCode(&Cpu::load_from_hl_address, 2, 1);
static OpCode store_a_at_register_address = OpCode(&Cpu::store_a_at_register_address, 2, 1);
static OpCode store_a_at_immediate_address = OpCode(&Cpu::store_a_at_immediate_address, 4, 3);
static OpCode store_a_at_immediate_hardware_address = OpCode(&Cpu::store_a_at_immediate_hardware_address, 3, 2);
static OpCode store_a_at_hardware_address_offset_by_c = OpCode(&Cpu::store_a_at_hardware_address_offset_by_c, 2, 1);
static OpCode load_a_from_register_address = OpCode(&Cpu::load_a_from_register_address, 2, 1);
static OpCode load_a_from_immediate_address = OpCode(&Cpu::load_a_from_immediate_address, 4, 3);
static OpCode load_a_from_immediate_hardware_address = OpCode(&Cpu::load_a_from_immediate_hardware_address, 3, 2);
static OpCode load_a_from_hardware_address_offset_by_c = OpCode(&Cpu::load_a_from_hardware_address_offset_by_c, 2, 1);
static OpCode store_a_at_hl_address_increment = OpCode(&Cpu::store_a_at_hl_address_increment, 2, 1);
static OpCode store_a_at_hl_address_decrement = OpCode(&Cpu::store_a_at_hl_address_decrement, 2, 1);
static OpCode load_a_from_hl_address_increment = OpCode(&Cpu::load_a_from_hl_address_increment, 2, 1);
static OpCode load_a_from_hl_address_decrement = OpCode(&Cpu::load_a_from_hl_address_decrement, 2, 1);

static OpCode add_with_carry_register_to_a = OpCode(&Cpu::add_with_carry_register_to_a, 1, 1);
static OpCode add_with_carry_from_hl_address_to_a = OpCode(&Cpu::add_with_carry_from_hl_address_to_a, 2, 1);
static OpCode add_with_carry_immediate_to_a = OpCode(&Cpu::add_with_carry_immediate_to_a, 2, 2);
static OpCode add_register_to_a = OpCode(&Cpu::add_register_to_a, 1, 1);
static OpCode add_value_at_hl_address_to_a = OpCode(&Cpu::add_value_at_hl_address_to_a, 2, 1);
static OpCode add_immediate_to_a = OpCode(&Cpu::add_immediate_to_a, 2, 2);
static OpCode compare_a_with_register = OpCode(&Cpu::compare_a_with_register, 1, 1);
static OpCode compare_a_with_value_at_hl_address = OpCode(&Cpu::compare_a_with_value_at_hl_address, 2, 1);
static OpCode compare_a_with_immediate = OpCode(&Cpu::compare_a_with_immediate, 2, 2);
static OpCode decrement_register = OpCode(&Cpu::decrement_register, 1, 1);
static OpCode decrement_value_at_hl_address = OpCode(&Cpu::decrement_value_at_hl_address, 3, 1);
static OpCode increment_register = OpCode(&Cpu::increment_register, 1, 1);
static OpCode increment_value_at_hl_address = OpCode(&Cpu::increment_value_at_hl_address, 3, 1);
static OpCode subtract_with_carry_register_from_a = OpCode(&Cpu::subtract_with_carry_register_from_a, 1, 1);
static OpCode subtract_with_carry_value_at_hl_address_from_a =
	OpCode(&Cpu::subtract_with_carry_value_at_hl_address_from_a, 2, 1);
static OpCode subtract_with_carry_immediate_from_a = OpCode(&Cpu::subtract_with_carry_immediate_from_a, 2, 2);
static OpCode subtract_register_from_a = OpCode(&Cpu::subtract_register_from_a, 1, 1);
static OpCode subtract_value_at_hl_address_from_a = OpCode(&Cpu::subtract_value_at_hl_address_from_a, 2, 1);
static OpCode subtract_immediate_from_a = OpCode(&Cpu::subtract_immediate_from_a, 2, 2);
static OpCode add_16bit_register_to_HL = OpCode(&Cpu::add_16bit_register_to_HL, 2, 1);
static OpCode decrement_16bit_register = OpCode(&Cpu::decrement_16bit_register, 2, 1);
static OpCode increment_16bit_register = OpCode(&Cpu::increment_16bit_register, 2, 1);
static OpCode and_a_with_register = OpCode(&Cpu::and_a_with_register, 1, 1);
static OpCode and_a_with_value_at_hl_address = OpCode(&Cpu::and_a_with_value_at_hl_address, 2, 1);
static OpCode and_a_with_immediate = OpCode(&Cpu::and_a_with_immediate, 2, 2);
static OpCode invert_a = OpCode(&Cpu::invert_a, 1, 1);
static OpCode or_a_with_register = OpCode(&Cpu::or_a_with_register, 1, 1);
static OpCode or_a_with_value_at_hl_address = OpCode(&Cpu::or_a_with_value_at_hl_address, 2, 1);
static OpCode or_a_with_immediate = OpCode(&Cpu::or_a_with_immediate, 2, 2);
static OpCode xor_a_with_register = OpCode(&Cpu::xor_a_with_register, 1, 1);
static OpCode xor_a_with_value_at_hl_address = OpCode(&Cpu::xor_a_with_value_at_hl_address, 2, 1);
static OpCode xor_a_with_immediate = OpCode(&Cpu::xor_a_with_immediate, 2, 2);
static OpCode set_zflag_if_register_bit_not_set = OpCode(&Cpu::set_zflag_if_register_bit_not_set, 2, 2);
static OpCode set_zflag_if_value_at_hl_address_bit_not_set =
	OpCode(&Cpu::set_zflag_if_value_at_hl_address_bit_not_set, 3, 2);
static OpCode clear_register_bit = OpCode(&Cpu::clear_register_bit, 2, 2);
static OpCode set_register_bit = OpCode(&Cpu::set_register_bit, 2, 2);
static OpCode clear_value_at_hl_address_bit = OpCode(&Cpu::clear_value_at_hl_address_bit, 4, 2);
static OpCode set_value_at_hl_address_bit = OpCode(&Cpu::set_value_at_hl_address_bit, 4, 2);
static OpCode rotate_register_left = OpCode(&Cpu::rotate_register_left, 2, 2);
static OpCode rotate_value_at_hl_address_left = OpCode(&Cpu::rotate_value_at_hl_address_left, 4, 2);
static OpCode rotate_a_left = OpCode(&Cpu::rotate_a_left, 1, 1);
static OpCode rotate_register_left_with_carry = OpCode(&Cpu::rotate_register_left_with_carry, 2, 2);
static OpCode rotate_value_at_hl_address_left_with_carry =
	OpCode(&Cpu::rotate_value_at_hl_address_left_with_carry, 4, 2);
static OpCode rotate_a_left_with_carry = OpCode(&Cpu::rotate_a_left_with_carry, 1, 1);
static OpCode rotate_register_right = OpCode(&Cpu::rotate_register_right, 2, 2);
static OpCode rotate_value_at_hl_address_right = OpCode(&Cpu::rotate_value_at_hl_address_right, 4, 2);
static OpCode rotate_a_right = OpCode(&Cpu::rotate_a_right, 1, 1);
static OpCode rotate_register_right_with_carry = OpCode(&Cpu::rotate_register_right_with_carry, 2, 2);
static OpCode rotate_value_at_hl_address_right_with_carry =
	OpCode(&Cpu::rotate_value_at_hl_address_right_with_carry, 4, 2);
static OpCode rotate_a_right_with_carry = OpCode(&Cpu::rotate_a_right_with_carry, 1, 1);
static OpCode shift_register_left_arithmetically = OpCode(&Cpu::shift_register_left_arithmetically, 2, 2);
static OpCode shift_value_at_hl_address_left_arithmetically =
	OpCode(&Cpu::shift_value_at_hl_address_left_arithmetically, 4, 2);
static OpCode shift_register_right_arithmetically = OpCode(&Cpu::shift_register_right_arithmetically, 2, 2);
static OpCode shift_value_at_hl_address_right_arithmetically =
	OpCode(&Cpu::shift_value_at_hl_address_right_arithmetically, 4, 2);
static OpCode shift_register_right_logically = OpCode(&Cpu::shift_register_right_logically, 2, 2);
static OpCode shift_value_at_hl_address_right_logically = OpCode(&Cpu::shift_value_at_hl_address_right_logically, 4, 2);
static OpCode swap_register_nibbles = OpCode(&Cpu::swap_register_nibbles, 2, 2);
static OpCode swap_value_at_hl_address_nibbles = OpCode(&Cpu::swap_value_at_hl_address_nibbles, 4, 2);
static OpCode call = OpCode(&Cpu::call, 6, 3);
static OpCode call_conditionally = OpCode(&Cpu::call_conditionally, 6, 3);
static OpCode jump_to_value_at_hl_address = OpCode(&Cpu::jump_to_value_at_hl_address, 1, 1);
static OpCode jump_to_immediate = OpCode(&Cpu::jump_to_immediate, 4, 3);
static OpCode jump_to_immediate_conditionally = OpCode(&Cpu::jump_to_immediate_conditionally, 4, 3);
static OpCode jump_relative_to_immediate = OpCode(&Cpu::jump_relative_to_immediate, 3, 2);
static OpCode jump_relative_to_immediate_conditionally = OpCode(&Cpu::jump_relative_to_immediate_conditionally, 3, 2);
static OpCode return_from_subroutine_conditionally = OpCode(&Cpu::return_from_subroutine_conditionally, 5, 1);
static OpCode return_from_subroutine = OpCode(&Cpu::return_from_subroutine, 4, 1);
static OpCode return_from_interrupt_subroutine = OpCode(&Cpu::return_from_interrupt_subroutine, 4, 1);
static OpCode call_vec = OpCode(&Cpu::call_vec, 4, 1);
static OpCode invert_carry_flag = OpCode(&Cpu::invert_carry_flag, 1, 1);
static OpCode set_carry_flag = OpCode(&Cpu::set_carry_flag, 1, 1);
static OpCode add_sp_to_hl = OpCode(&Cpu::add_sp_to_hl, 2, 1);
static OpCode add_signed_immediate_to_sp = OpCode(&Cpu::add_signed_immediate_to_sp, 4, 2);
static OpCode decrement_sp = OpCode(&Cpu::decrement_sp, 2, 1);
static OpCode increment_sp = OpCode(&Cpu::increment_sp, 2, 1);
static OpCode load_sp_from_immediate_16bit = OpCode(&Cpu::load_sp_from_immediate_16bit, 3, 3);
static OpCode store_sp_at_immediate_address = OpCode(&Cpu::store_sp_at_immediate_address, 5, 3);
static OpCode load_hl_from_sp_plus_signed_immediate = OpCode(&Cpu::load_hl_from_sp_plus_signed_immediate, 3, 2);
static OpCode copy_hl_to_sp = OpCode(&Cpu::copy_hl_to_sp, 2, 1);
static OpCode pop_stack_to_af = OpCode(&Cpu::pop_stack_to_af, 3, 1);
static OpCode pop_stack_to_16bit_register = OpCode(&Cpu::pop_stack_to_16bit_register, 3, 1);
static OpCode push_af_to_stack = OpCode(&Cpu::push_af_to_stack, 4, 1);
static OpCode push_16bit_register_to_stack = OpCode(&Cpu::push_16bit_register_to_stack, 4, 1);
static OpCode disable_interrupts = OpCode(&Cpu::disable_interrupts, 1, 1);
static OpCode enable_interrupts = OpCode(&Cpu::enable_interrupts, 1, 1);
static OpCode halt = OpCode(&Cpu::halt, 0, 1);
static OpCode decimal_adjust_accumulator = OpCode(&Cpu::decimal_adjust_accumulator, 1, 1);
static OpCode nop = OpCode(&Cpu::nop, 1, 1);
static OpCode stop = OpCode(&Cpu::stop, 0, 2);
static OpCode unsupported_op = OpCode(&Cpu::unsupported_op, 0, 1);
static std::array<JumpTableEntry, 256> jump_table = {
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->nop();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "NOP";
		},
		nop.cycles,
		nop.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_16bit(cpu->get_bc_pointer(), reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "BC";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		load_immediate_16bit.cycles,
		load_immediate_16bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_register_address(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [BC]";
		},
		store_a_at_register_address.cycles,
		store_a_at_register_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_16bit_register(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC BC";
		},
		increment_16bit_register.cycles,
		increment_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC B";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC B";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_b_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "B";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_a_left_with_carry();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLCA";
		},
		rotate_a_left_with_carry.cycles,
		rotate_a_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_sp_at_immediate_address(reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "SP ";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		store_sp_at_immediate_address.cycles,
		store_sp_at_immediate_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_16bit_register_to_HL(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD BC";
		},
		add_16bit_register_to_HL.cycles,
		add_16bit_register_to_HL.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_register_address(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,[BC]";
		},
		load_a_from_register_address.cycles,
		load_a_from_register_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_16bit_register(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC BC";
		},
		decrement_16bit_register.cycles,
		decrement_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC C";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC C";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_c_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "C";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_a_right_with_carry();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRCA";
		},
		rotate_a_right_with_carry.cycles,
		rotate_a_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->stop();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "STOP";
		},
		stop.cycles,
		stop.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_16bit(cpu->get_de_pointer(), reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "DE";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		load_immediate_16bit.cycles,
		load_immediate_16bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_register_address(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [DE]";
		},
		store_a_at_register_address.cycles,
		store_a_at_register_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_16bit_register(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC DE";
		},
		increment_16bit_register.cycles,
		increment_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC D";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC D";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_d_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "D";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_a_left();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLA";
		},
		rotate_a_left.cycles,
		rotate_a_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_relative_to_immediate(reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JR ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		jump_relative_to_immediate.cycles,
		jump_relative_to_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_16bit_register_to_HL(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD DE";
		},
		add_16bit_register_to_HL.cycles,
		add_16bit_register_to_HL.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_register_address(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,[DE]";
		},
		load_a_from_register_address.cycles,
		load_a_from_register_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_16bit_register(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC DE";
		},
		decrement_16bit_register.cycles,
		decrement_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC E";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC E";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_e_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "E";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_a_right();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRA";
		},
		rotate_a_right.cycles,
		rotate_a_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_relative_to_immediate_conditionally(Condition::NZ, reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JR ";
			string += "NZ";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		jump_relative_to_immediate_conditionally.cycles,
		jump_relative_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_16bit(cpu->get_hl_pointer(), reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "HL";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		load_immediate_16bit.cycles,
		load_immediate_16bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_hl_address_increment();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HLI],A";
		},
		store_a_at_hl_address_increment.cycles,
		store_a_at_hl_address_increment.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_16bit_register(cpu->get_hl_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC HL";
		},
		increment_16bit_register.cycles,
		increment_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC H";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC H";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_h_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "H";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decimal_adjust_accumulator();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DAA";
		},
		decimal_adjust_accumulator.cycles,
		decimal_adjust_accumulator.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_relative_to_immediate_conditionally(Condition::Z, reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JR ";
			string += "Z";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		jump_relative_to_immediate_conditionally.cycles,
		jump_relative_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_16bit_register_to_HL(cpu->get_hl_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD HL";
		},
		add_16bit_register_to_HL.cycles,
		add_16bit_register_to_HL.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_hl_address_increment();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,[HLI]";
		},
		load_a_from_hl_address_increment.cycles,
		load_a_from_hl_address_increment.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_16bit_register(cpu->get_hl_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC HL";
		},
		decrement_16bit_register.cycles,
		decrement_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC L";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC L";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_l_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "L";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->invert_a();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CPL";
		},
		invert_a.cycles,
		invert_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_relative_to_immediate_conditionally(Condition::NC, reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JR ";
			string += "NC";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		jump_relative_to_immediate_conditionally.cycles,
		jump_relative_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_16bit(cpu->get_sp_pointer(), reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "SP";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		load_immediate_16bit.cycles,
		load_immediate_16bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_hl_address_decrement();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HLD],A";
		},
		store_a_at_hl_address_decrement.cycles,
		store_a_at_hl_address_decrement.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_16bit_register(cpu->get_sp_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC SP";
		},
		increment_16bit_register.cycles,
		increment_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC [HL]";
		},
		increment_value_at_hl_address.cycles,
		increment_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC [HL]";
		},
		decrement_value_at_hl_address.cycles,
		decrement_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_immediate_at_hl_address(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "[HL]";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		store_immediate_at_hl_address.cycles,
		store_immediate_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_carry_flag();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SCF";
		},
		set_carry_flag.cycles,
		set_carry_flag.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_relative_to_immediate_conditionally(Condition::C, reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JR ";
			string += "C";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		jump_relative_to_immediate_conditionally.cycles,
		jump_relative_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_16bit_register_to_HL(cpu->get_sp_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD SP";
		},
		add_16bit_register_to_HL.cycles,
		add_16bit_register_to_HL.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_hl_address_decrement();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,[HLD]";
		},
		load_a_from_hl_address_decrement.cycles,
		load_a_from_hl_address_decrement.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_16bit_register(cpu->get_sp_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC SP";
		},
		decrement_16bit_register.cycles,
		decrement_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->increment_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "INC A";
		},
		increment_register.cycles,
		increment_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->decrement_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DEC A";
		},
		decrement_register.cycles,
		decrement_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_immediate_8bit(cpu->get_a_pointer(), instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "A";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		load_immediate_8bit.cycles,
		load_immediate_8bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->invert_carry_flag();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CCF";
		},
		invert_carry_flag.cycles,
		invert_carry_flag.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_b_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD B,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_c_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD C,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_d_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD D,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_e_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD E,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_h_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD H,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_l_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD L,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],B";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],C";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],D";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],E";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],H";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],L";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->halt();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "HALT";
		},
		halt.cycles,
		halt.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_at_hl_address(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD [HL],A";
		},
		store_at_hl_address.cycles,
		store_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,B";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,C";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,D";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,E";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,H";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,L";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_from_hl_address(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A";
		},
		load_from_hl_address.cycles,
		load_from_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy(cpu->get_a_pointer(), cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD A,A";
		},
		copy.cycles,
		copy.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD B";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD C";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD D";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD E";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD H";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD L";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_value_at_hl_address_to_a();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD A,[HL]";
		},
		add_value_at_hl_address_to_a.cycles,
		add_value_at_hl_address_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_register_to_a(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADD A";
		},
		add_register_to_a.cycles,
		add_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC B";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC C";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC D";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC E";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC H";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC L";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_from_hl_address_to_a();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC A,[HL]";
		},
		add_with_carry_from_hl_address_to_a.cycles,
		add_with_carry_from_hl_address_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_register_to_a(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "ADC A";
		},
		add_with_carry_register_to_a.cycles,
		add_with_carry_register_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB B";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB C";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB D";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB E";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB H";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB L";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_value_at_hl_address_from_a();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB A,[HL]";
		},
		subtract_value_at_hl_address_from_a.cycles,
		subtract_value_at_hl_address_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_register_from_a(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SUB A";
		},
		subtract_register_from_a.cycles,
		subtract_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC B";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC C";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC D";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC E";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC H";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC L";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_value_at_hl_address_from_a();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC A,[HL]";
		},
		subtract_with_carry_value_at_hl_address_from_a.cycles,
		subtract_with_carry_value_at_hl_address_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_register_from_a(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SBC A";
		},
		subtract_with_carry_register_from_a.cycles,
		subtract_with_carry_register_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND B";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND C";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND D";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND E";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND H";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND L";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND A,[HL]";
		},
		and_a_with_value_at_hl_address.cycles,
		and_a_with_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "AND A";
		},
		and_a_with_register.cycles,
		and_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR B";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR C";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR D";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR E";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR H";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR L";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR A,[HL]";
		},
		xor_a_with_value_at_hl_address.cycles,
		xor_a_with_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "XOR A";
		},
		xor_a_with_register.cycles,
		xor_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR B";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR C";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR D";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR E";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR H";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR L";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR A,[HL]";
		},
		or_a_with_value_at_hl_address.cycles,
		or_a_with_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "OR A";
		},
		or_a_with_register.cycles,
		or_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP B";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP C";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP D";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP E";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP H";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP L";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP A,[HL]";
		},
		compare_a_with_value_at_hl_address.cycles,
		compare_a_with_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_register(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CP A";
		},
		compare_a_with_register.cycles,
		compare_a_with_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_subroutine_conditionally(Condition::NZ);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RET NZ";
		},
		return_from_subroutine_conditionally.cycles,
		return_from_subroutine_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->pop_stack_to_16bit_register(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "POP BC";
		},
		pop_stack_to_16bit_register.cycles,
		pop_stack_to_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_immediate_conditionally(Condition::NZ, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JP ";
			string += "NZ";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		jump_to_immediate_conditionally.cycles,
		jump_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_immediate(reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JP ";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		jump_to_immediate.cycles,
		jump_to_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_conditionally(Condition::NZ, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CALL ";
			string += "NZ";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		call_conditionally.cycles,
		call_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->push_16bit_register_to_stack(cpu->get_bc_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "PUSH BC";
		},
		push_16bit_register_to_stack.cycles,
		push_16bit_register_to_stack.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_immediate_to_a(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "ADD ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		add_immediate_to_a.cycles,
		add_immediate_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(0);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 0);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_subroutine_conditionally(Condition::Z);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RET Z";
		},
		return_from_subroutine_conditionally.cycles,
		return_from_subroutine_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_subroutine();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RET";
		},
		return_from_subroutine.cycles,
		return_from_subroutine.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_immediate_conditionally(Condition::Z, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JP ";
			string += "Z";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		jump_to_immediate_conditionally.cycles,
		jump_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->nop();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "CB INSTRUCTION";
		},
		nop.cycles,
		nop.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_conditionally(Condition::Z, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CALL ";
			string += "Z";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		call_conditionally.cycles,
		call_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call(reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CALL ";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		call.cycles,
		call.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_with_carry_immediate_to_a(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "ADC ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		add_with_carry_immediate_to_a.cycles,
		add_with_carry_immediate_to_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 1);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_subroutine_conditionally(Condition::NC);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RET NC";
		},
		return_from_subroutine_conditionally.cycles,
		return_from_subroutine_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->pop_stack_to_16bit_register(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "POP DE";
		},
		pop_stack_to_16bit_register.cycles,
		pop_stack_to_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_immediate_conditionally(Condition::NC, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JP ";
			string += "NC";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		jump_to_immediate_conditionally.cycles,
		jump_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_conditionally(Condition::NC, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CALL ";
			string += "NC";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		call_conditionally.cycles,
		call_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->push_16bit_register_to_stack(cpu->get_de_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "PUSH DE";
		},
		push_16bit_register_to_stack.cycles,
		push_16bit_register_to_stack.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_immediate_from_a(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "SUB ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		subtract_immediate_from_a.cycles,
		subtract_immediate_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(2);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 2);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_subroutine_conditionally(Condition::C);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RET C";
		},
		return_from_subroutine_conditionally.cycles,
		return_from_subroutine_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->return_from_interrupt_subroutine();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RETI";
		},
		return_from_interrupt_subroutine.cycles,
		return_from_interrupt_subroutine.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_immediate_conditionally(Condition::C, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "JP ";
			string += "C";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		jump_to_immediate_conditionally.cycles,
		jump_to_immediate_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_conditionally(Condition::C, reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CALL ";
			string += "C";
			string += ",";
			string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		call_conditionally.cycles,
		call_conditionally.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->subtract_with_carry_immediate_from_a(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "SBC ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		subtract_with_carry_immediate_from_a.cycles,
		subtract_with_carry_immediate_from_a.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(3);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 3);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_immediate_hardware_address(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LDH ";
			string += std::format("[${:02x}]", static_cast<int>(bytes[1]));
			string += ",";
			string += "A";
			return string;
		},
		store_a_at_immediate_hardware_address.cycles,
		store_a_at_immediate_hardware_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->pop_stack_to_16bit_register(cpu->get_hl_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "POP HL";
		},
		pop_stack_to_16bit_register.cycles,
		pop_stack_to_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_hardware_address_offset_by_c();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LDH [C],A";
		},
		store_a_at_hardware_address_offset_by_c.cycles,
		store_a_at_hardware_address_offset_by_c.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->push_16bit_register_to_stack(cpu->get_hl_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "PUSH HL";
		},
		push_16bit_register_to_stack.cycles,
		push_16bit_register_to_stack.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->and_a_with_immediate(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "AND ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		and_a_with_immediate.cycles,
		and_a_with_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(4);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 4);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->add_signed_immediate_to_sp(reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "ADD ";
			string += "SP";
			string += ",";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		add_signed_immediate_to_sp.cycles,
		add_signed_immediate_to_sp.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->jump_to_value_at_hl_address();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "JP [HL]";
		},
		jump_to_value_at_hl_address.cycles,
		jump_to_value_at_hl_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->store_a_at_immediate_address(reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += std::format("[${:04x}]", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			string += ",";
			string += "A";
			return string;
		},
		store_a_at_immediate_address.cycles,
		store_a_at_immediate_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->xor_a_with_immediate(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "XOR ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		xor_a_with_immediate.cycles,
		xor_a_with_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(5);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 5);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_immediate_hardware_address(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LDH ";
			string += "A";
			string += ",";
			string += std::format("[${:02x}]", static_cast<int>(bytes[1]));
			return string;
		},
		load_a_from_immediate_hardware_address.cycles,
		load_a_from_immediate_hardware_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->pop_stack_to_16bit_register(cpu->get_af_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "POP AF";
		},
		pop_stack_to_16bit_register.cycles,
		pop_stack_to_16bit_register.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_hardware_address_offset_by_c();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LDH A,[C]";
		},
		load_a_from_hardware_address_offset_by_c.cycles,
		load_a_from_hardware_address_offset_by_c.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->disable_interrupts();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "DI";
		},
		disable_interrupts.cycles,
		disable_interrupts.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->push_16bit_register_to_stack(cpu->get_af_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "PUSH AF";
		},
		push_16bit_register_to_stack.cycles,
		push_16bit_register_to_stack.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->or_a_with_immediate(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "OR ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		or_a_with_immediate.cycles,
		or_a_with_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(6);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 6);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_hl_from_sp_plus_signed_immediate(reinterpret_cast<int8_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "HL";
			string += ",";
			string += std::format("SP + {}", static_cast<int>(bytes[1]));
			return string;
		},
		load_hl_from_sp_plus_signed_immediate.cycles,
		load_hl_from_sp_plus_signed_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->copy_hl_to_sp();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "LD SP,HL";
		},
		copy_hl_to_sp.cycles,
		copy_hl_to_sp.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->load_a_from_immediate_address(reinterpret_cast<uint16_t*>(instr_ptr + 1));
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "LD ";
			string += "A";
			string += ",";
			string += std::format("[${:04x}]", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
			return string;
		},
		load_a_from_immediate_address.cycles,
		load_a_from_immediate_address.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->enable_interrupts();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "EI";
		},
		enable_interrupts.cycles,
		enable_interrupts.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->unsupported_op();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "";
		},
		unsupported_op.cycles,
		unsupported_op.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->compare_a_with_immediate(instr_ptr + 1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "CP ";
			string += std::format("${:02x}", static_cast<int>(bytes[1]));
			return string;
		},
		compare_a_with_immediate.cycles,
		compare_a_with_immediate.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->call_vec(7);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			std::string string = "RST ";
			string += std::format("{:02x}", 7);
			return string;
		},
		call_vec.cycles,
		call_vec.bytes,
	},
};
static std::array<JumpTableEntry, 256> jump_table_cb = {
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC B";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC C";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC D";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC E";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC H";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC L";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_value_at_hl_address_left_with_carry();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC [HL]";
		},
		rotate_value_at_hl_address_left_with_carry.cycles,
		rotate_value_at_hl_address_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left_with_carry(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RLC A";
		},
		rotate_register_left_with_carry.cycles,
		rotate_register_left_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC B";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC C";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC D";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC E";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC H";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC L";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_value_at_hl_address_right_with_carry();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC [HL]";
		},
		rotate_value_at_hl_address_right_with_carry.cycles,
		rotate_value_at_hl_address_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right_with_carry(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RRC A";
		},
		rotate_register_right_with_carry.cycles,
		rotate_register_right_with_carry.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL B";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL C";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL D";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL E";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL H";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL L";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_value_at_hl_address_left();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL [HL]";
		},
		rotate_value_at_hl_address_left.cycles,
		rotate_value_at_hl_address_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_left(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RL A";
		},
		rotate_register_left.cycles,
		rotate_register_left.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR B";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR C";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR D";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR E";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR H";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR L";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_value_at_hl_address_right();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR [HL]";
		},
		rotate_value_at_hl_address_right.cycles,
		rotate_value_at_hl_address_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->rotate_register_right(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RR A";
		},
		rotate_register_right.cycles,
		rotate_register_right.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA B";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA C";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA D";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA E";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA H";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA L";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_value_at_hl_address_left_arithmetically();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA [HL]";
		},
		shift_value_at_hl_address_left_arithmetically.cycles,
		shift_value_at_hl_address_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_left_arithmetically(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SLA A";
		},
		shift_register_left_arithmetically.cycles,
		shift_register_left_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA B";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA C";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA D";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA E";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA H";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA L";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_value_at_hl_address_right_arithmetically();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA [HL]";
		},
		shift_value_at_hl_address_right_arithmetically.cycles,
		shift_value_at_hl_address_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_arithmetically(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA A";
		},
		shift_register_right_arithmetically.cycles,
		shift_register_right_arithmetically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP B";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP C";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP D";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP E";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP H";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP L";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_value_at_hl_address_nibbles();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP HL";
		},
		swap_value_at_hl_address_nibbles.cycles,
		swap_value_at_hl_address_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->swap_register_nibbles(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SWAP A";
		},
		swap_register_nibbles.cycles,
		swap_register_nibbles.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA B";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA C";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA D";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA E";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA H";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA L";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_value_at_hl_address_right_logically();
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRL [HL]";
		},
		shift_value_at_hl_address_right_logically.cycles,
		shift_value_at_hl_address_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->shift_register_right_logically(cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SRA A";
		},
		shift_register_right_logically.cycles,
		shift_register_right_logically.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(0);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(0, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 0,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(1, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 1,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(2);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(2, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 2,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(3);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(3, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 3,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(4);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(4, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 4,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(5);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(5, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 5,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(6);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(6, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 6,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,B";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,C";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,D";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,E";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,H";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,L";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_value_at_hl_address_bit_not_set(7);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,[HL]";
		},
		set_zflag_if_value_at_hl_address_bit_not_set.cycles,
		set_zflag_if_value_at_hl_address_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_zflag_if_register_bit_not_set(7, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "BIT 7,A";
		},
		set_zflag_if_register_bit_not_set.cycles,
		set_zflag_if_register_bit_not_set.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(0);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(0, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 0,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(1, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 1,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(2);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(2, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 2,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(3);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(3, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 3,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(4);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(4, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 4,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(5);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(5, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 5,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(6);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(6, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 6,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,B";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,C";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,D";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,E";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,H";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,L";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_value_at_hl_address_bit(7);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,[HL]";
		},
		clear_value_at_hl_address_bit.cycles,
		clear_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->clear_register_bit(7, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "RES 7,A";
		},
		clear_register_bit.cycles,
		clear_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(0);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(0, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 0,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(1);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(1, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 1,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(2);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(2, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 2,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(3);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(3, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 3,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(4);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(4, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 4,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(5);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(5, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 5,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(6);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(6, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 6,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_b_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,B";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_c_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,C";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_d_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,D";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_e_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,E";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_h_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,H";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_l_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,L";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_value_at_hl_address_bit(7);
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,[HL]";
		},
		set_value_at_hl_address_bit.cycles,
		set_value_at_hl_address_bit.bytes,
	},
	JumpTableEntry{
		[](Cpu* cpu, uint8_t* instr_ptr) -> void {
			cpu->set_register_bit(7, cpu->get_a_pointer());
		},
		[](std::array<uint8_t, 3> bytes) -> const std::string {
			return "SET 7,A";
		},
		set_register_bit.cycles,
		set_register_bit.bytes,
	},
};