#ifndef OPCODES_H
#define OPCODES_H
#include "../core/Cpu.h"
#include <array>

typedef void (Cpu::*OpFunc)(void *);
class OpCode {
	OpFunc op_func;
	uint8_t cycles;
	uint8_t bytes;

  public:
	OpCode(OpFunc func, uint8_t cycles, uint8_t bytes) : op_func(func), cycles(cycles), bytes(bytes) {};

	void execute(Cpu *cpu, void *args);
	uint8_t get_length();
	uint8_t get_cycles();
};

struct JumpTableEntry {
	OpCode *op_code;
	void *(*get_arguments)(Cpu *, uint8_t *);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
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

constexpr std::array<JumpTableEntry, 256> jump_table = {
	JumpTableEntry{&nop,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "NOP";
				   }},
	JumpTableEntry{&load_immediate_16bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint16_t *, uint16_t *>(cpu->get_bc_pointer(),
																		  reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += "BC";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&store_a_at_register_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD BC";
				   }},
	JumpTableEntry{&increment_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC BC";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC B";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC B";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B";
				   }},
	JumpTableEntry{&rotate_a_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLCA";
				   }},
	JumpTableEntry{&store_sp_at_immediate_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<uint16_t *>(instr_ptr + 1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "SP ";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&add_16bit_register_to_HL,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD BC";
				   }},
	JumpTableEntry{&load_a_from_register_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD BC";
				   }},
	JumpTableEntry{&decrement_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC BC";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC C";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC C";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C";
				   }},
	JumpTableEntry{&rotate_a_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRCA";
				   }},
	JumpTableEntry{&stop,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "STOP";
				   }},
	JumpTableEntry{&load_immediate_16bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint16_t *, uint16_t *>(cpu->get_de_pointer(),
																		  reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += "DE";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&store_a_at_register_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD DE";
				   }},
	JumpTableEntry{&increment_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC DE";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC D";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC D";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D";
				   }},
	JumpTableEntry{&rotate_a_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLA";
				   }},
	JumpTableEntry{&jump_relative_to_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JR ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&add_16bit_register_to_HL,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD DE";
				   }},
	JumpTableEntry{&load_a_from_register_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD DE";
				   }},
	JumpTableEntry{&decrement_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC DE";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC E";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC E";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E";
				   }},
	JumpTableEntry{&rotate_a_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRA";
				   }},
	JumpTableEntry{&jump_relative_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint8_t *>(Condition::NZ, instr_ptr + 1);
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JR ";
					   string += "NZ";
					   string += ",";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&load_immediate_16bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint16_t *, uint16_t *>(cpu->get_hl_pointer(),
																		  reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += "HL";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&store_a_at_hl_address_increment,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HLI],A";
				   }},
	JumpTableEntry{&increment_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_hl_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC HL";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC H";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC H";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H";
				   }},
	JumpTableEntry{&decimal_adjust_accumulator,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DAA";
				   }},
	JumpTableEntry{&jump_relative_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint8_t *>(Condition::Z, instr_ptr + 1);
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JR ";
					   string += "Z";
					   string += ",";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&add_16bit_register_to_HL,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_hl_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD HL";
				   }},
	JumpTableEntry{&load_a_from_hl_address_increment,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,[HLI]";
				   }},
	JumpTableEntry{&decrement_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_hl_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC HL";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC L";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC L";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L";
				   }},
	JumpTableEntry{&invert_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CPL";
				   }},
	JumpTableEntry{&jump_relative_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint8_t *>(Condition::NC, instr_ptr + 1);
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JR ";
					   string += "NC";
					   string += ",";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&load_immediate_16bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint16_t *, uint16_t *>(cpu->get_sp_pointer(),
																		  reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += "SP";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&store_a_at_hl_address_decrement,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HLD],A";
				   }},
	JumpTableEntry{&increment_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_sp_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC SP";
				   }},
	JumpTableEntry{&increment_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC [HL]";
				   }},
	JumpTableEntry{&decrement_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC [HL]";
				   }},
	JumpTableEntry{&store_immediate_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += "[HL]";
					   string += ",";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&set_carry_flag,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SCF";
				   }},
	JumpTableEntry{&jump_relative_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint8_t *>(Condition::C, instr_ptr + 1);
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JR ";
					   string += "C";
					   string += ",";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&add_16bit_register_to_HL,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_sp_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD SP";
				   }},
	JumpTableEntry{&load_a_from_hl_address_decrement,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,[HLD]";
				   }},
	JumpTableEntry{&decrement_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_sp_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC SP";
				   }},
	JumpTableEntry{&increment_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "INC A";
				   }},
	JumpTableEntry{&decrement_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DEC A";
				   }},
	JumpTableEntry{&load_immediate_8bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A";
				   }},
	JumpTableEntry{&invert_carry_flag,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CCF";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_b_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD B,A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_c_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD C,A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_d_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD D,A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_e_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD E,A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_h_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD H,A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_l_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD L,A";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],B";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],C";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],D";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],E";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],H";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],L";
				   }},
	JumpTableEntry{&halt,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "HALT";
				   }},
	JumpTableEntry{&store_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD [HL],A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,B";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,C";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,D";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,E";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,H";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,L";
				   }},
	JumpTableEntry{&load_from_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A";
				   }},
	JumpTableEntry{&copy,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t *, uint8_t *>(cpu->get_a_pointer(), cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD A,A";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD B";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD C";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD D";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD E";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD H";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD L";
				   }},
	JumpTableEntry{&add_value_at_hl_address_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD A,[HL]";
				   }},
	JumpTableEntry{&add_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADD A";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC B";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC C";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC D";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC E";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC H";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC L";
				   }},
	JumpTableEntry{&add_with_carry_from_hl_address_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC A,[HL]";
				   }},
	JumpTableEntry{&add_with_carry_register_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "ADC A";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB B";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB C";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB D";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB E";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB H";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB L";
				   }},
	JumpTableEntry{&subtract_value_at_hl_address_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB A,[HL]";
				   }},
	JumpTableEntry{&subtract_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SUB A";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC B";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC C";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC D";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC E";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC H";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC L";
				   }},
	JumpTableEntry{&subtract_with_carry_value_at_hl_address_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC A,[HL]";
				   }},
	JumpTableEntry{&subtract_with_carry_register_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SBC A";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND B";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND C";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND D";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND E";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND H";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND L";
				   }},
	JumpTableEntry{&and_a_with_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND A,[HL]";
				   }},
	JumpTableEntry{&and_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "AND A";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR B";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR C";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR D";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR E";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR H";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR L";
				   }},
	JumpTableEntry{&xor_a_with_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR A,[HL]";
				   }},
	JumpTableEntry{&xor_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "XOR A";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR B";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR C";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR D";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR E";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR H";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR L";
				   }},
	JumpTableEntry{&or_a_with_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR A,[HL]";
				   }},
	JumpTableEntry{&or_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "OR A";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP B";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP C";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP D";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP E";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP H";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP L";
				   }},
	JumpTableEntry{&compare_a_with_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP A,[HL]";
				   }},
	JumpTableEntry{&compare_a_with_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CP A";
				   }},
	JumpTableEntry{&return_from_subroutine_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(Condition::NZ);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RET NZ";
				   }},
	JumpTableEntry{&pop_stack_to_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "POP BC";
				   }},
	JumpTableEntry{&jump_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::NZ,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JP ";
					   string += "NZ";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&jump_to_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<uint16_t *>(instr_ptr + 1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JP ";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::NZ,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CALL ";
					   string += "NZ";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&push_16bit_register_to_stack,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_bc_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "PUSH BC";
				   }},
	JumpTableEntry{&add_immediate_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "ADD ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(0));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 0);
					   return string;
				   }},
	JumpTableEntry{&return_from_subroutine_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(Condition::Z);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RET Z";
				   }},
	JumpTableEntry{&return_from_subroutine,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RET";
				   }},
	JumpTableEntry{&jump_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::Z,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JP ";
					   string += "Z";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&nop,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "CB INSTRUCTION";
				   }},
	JumpTableEntry{&call_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::Z,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CALL ";
					   string += "Z";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<uint16_t *>(instr_ptr + 1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CALL ";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&add_with_carry_immediate_to_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "ADC ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(1));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 1);
					   return string;
				   }},
	JumpTableEntry{&return_from_subroutine_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(Condition::NC);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RET NC";
				   }},
	JumpTableEntry{&pop_stack_to_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "POP DE";
				   }},
	JumpTableEntry{&jump_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::NC,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JP ";
					   string += "NC";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&call_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::NC,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CALL ";
					   string += "NC";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&push_16bit_register_to_stack,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_de_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "PUSH DE";
				   }},
	JumpTableEntry{&subtract_immediate_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "SUB ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(2));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 2);
					   return string;
				   }},
	JumpTableEntry{&return_from_subroutine_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(Condition::C);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RET C";
				   }},
	JumpTableEntry{&return_from_interrupt_subroutine,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RETI";
				   }},
	JumpTableEntry{&jump_to_immediate_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::C,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "JP ";
					   string += "C";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&call_conditionally,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<Condition, uint16_t *>(Condition::C,
																		 reinterpret_cast<uint16_t *>(instr_ptr + 1));
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CALL ";
					   string += "C";
					   string += ",";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&subtract_with_carry_immediate_from_a,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "SBC ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(3));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 3);
					   return string;
				   }},
	JumpTableEntry{&store_a_at_immediate_hardware_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LDH ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&pop_stack_to_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_hl_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "POP HL";
				   }},
	JumpTableEntry{&store_a_at_hardware_address_offset_by_c,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LDH";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&push_16bit_register_to_stack,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_hl_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "PUSH HL";
				   }},
	JumpTableEntry{&and_a_with_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "AND ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(4));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 4);
					   return string;
				   }},
	JumpTableEntry{&add_signed_immediate_to_sp,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "ADD ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&jump_to_value_at_hl_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "JP";
				   }},
	JumpTableEntry{&store_a_at_immediate_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<uint16_t *>(instr_ptr + 1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&xor_a_with_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "XOR ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(5));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 5);
					   return string;
				   }},
	JumpTableEntry{&load_a_from_immediate_hardware_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LDH ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&pop_stack_to_16bit_register,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_af_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "POP AF";
				   }},
	JumpTableEntry{&load_a_from_hardware_address_offset_by_c,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LDH";
				   }},
	JumpTableEntry{&disable_interrupts,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "DI";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&push_16bit_register_to_stack,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_af_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "PUSH AF";
				   }},
	JumpTableEntry{&or_a_with_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "OR ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(6));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 6);
					   return string;
				   }},
	JumpTableEntry{&load_hl_from_sp_plus_signed_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "LD ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&copy_hl_to_sp,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD";
				   }},
	JumpTableEntry{&load_a_from_immediate_address,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "LD";
				   }},
	JumpTableEntry{&enable_interrupts,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "EI";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&unsupported_op,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "";
				   }},
	JumpTableEntry{&compare_a_with_immediate,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return instr_ptr + 1;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "CP ";
					   string += std::format("${:02x}", static_cast<int>(bytes[1]));
					   return string;
				   }},
	JumpTableEntry{&call_vec,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(reinterpret_cast<void *>(7));
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   std::string string = "RST ";
					   string += std::format("{:02x}", 7);
					   return string;
				   }},
};
constexpr std::array<JumpTableEntry, 256> jump_table_cb = {
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC B";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC C";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC D";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC E";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC H";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC L";
				   }},
	JumpTableEntry{&rotate_value_at_hl_address_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC [HL]";
				   }},
	JumpTableEntry{&rotate_register_left_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RLC A";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC B";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC C";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC D";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC E";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC H";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC L";
				   }},
	JumpTableEntry{&rotate_value_at_hl_address_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC [HL]";
				   }},
	JumpTableEntry{&rotate_register_right_with_carry,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RRC A";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL B";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL C";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL D";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL E";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL H";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL L";
				   }},
	JumpTableEntry{&rotate_value_at_hl_address_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL [HL]";
				   }},
	JumpTableEntry{&rotate_register_left,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RL A";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR B";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR C";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR D";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR E";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR H";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR L";
				   }},
	JumpTableEntry{&rotate_value_at_hl_address_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR [HL]";
				   }},
	JumpTableEntry{&rotate_register_right,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RR A";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA B";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA C";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA D";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA E";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA H";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA L";
				   }},
	JumpTableEntry{&shift_value_at_hl_address_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA [HL]";
				   }},
	JumpTableEntry{&shift_register_left_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SLA A";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA B";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA C";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA D";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA E";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA H";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA L";
				   }},
	JumpTableEntry{&shift_value_at_hl_address_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA [HL]";
				   }},
	JumpTableEntry{&shift_register_right_arithmetically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA A";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP B";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP C";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP D";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP E";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP H";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP L";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP";
				   }},
	JumpTableEntry{&swap_register_nibbles,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SWAP A";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_b_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA B";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_c_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA C";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_d_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA D";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_e_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA E";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_h_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA H";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_l_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA L";
				   }},
	JumpTableEntry{&shift_value_at_hl_address_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return nullptr;
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRL [HL]";
				   }},
	JumpTableEntry{&shift_register_right_logically,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return cpu->get_a_pointer();
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SRA A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(0);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 0,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 1,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(2);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 2,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(3);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 3,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(4);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 4,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(5);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 5,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(6);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 6,A";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,B";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,C";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,D";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,E";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,H";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,L";
				   }},
	JumpTableEntry{&set_zflag_if_value_at_hl_address_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(7);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,[HL]";
				   }},
	JumpTableEntry{&set_zflag_if_register_bit_not_set,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "BIT 7,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(0);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 0,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 1,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(2);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 2,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(3);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 3,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(4);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 4,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(5);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 5,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(6);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 6,A";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,B";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,C";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,D";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,E";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,H";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,L";
				   }},
	JumpTableEntry{&clear_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(7);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,[HL]";
				   }},
	JumpTableEntry{&clear_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "RES 7,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(0);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(0, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 0,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(1);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(1, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 1,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(2);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(2, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 2,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(3);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(3, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 3,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(4);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(4, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 4,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(5);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(5, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 5,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(6);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(6, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 6,A";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_b_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,B";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_c_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,C";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_d_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,D";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_e_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,E";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_h_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,H";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_l_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,L";
				   }},
	JumpTableEntry{&set_value_at_hl_address_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   return reinterpret_cast<void *>(7);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,[HL]";
				   }},
	JumpTableEntry{&set_register_bit,
				   [](Cpu *cpu, uint8_t *instr_ptr) -> void * {
					   auto *args = new std::pair<uint8_t, uint8_t *>(7, cpu->get_a_pointer());
					   return static_cast<void *>(args);
				   },
				   [](std::array<uint8_t, 3> bytes) -> const std::string {
					   return "SET 7,A";
				   }},
};

#endif // OPCODES_H
