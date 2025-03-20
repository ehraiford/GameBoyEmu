#include <cstdint>
#include <functional>
#include <array>
#include "Cpu.h"

typedef void (Cpu::*OpFunc)(void*);
class OpCode {
    OpFunc op_func;
    uint8_t cycles;
    uint8_t bytes;
public: 
    OpCode(OpFunc func, uint8_t cycles) : op_func(func), cycles(cycles) {};
    OpCode(OpFunc func, uint8_t cycles, uint8_t bytes) : op_func(func), cycles(cycles), bytes(bytes) {};
    
    void execute(Cpu* cpu, void* args) {
        (cpu->*op_func)(args);
    };
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
static OpCode subtract_with_carry_value_at_hl_address_from_a = OpCode(&Cpu::subtract_with_carry_value_at_hl_address_from_a, 2, 1);
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
static OpCode set_zflag_if_value_at_hl_address_bit_not_set = OpCode(&Cpu::set_zflag_if_value_at_hl_address_bit_not_set, 3, 2); 
static OpCode clear_register_bit = OpCode(&Cpu::clear_register_bit, 2, 2); 
static OpCode clear_value_at_hl_address_bit = OpCode(&Cpu::clear_value_at_hl_address_bit, 4, 2); 
static OpCode set_value_at_hl_address_bit = OpCode(&Cpu::set_value_at_hl_address_bit, 4, 2);
static OpCode rotate_register_left = OpCode(&Cpu::rotate_register_left, 2, 2); 
static OpCode rotate_value_at_hl_address_left = OpCode(&Cpu::rotate_value_at_hl_address_left, 4, 2); 
static OpCode rotate_a_left = OpCode(&Cpu::rotate_a_left, 1, 1); 
static OpCode rotate_register_left_carry = OpCode(&Cpu::rotate_register_left_carry, 2, 2);
static OpCode rotate_value_at_hl_address_left_carry = OpCode(&Cpu::rotate_value_at_hl_address_left_carry, 4, 2); 
static OpCode rotate_a_left_with_carry = OpCode(&Cpu::rotate_a_left_with_carry, 1, 1); 
static OpCode rotate_register_right = OpCode(&Cpu::rotate_register_right, 2, 2); 
static OpCode rotate_value_at_hl_address_right = OpCode(&Cpu::rotate_value_at_hl_address_right, 4, 2); 
static OpCode rotate_a_right = OpCode(&Cpu::rotate_a_right, 1, 1);
static OpCode rotate_register_right_with_carry = OpCode(&Cpu::rotate_register_right_with_carry, 2, 2); 
static OpCode rotate_value_at_hl_address_right_with_carry = OpCode(&Cpu::rotate_value_at_hl_address_right_with_carry, 4, 2); 
static OpCode rotate_a_right_with_carry = OpCode(&Cpu::rotate_a_right_with_carry, 1, 1); 
static OpCode shift_register_left_arithmetically = OpCode(&Cpu::shift_register_left_arithmetically, 2, 2);
static OpCode shift_value_at_hl_address_left_arithmetically = OpCode(&Cpu::shift_value_at_hl_address_left_arithmetically, 4, 2); 
static OpCode shift_register_right_arithmetically = OpCode(&Cpu::shift_register_right_arithmetically, 2, 2); 
static OpCode shift_value_at_hl_address_right_arithmetically = OpCode(&Cpu::shift_value_at_hl_address_right_arithmetically, 4, 2);
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
static OpCode call_address = OpCode(&Cpu::call_address, 4, 1); 
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


struct JumpTableEntry {
    OpCode* op_code;
    void* (*get_arguments)(Cpu*, uint16_t*);
};

constexpr std::array<JumpTableEntry, 512> jump_table = {
    JumpTableEntry {
        &nop,
        [](Cpu* cpu, uint16_t* instr_ptr) -> void* { return nullptr; }
    },
    JumpTableEntry {
        &load_immediate_16bit,
        [](Cpu* cpu, uint16_t* instr_ptr) -> void* {
            auto* args = new std::pair<uint16_t*, uint16_t*>(cpu->get_bc_pointer(), instr_ptr + 1);
            return static_cast<void*>(args);
        }
    },
    JumpTableEntry {
        &store_a_at_register_address,
        [](Cpu* cpu, uint16_t* instr_ptr) -> void* { return cpu->get_bc_pointer(); }
    },
};
