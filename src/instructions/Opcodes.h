#pragma once
#include "../executors/Cpu.h"
#include <array>
#include <tuple>
#include <variant>

typedef void (Cpu::*NoArgs)();
typedef void (Cpu::*OneU8)(uint8_t*);
typedef void (Cpu::*TwoU8)(uint8_t*, uint8_t*);
typedef void (Cpu::*OneU16)(uint16_t*);
typedef void (Cpu::*TwoU16)(uint16_t*, uint16_t*);
typedef void (Cpu::*ConU16)(Condition*, uint16_t*);
typedef void (Cpu::*OneI8)(int8_t*);
typedef void (Cpu::*ConI8)(Condition*, int8_t*);
typedef void (Cpu::*ConU8)(Condition*, uint8_t*);
typedef void (Cpu::*Con)(Condition*);

using OpFunc = std::variant<NoArgs, OneU8, TwoU8, OneU16, TwoU16, ConU16, OneI8, ConI8, ConU8, Con>;
using FuncArgs =
	std::variant<std::monostate, uint8_t, uint8_t*, std::tuple<uint8_t*, uint8_t*>, std::tuple<uint8_t, uint8_t*>,
				 uint16_t*, std::tuple<uint16_t*, uint16_t*>, std::tuple<Condition, uint16_t*>, int8_t*,
				 std::tuple<Condition, int8_t*>, std::tuple<Condition, uint8_t*>, Condition>;

class OpCode {
	OpFunc opfunc;
	uint8_t cycles;
	uint8_t bytes;

  public:
	OpCode(OpFunc func, uint8_t cycles, uint8_t bytes) : opfunc(func), cycles(cycles), bytes(bytes) {};

	void virtual execute(Cpu* cpu, FuncArgs args) = 0;
	uint8_t get_length();
	uint8_t get_cycles();
};
class NoArgCode : public OpCode {
	NoArgs opfunc;

  public:
	NoArgCode(NoArgs func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class OneU8Code : public OpCode {
	OneU8 opfunc;

  public:
	OneU8Code(OneU8 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class TwoU8Code : public OpCode {
	TwoU8 opfunc;

  public:
	TwoU8Code(TwoU8 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class OneU16Code : public OpCode {
	OneU16 opfunc;

  public:
	OneU16Code(OneU16 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class TwoU16Code : public OpCode {
	TwoU16 opfunc;

  public:
	TwoU16Code(TwoU16 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class ConU16Code : public OpCode {
	ConU16 opfunc;

  public:
	ConU16Code(ConU16 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class OneI8Code : public OpCode {
	OneI8 opfunc;

  public:
	OneI8Code(OneI8 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class ConI8Code : public OpCode {
	ConI8 opfunc;

  public:
	ConI8Code(ConI8 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class ConU8Code : public OpCode {
	ConU8 opfunc;

  public:
	ConU8Code(ConU8 func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};
class ConCode : public OpCode {
	Con opfunc;

  public:
	ConCode(Con func, uint8_t cycles, uint8_t bytes) : OpCode(func, cycles, bytes), opfunc(func) {
	}
	void execute(Cpu* cpu, FuncArgs args) override;
};

struct JumpTableEntry {
	OpCode* op_code;
	FuncArgs (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};

struct NoArgEntry : JumpTableEntry {
	NoArgCode* op_code;
	FuncArgs (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct OneU8Entry : JumpTableEntry {
	OneU8* op_code;
	uint8_t* (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct TwoU8Entry : JumpTableEntry {
	TwoU8* op_code;
	std::tuple<uint8_t*, uint8_t*> (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct OneU16Entry : JumpTableEntry {
	OneU16* op_code;
	uint16_t* (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct TwoU16Entry : JumpTableEntry {
	TwoU16* op_code;
	std::tuple<uint16_t*, uint16_t*> (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct ConU16Entry : JumpTableEntry {
	ConU16* op_code;
	std::tuple<Condition*, uint16_t*> (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct OneI8Entry : JumpTableEntry {
	OneI8* op_code;
	int8_t* (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct ConI8Entry : JumpTableEntry {
	ConI8* op_code;
	std::tuple<Condition*, int8_t*> (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct ConU8Entry : JumpTableEntry {
	ConU8* op_code;
	std::tuple<Condition*, uint8_t*> (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};
struct ConEntry : JumpTableEntry {
	Con* op_code;
	Condition* (*get_arguments)(Cpu*, uint8_t*);
	const std::string (*get_disassembly)(std::array<uint8_t, 3>);
};

static TwoU8Code copy = TwoU8Code(&Cpu::copy, 1, 1);
static TwoU8Code load_immediate_8bit = TwoU8Code(&Cpu::load_immediate_8bit, 2, 2);
static TwoU16Code load_immediate_16bit = TwoU16Code(&Cpu::load_immediate_16bit, 3, 3);
static OneU8Code store_at_hl_address = OneU8Code(&Cpu::store_at_hl_address, 2, 1);
static OneU8Code store_immediate_at_hl_address = OneU8Code(&Cpu::store_immediate_at_hl_address, 3, 2);
static OneU8Code load_from_hl_address = OneU8Code(&Cpu::load_from_hl_address, 2, 1);
static OneU16Code store_a_at_register_address = OneU16Code(&Cpu::store_a_at_register_address, 2, 1);
static OneU16Code store_a_at_immediate_address = OneU16Code(&Cpu::store_a_at_immediate_address, 4, 3);
static OneU8Code store_a_at_immediate_hardware_address = OneU8Code(&Cpu::store_a_at_immediate_hardware_address, 3, 2);
static NoArgCode store_a_at_hardware_address_offset_by_c =
	NoArgCode(&Cpu::store_a_at_hardware_address_offset_by_c, 2, 1);
static OneU16Code load_a_from_register_address = OneU16Code(&Cpu::load_a_from_register_address, 2, 1);
static OneU16Code load_a_from_immediate_address = OneU16Code(&Cpu::load_a_from_immediate_address, 4, 3);
static OneU8Code load_a_from_immediate_hardware_address = OneU8Code(&Cpu::load_a_from_immediate_hardware_address, 3, 2);
static NoArgCode load_a_from_hardware_address_offset_by_c =
	NoArgCode(&Cpu::load_a_from_hardware_address_offset_by_c, 2, 1);
static NoArgCode store_a_at_hl_address_increment = NoArgCode(&Cpu::store_a_at_hl_address_increment, 2, 1);
static NoArgCode store_a_at_hl_address_decrement = NoArgCode(&Cpu::store_a_at_hl_address_decrement, 2, 1);
static NoArgCode load_a_from_hl_address_increment = NoArgCode(&Cpu::load_a_from_hl_address_increment, 2, 1);
static NoArgCode load_a_from_hl_address_decrement = NoArgCode(&Cpu::load_a_from_hl_address_decrement, 2, 1);

static OneU8Code add_with_carry_register_to_a = OneU8Code(&Cpu::add_with_carry_register_to_a, 1, 1);
static NoArgCode add_with_carry_from_hl_address_to_a = NoArgCode(&Cpu::add_with_carry_from_hl_address_to_a, 2, 1);
static OneU8Code add_with_carry_immediate_to_a = OneU8Code(&Cpu::add_with_carry_immediate_to_a, 2, 2);
static OneU8Code add_register_to_a = OneU8Code(&Cpu::add_register_to_a, 1, 1);
static NoArgCode add_value_at_hl_address_to_a = NoArgCode(&Cpu::add_value_at_hl_address_to_a, 2, 1);
static OneU8Code add_immediate_to_a = OneU8Code(&Cpu::add_immediate_to_a, 2, 2);
static OneU8Code compare_a_with_register = OneU8Code(&Cpu::compare_a_with_register, 1, 1);
static NoArgCode compare_a_with_value_at_hl_address = NoArgCode(&Cpu::compare_a_with_value_at_hl_address, 2, 1);
static OneU8Code compare_a_with_immediate = OneU8Code(&Cpu::compare_a_with_immediate, 2, 2);
static OneU8Code decrement_register = OneU8Code(&Cpu::decrement_register, 1, 1);
static NoArgCode decrement_value_at_hl_address = NoArgCode(&Cpu::decrement_value_at_hl_address, 3, 1);
static OneU8Code increment_register = OneU8Code(&Cpu::increment_register, 1, 1);
static NoArgCode increment_value_at_hl_address = NoArgCode(&Cpu::increment_value_at_hl_address, 3, 1);
static OneU8Code subtract_with_carry_register_from_a = OneU8Code(&Cpu::subtract_with_carry_register_from_a, 1, 1);
static NoArgCode subtract_with_carry_value_at_hl_address_from_a =
	NoArgCode(&Cpu::subtract_with_carry_value_at_hl_address_from_a, 2, 1);
static OneU8Code subtract_with_carry_immediate_from_a = OneU8Code(&Cpu::subtract_with_carry_immediate_from_a, 2, 2);
static OneU8Code subtract_register_from_a = OneU8Code(&Cpu::subtract_register_from_a, 1, 1);
static NoArgCode subtract_value_at_hl_address_from_a = NoArgCode(&Cpu::subtract_value_at_hl_address_from_a, 2, 1);
static OneU8Code subtract_immediate_from_a = OneU8Code(&Cpu::subtract_immediate_from_a, 2, 2);
static OneU16Code add_16bit_register_to_HL = OneU16Code(&Cpu::add_16bit_register_to_HL, 2, 1);
static OneU16Code decrement_16bit_register = OneU16Code(&Cpu::decrement_16bit_register, 2, 1);
static OneU16Code increment_16bit_register = OneU16Code(&Cpu::increment_16bit_register, 2, 1);
static OneU8Code and_a_with_register = OneU8Code(&Cpu::and_a_with_register, 1, 1);
static NoArgCode and_a_with_value_at_hl_address = NoArgCode(&Cpu::and_a_with_value_at_hl_address, 2, 1);
static OneU8Code and_a_with_immediate = OneU8Code(&Cpu::and_a_with_immediate, 2, 2);
static NoArgCode invert_a = NoArgCode(&Cpu::invert_a, 1, 1);
static OneU8Code or_a_with_register = OneU8Code(&Cpu::or_a_with_register, 1, 1);
static NoArgCode or_a_with_value_at_hl_address = NoArgCode(&Cpu::or_a_with_value_at_hl_address, 2, 1);
static OneU8Code or_a_with_immediate = OneU8Code(&Cpu::or_a_with_immediate, 2, 2);
static OneU8Code xor_a_with_register = OneU8Code(&Cpu::xor_a_with_register, 1, 1);
static NoArgCode xor_a_with_value_at_hl_address = NoArgCode(&Cpu::xor_a_with_value_at_hl_address, 2, 1);
static OneU8Code xor_a_with_immediate = OneU8Code(&Cpu::xor_a_with_immediate, 2, 2);
static TwoU8Code set_zflag_if_register_bit_not_set = TwoU8Code(&Cpu::set_zflag_if_register_bit_not_set, 2, 2);
static OneU8Code set_zflag_if_value_at_hl_address_bit_not_set =
	OneU8Code(&Cpu::set_zflag_if_value_at_hl_address_bit_not_set, 3, 2);
static TwoU8Code clear_register_bit = TwoU8Code(&Cpu::clear_register_bit, 2, 2);
static TwoU8Code set_register_bit = TwoU8Code(&Cpu::set_register_bit, 2, 2);
static OneU8Code clear_value_at_hl_address_bit = OneU8Code(&Cpu::clear_value_at_hl_address_bit, 4, 2);
static OneU8Code set_value_at_hl_address_bit = OneU8Code(&Cpu::set_value_at_hl_address_bit, 4, 2);
static OneU8Code rotate_register_left = OneU8Code(&Cpu::rotate_register_left, 2, 2);
static NoArgCode rotate_value_at_hl_address_left = NoArgCode(&Cpu::rotate_value_at_hl_address_left, 4, 2);
static NoArgCode rotate_a_left = NoArgCode(&Cpu::rotate_a_left, 1, 1);
static OneU8Code rotate_register_left_with_carry = OneU8Code(&Cpu::rotate_register_left_with_carry, 2, 2);
static NoArgCode rotate_value_at_hl_address_left_with_carry =
	NoArgCode(&Cpu::rotate_value_at_hl_address_left_with_carry, 4, 2);
static NoArgCode rotate_a_left_with_carry = NoArgCode(&Cpu::rotate_a_left_with_carry, 1, 1);
static OneU8Code rotate_register_right = OneU8Code(&Cpu::rotate_register_right, 2, 2);
static NoArgCode rotate_value_at_hl_address_right = NoArgCode(&Cpu::rotate_value_at_hl_address_right, 4, 2);
static NoArgCode rotate_a_right = NoArgCode(&Cpu::rotate_a_right, 1, 1);
static OneU8Code rotate_register_right_with_carry = OneU8Code(&Cpu::rotate_register_right_with_carry, 2, 2);
static NoArgCode rotate_value_at_hl_address_right_with_carry =
	NoArgCode(&Cpu::rotate_value_at_hl_address_right_with_carry, 4, 2);
static NoArgCode rotate_a_right_with_carry = NoArgCode(&Cpu::rotate_a_right_with_carry, 1, 1);
static OneU8Code shift_register_left_arithmetically = OneU8Code(&Cpu::shift_register_left_arithmetically, 2, 2);
static NoArgCode shift_value_at_hl_address_left_arithmetically =
	NoArgCode(&Cpu::shift_value_at_hl_address_left_arithmetically, 4, 2);
static OneU8Code shift_register_right_arithmetically = OneU8Code(&Cpu::shift_register_right_arithmetically, 2, 2);
static NoArgCode shift_value_at_hl_address_right_arithmetically =
	NoArgCode(&Cpu::shift_value_at_hl_address_right_arithmetically, 4, 2);
static OneU8Code shift_register_right_logically = OneU8Code(&Cpu::shift_register_right_logically, 2, 2);
static NoArgCode shift_value_at_hl_address_right_logically =
	NoArgCode(&Cpu::shift_value_at_hl_address_right_logically, 4, 2);
static OneU8Code swap_register_nibbles = OneU8Code(&Cpu::swap_register_nibbles, 2, 2);
static NoArgCode swap_value_at_hl_address_nibbles = NoArgCode(&Cpu::swap_value_at_hl_address_nibbles, 4, 2);
static OneU16Code call = OneU16Code(&Cpu::call, 6, 3);
static ConU16Code call_conditionally = ConU16Code(&Cpu::call_conditionally, 6, 3);
static NoArgCode jump_to_value_at_hl_address = NoArgCode(&Cpu::jump_to_value_at_hl_address, 1, 1);
static OneU16Code jump_to_immediate = OneU16Code(&Cpu::jump_to_immediate, 4, 3);
static ConU16Code jump_to_immediate_conditionally = ConU16Code(&Cpu::jump_to_immediate_conditionally, 4, 3);
static OneI8Code jump_relative_to_immediate = OneI8Code(&Cpu::jump_relative_to_immediate, 3, 2);
static ConI8Code jump_relative_to_immediate_conditionally =
	ConI8Code(&Cpu::jump_relative_to_immediate_conditionally, 3, 2);
static ConCode return_from_subroutine_conditionally = ConCode(&Cpu::return_from_subroutine_conditionally, 5, 1);
static NoArgCode return_from_subroutine = NoArgCode(&Cpu::return_from_subroutine, 4, 1);
static NoArgCode return_from_interrupt_subroutine = NoArgCode(&Cpu::return_from_interrupt_subroutine, 4, 1);
static OneU8Code call_vec = OneU8Code(&Cpu::call_vec, 4, 1);
static NoArgCode invert_carry_flag = NoArgCode(&Cpu::invert_carry_flag, 1, 1);
static NoArgCode set_carry_flag = NoArgCode(&Cpu::set_carry_flag, 1, 1);
static NoArgCode add_sp_to_hl = NoArgCode(&Cpu::add_sp_to_hl, 2, 1);
static OneI8Code add_signed_immediate_to_sp = OneI8Code(&Cpu::add_signed_immediate_to_sp, 4, 2);
static NoArgCode decrement_sp = NoArgCode(&Cpu::decrement_sp, 2, 1);
static NoArgCode increment_sp = NoArgCode(&Cpu::increment_sp, 2, 1);
static OneU16Code load_sp_from_immediate_16bit = OneU16Code(&Cpu::load_sp_from_immediate_16bit, 3, 3);
static OneU16Code store_sp_at_immediate_address = OneU16Code(&Cpu::store_sp_at_immediate_address, 5, 3);
static OneI8Code load_hl_from_sp_plus_signed_immediate = OneI8Code(&Cpu::load_hl_from_sp_plus_signed_immediate, 3, 2);
static NoArgCode copy_hl_to_sp = NoArgCode(&Cpu::copy_hl_to_sp, 2, 1);
static NoArgCode pop_stack_to_af = NoArgCode(&Cpu::pop_stack_to_af, 3, 1);
static OneU16Code pop_stack_to_16bit_register = OneU16Code(&Cpu::pop_stack_to_16bit_register, 3, 1);
static NoArgCode push_af_to_stack = NoArgCode(&Cpu::push_af_to_stack, 4, 1);
static OneU16Code push_16bit_register_to_stack = OneU16Code(&Cpu::push_16bit_register_to_stack, 4, 1);
static NoArgCode disable_interrupts = NoArgCode(&Cpu::disable_interrupts, 1, 1);
static NoArgCode enable_interrupts = NoArgCode(&Cpu::enable_interrupts, 1, 1);
static NoArgCode halt = NoArgCode(&Cpu::halt, 0, 1);
static NoArgCode decimal_adjust_accumulator = NoArgCode(&Cpu::decimal_adjust_accumulator, 1, 1);
static NoArgCode nop = NoArgCode(&Cpu::nop, 1, 1);
static NoArgCode stop = NoArgCode(&Cpu::stop, 0, 2);
static NoArgCode unsupported_op = NoArgCode(&Cpu::unsupported_op, 0, 1);

constexpr std::array<JumpTableEntry, 256> jump_table = {
	NoArgEntry{&nop,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "NOP";
			   }},
	TwoU16Entry{&load_immediate_16bit,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<uint16_t*, uint16_t*>(cpu->get_bc_pointer(),
															reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += "BC";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&store_a_at_register_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "LD [BC]";
				}},
	OneU16Entry{&increment_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "INC BC";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC B";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC B";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "B";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&rotate_a_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLCA";
			   }},
	OneU16Entry{&store_sp_at_immediate_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return reinterpret_cast<uint16_t*>(instr_ptr + 1);
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "SP ";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&add_16bit_register_to_HL,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "ADD BC";
				}},
	OneU16Entry{&load_a_from_register_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "LD A,[BC]";
				}},
	OneU16Entry{&decrement_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "DEC BC";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC C";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC C";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "C";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&rotate_a_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRCA";
			   }},
	NoArgEntry{&stop,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "STOP";
			   }},
	TwoU16Entry{&load_immediate_16bit,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<uint16_t*, uint16_t*>(cpu->get_de_pointer(),
															reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += "DE";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&store_a_at_register_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "LD [DE]";
				}},
	OneU16Entry{&increment_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "INC DE";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC D";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC D";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "D";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&rotate_a_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLA";
			   }},
	OneU8Entry{&jump_relative_to_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "JR ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU16Entry{&add_16bit_register_to_HL,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "ADD DE";
				}},
	OneU16Entry{&load_a_from_register_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "LD A,[DE]";
				}},
	OneU16Entry{&decrement_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "DEC DE";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC E";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC E";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "E";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&rotate_a_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRA";
			   }},
	ConU8Entry{&jump_relative_to_immediate_conditionally,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<Condition, uint8_t*>(Condition::NZ, instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "JR ";
				   string += "NZ";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	TwoU16Entry{&load_immediate_16bit,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<uint16_t*, uint16_t*>(cpu->get_hl_pointer(),
															reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += "HL";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&store_a_at_hl_address_increment,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HLI],A";
			   }},
	OneU16Entry{&increment_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_hl_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "INC HL";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC H";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC H";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "H";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&decimal_adjust_accumulator,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DAA";
			   }},
	ConU8Entry{&jump_relative_to_immediate_conditionally,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<Condition, uint8_t*>(Condition::Z, instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "JR ";
				   string += "Z";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU16Entry{&add_16bit_register_to_HL,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_hl_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "ADD HL";
				}},
	NoArgEntry{&load_a_from_hl_address_increment,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,[HLI]";
			   }},
	OneU16Entry{&decrement_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_hl_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "DEC HL";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC L";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC L";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "L";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&invert_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CPL";
			   }},
	ConU8Entry{&jump_relative_to_immediate_conditionally,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<Condition, uint8_t*>(Condition::NC, instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "JR ";
				   string += "NC";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	TwoU16Entry{&load_immediate_16bit,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<uint16_t*, uint16_t*>(cpu->get_sp_pointer(),
															reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += "SP";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&store_a_at_hl_address_decrement,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HLD],A";
			   }},
	OneU16Entry{&increment_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_sp_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "INC SP";
				}},
	NoArgEntry{&increment_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC [HL]";
			   }},
	NoArgEntry{&decrement_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC [HL]";
			   }},
	OneU8Entry{&store_immediate_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "[HL]";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&set_carry_flag,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SCF";
			   }},
	ConU8Entry{&jump_relative_to_immediate_conditionally,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<Condition, uint8_t*>(Condition::C, instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "JR ";
				   string += "C";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU16Entry{&add_16bit_register_to_HL,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_sp_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "ADD SP";
				}},
	NoArgEntry{&load_a_from_hl_address_decrement,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,[HLD]";
			   }},
	OneU16Entry{&decrement_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_sp_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "DEC SP";
				}},
	OneU8Entry{&increment_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "INC A";
			   }},
	OneU8Entry{&decrement_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DEC A";
			   }},
	TwoU8Entry{&load_immediate_8bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), instr_ptr + 1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "A";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&invert_carry_flag,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CCF";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_b_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD B,A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_c_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD C,A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_d_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD D,A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_e_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD E,A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_h_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD H,A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_l_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD L,A";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],B";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],C";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],D";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],E";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],H";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],L";
			   }},
	NoArgEntry{&halt,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "HALT";
			   }},
	OneU8Entry{&store_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD [HL],A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,B";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,C";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,D";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,E";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,H";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,L";
			   }},
	OneU8Entry{&load_from_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A";
			   }},
	TwoU8Entry{&copy,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t*, uint8_t*>(cpu->get_a_pointer(), cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD A,A";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD B";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD C";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD D";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD E";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD H";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD L";
			   }},
	NoArgEntry{&add_value_at_hl_address_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD A,[HL]";
			   }},
	OneU8Entry{&add_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADD A";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC B";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC C";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC D";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC E";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC H";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC L";
			   }},
	NoArgEntry{&add_with_carry_from_hl_address_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC A,[HL]";
			   }},
	OneU8Entry{&add_with_carry_register_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "ADC A";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB B";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB C";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB D";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB E";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB H";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB L";
			   }},
	NoArgEntry{&subtract_value_at_hl_address_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB A,[HL]";
			   }},
	OneU8Entry{&subtract_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SUB A";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC B";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC C";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC D";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC E";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC H";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC L";
			   }},
	NoArgEntry{&subtract_with_carry_value_at_hl_address_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC A,[HL]";
			   }},
	OneU8Entry{&subtract_with_carry_register_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SBC A";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND B";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND C";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND D";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND E";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND H";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND L";
			   }},
	NoArgEntry{&and_a_with_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND A,[HL]";
			   }},
	OneU8Entry{&and_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "AND A";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR B";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR C";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR D";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR E";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR H";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR L";
			   }},
	NoArgEntry{&xor_a_with_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR A,[HL]";
			   }},
	OneU8Entry{&xor_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "XOR A";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR B";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR C";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR D";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR E";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR H";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR L";
			   }},
	NoArgEntry{&or_a_with_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR A,[HL]";
			   }},
	OneU8Entry{&or_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "OR A";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP B";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP C";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP D";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP E";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP H";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP L";
			   }},
	NoArgEntry{&compare_a_with_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP A,[HL]";
			   }},
	OneU8Entry{&compare_a_with_register,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CP A";
			   }},
	ConEntry{&return_from_subroutine_conditionally,
			 [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				 return Condition::NZ;
			 },
			 [](std::array<uint8_t, 3> bytes) -> const std::string {
				 return "RET NZ";
			 }},
	OneU16Entry{&pop_stack_to_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "POP BC";
				}},
	ConU16Entry{&jump_to_immediate_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::NZ, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "JP ";
					string += "NZ";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&jump_to_immediate,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return reinterpret_cast<uint16_t*>(instr_ptr + 1);
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "JP ";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	ConU16Entry{&call_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::NZ, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "CALL ";
					string += "NZ";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&push_16bit_register_to_stack,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_bc_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "PUSH BC";
				}},
	OneU8Entry{&add_immediate_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "ADD ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(0);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 0);
				   return string;
			   }},
	ConEntry{&return_from_subroutine_conditionally,
			 [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				 return Condition::Z;
			 },
			 [](std::array<uint8_t, 3> bytes) -> const std::string {
				 return "RET Z";
			 }},
	NoArgEntry{&return_from_subroutine,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RET";
			   }},
	ConU16Entry{&jump_to_immediate_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::Z, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "JP ";
					string += "Z";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&nop,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "CB INSTRUCTION";
			   }},
	ConU16Entry{&call_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::Z, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "CALL ";
					string += "Z";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&call,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return reinterpret_cast<uint16_t*>(instr_ptr + 1);
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "CALL ";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU8Entry{&add_with_carry_immediate_to_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "ADC ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 1);
				   return string;
			   }},
	ConEntry{&return_from_subroutine_conditionally,
			 [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				 return Condition::NC;
			 },
			 [](std::array<uint8_t, 3> bytes) -> const std::string {
				 return "RET NC";
			 }},
	OneU16Entry{&pop_stack_to_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "POP DE";
				}},
	ConU16Entry{&jump_to_immediate_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::NC, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "JP ";
					string += "NC";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	ConU16Entry{&call_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::NC, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "CALL ";
					string += "NC";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	OneU16Entry{&push_16bit_register_to_stack,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_de_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "PUSH DE";
				}},
	OneU8Entry{&subtract_immediate_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "SUB ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(2);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 2);
				   return string;
			   }},
	ConEntry{&return_from_subroutine_conditionally,
			 [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				 return Condition::C;
			 },
			 [](std::array<uint8_t, 3> bytes) -> const std::string {
				 return "RET C";
			 }},
	NoArgEntry{&return_from_interrupt_subroutine,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RETI";
			   }},
	ConU16Entry{&jump_to_immediate_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::C, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "JP ";
					string += "C";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	ConU16Entry{&call_conditionally,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return std::tuple<Condition, uint16_t*>(Condition::C, reinterpret_cast<uint16_t*>(instr_ptr + 1));
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "CALL ";
					string += "C";
					string += ",";
					string += std::format("${:04x}", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	OneU8Entry{&subtract_with_carry_immediate_from_a,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "SBC ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(3);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 3);
				   return string;
			   }},
	OneU8Entry{&store_a_at_immediate_hardware_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LDH ";
				   string += std::format("[${:02x}]", static_cast<int>(bytes[1]));
				   string += ",";
				   string += "A";
				   return string;
			   }},
	OneU16Entry{&pop_stack_to_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_hl_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "POP HL";
				}},
	NoArgEntry{&store_a_at_hardware_address_offset_by_c,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LDH [C],A";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	OneU16Entry{&push_16bit_register_to_stack,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_hl_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "PUSH HL";
				}},
	OneU8Entry{&and_a_with_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "AND ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(4);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 4);
				   return string;
			   }},
	OneU8Entry{&add_signed_immediate_to_sp,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "ADD ";
				   string += "SP";
				   string += ",";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&jump_to_value_at_hl_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "JP [HL]";
			   }},
	OneU16Entry{&store_a_at_immediate_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return reinterpret_cast<uint16_t*>(instr_ptr + 1);
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += std::format("[${:04x}]", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					string += ",";
					string += "A";
					return string;
				}},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	OneU8Entry{&xor_a_with_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "XOR ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(5);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 5);
				   return string;
			   }},
	OneU8Entry{&load_a_from_immediate_hardware_address,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LDH ";
				   string += "A";
				   string += ",";
				   string += std::format("[${:02x}]", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU16Entry{&pop_stack_to_16bit_register,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_af_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "POP AF";
				}},
	NoArgEntry{&load_a_from_hardware_address_offset_by_c,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LDH A,[C]";
			   }},
	NoArgEntry{&disable_interrupts,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "DI";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	OneU16Entry{&push_16bit_register_to_stack,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return cpu->get_af_pointer();
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					return "PUSH AF";
				}},
	OneU8Entry{&or_a_with_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "OR ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(6);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 6);
				   return string;
			   }},
	OneU8Entry{&load_hl_from_sp_plus_signed_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "LD ";
				   string += "HL";
				   string += ",";
				   string += std::format("SP + {}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	NoArgEntry{&copy_hl_to_sp,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "LD SP,HL";
			   }},
	OneU16Entry{&load_a_from_immediate_address,
				[](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
					return reinterpret_cast<uint16_t*>(instr_ptr + 1);
				},
				[](std::array<uint8_t, 3> bytes) -> const std::string {
					std::string string = "LD ";
					string += "A";
					string += ",";
					string += std::format("[${:04x}]", static_cast<uint16_t>((bytes[2] << 8) | bytes[1]));
					return string;
				}},
	NoArgEntry{&enable_interrupts,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "EI";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	NoArgEntry{&unsupported_op,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "";
			   }},
	OneU8Entry{&compare_a_with_immediate,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return instr_ptr + 1;
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "CP ";
				   string += std::format("${:02x}", static_cast<int>(bytes[1]));
				   return string;
			   }},
	OneU8Entry{&call_vec,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(7);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   std::string string = "RST ";
				   string += std::format("{:02x}", 7);
				   return string;
			   }},
};
constexpr std::array<JumpTableEntry, 256> jump_table_cb = {
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC B";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC C";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC D";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC E";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC H";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC L";
			   }},
	NoArgEntry{&rotate_value_at_hl_address_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC [HL]";
			   }},
	OneU8Entry{&rotate_register_left_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RLC A";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC B";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC C";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC D";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC E";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC H";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC L";
			   }},
	NoArgEntry{&rotate_value_at_hl_address_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC [HL]";
			   }},
	OneU8Entry{&rotate_register_right_with_carry,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RRC A";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL B";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL C";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL D";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL E";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL H";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL L";
			   }},
	NoArgEntry{&rotate_value_at_hl_address_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL [HL]";
			   }},
	OneU8Entry{&rotate_register_left,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RL A";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR B";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR C";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR D";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR E";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR H";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR L";
			   }},
	NoArgEntry{&rotate_value_at_hl_address_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR [HL]";
			   }},
	OneU8Entry{&rotate_register_right,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RR A";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA B";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA C";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA D";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA E";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA H";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA L";
			   }},
	NoArgEntry{&shift_value_at_hl_address_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA [HL]";
			   }},
	OneU8Entry{&shift_register_left_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SLA A";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA B";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA C";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA D";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA E";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA H";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA L";
			   }},
	NoArgEntry{&shift_value_at_hl_address_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA [HL]";
			   }},
	OneU8Entry{&shift_register_right_arithmetically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA A";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP B";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP C";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP D";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP E";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP H";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP L";
			   }},
	NoArgEntry{&swap_value_at_hl_address_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP HL";
			   }},
	OneU8Entry{&swap_register_nibbles,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SWAP A";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_b_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA B";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_c_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA C";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_d_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA D";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_e_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA E";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_h_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA H";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_l_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA L";
			   }},
	NoArgEntry{&shift_value_at_hl_address_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::monostate();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRL [HL]";
			   }},
	OneU8Entry{&shift_register_right_logically,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return cpu->get_a_pointer();
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SRA A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(0);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 0,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 1,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(2);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 2,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(3);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 3,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(4);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 4,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(5);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 5,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(6);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 6,A";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,B";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,C";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,D";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,E";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,H";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,L";
			   }},
	OneU8Entry{&set_zflag_if_value_at_hl_address_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(7);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,[HL]";
			   }},
	TwoU8Entry{&set_zflag_if_register_bit_not_set,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "BIT 7,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(0);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 0,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 1,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(2);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 2,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(3);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 3,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(4);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 4,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(5);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 5,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(6);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 6,A";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,B";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,C";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,D";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,E";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,H";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,L";
			   }},
	OneU8Entry{&clear_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(7);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,[HL]";
			   }},
	TwoU8Entry{&clear_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "RES 7,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(0);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(0, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 0,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(1);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(1, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 1,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(2);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(2, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 2,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(3);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(3, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 3,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(4);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(4, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 4,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(5);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(5, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 5,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(6);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(6, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 6,A";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_b_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,B";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_c_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,C";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_d_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,D";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_e_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,E";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_h_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,H";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_l_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,L";
			   }},
	OneU8Entry{&set_value_at_hl_address_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return static_cast<uint8_t>(7);
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,[HL]";
			   }},
	TwoU8Entry{&set_register_bit,
			   [](Cpu* cpu, uint8_t* instr_ptr) -> FuncArgs {
				   return std::tuple<uint8_t, uint8_t*>(7, cpu->get_a_pointer());
			   },
			   [](std::array<uint8_t, 3> bytes) -> const std::string {
				   return "SET 7,A";
			   }},
};