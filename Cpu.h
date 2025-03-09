#ifndef CPU_H  
#define CPU_H
#include <iostream>
#include "Ram.h"

enum EightBitRegs {
    B, C, D, E, F, H, L, A
};
enum SixteenBitRegs {
    BC, DE, HL, SP,
};


// TODO Check runtime alignment... 
class Cpu {
private:
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    Ram* ram;


    uint8_t get_r8(uint8_t register_number);
    uint16_t get_r16(uint8_t register_number);
    uint16_t get_r16_stk(uint8_t register_number);
    uint16_t get_r16_mem(uint8_t register_number);
    uint16_t get_immediate_ram_value(); //todo Should get the immediate value in memory following the decoded opcode and increment PC by 2 
    bool get_flag(uint8_t flag_number);
    
    void set_r8(uint8_t register_number, uint8_t value);
    void set_r16(uint8_t register_number, uint16_t value);
    void set_r16_stk(uint8_t register_number, uint16_t value);

public:
    Cpu();      
    ~Cpu();

    // OpCodes - Following https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#LD_r8,r8 but with more meaningful (for me, at least) names
    // Load/Store operations
    void copy(void* args); // LD r8,r8
    void load_immediate_8bit(void* args); // LD r8,n8
    void load_immediate_16bit(void* args); // LD r16,n16
    void store_at_hl_address(void* args); // LD [HL],r8
    void store_immediate_at_hl_address(void* args); // LD [HL],n8
    void load_from_hl_address(void* args); // LD r8,[HL]
    void store_a_at_register_address(void* args); // LD [r16],A
    void store_a_at_immediate_address(void* args); // LD [n16],A
    void store_a_at_immediate_hardware_address(void* args); // LDH [n16],A
    void store_a_at_hardware_address_offset_by_c(void* args); // LDH [C],A
    void load_a_from_register_address(void* args); // LD A,[r16]
    void load_a_from_immediate_address(void* args); // LD A,[n16]
    void load_a_from_immediate_hardware_address(void* args); // LDH A,[n16]
    void load_a_from_hardware_address_offset_by_c(void* args); // LDH A,[C]
    void store_a_at_hl_address_increment(void* args); // LD [HLI],A
    void store_a_at_hl_address_decrement(void* args); // LD [HLD],A
    void load_a_from_hl_address_increment(void* args); // LD A,[HLI]
    void load_a_from_hl_address_decrement(void* args); // LD A,[HLD]

    // 8-bit arithmetic instructions
    void add_with_carry_register_to_a(void* args); // ADC A,r8
    void add_with_carry_from_hl_address_to_a(void* args); // ADC A,[HL]
    void add_with_carry_immediate_to_a(void* args); // ADC A,n8
    void add_register_to_a(void* args); // ADD A,r8
    void add_value_at_hl_address_to_a(void* args); // ADD A,[HL]
    void add_immediate_to_a(void* args); // ADD A,n8
    void compare_a_with_register(void* args); // CP A,r8
    void compare_a_with_value_at_hl_address(void* args); // CP A,[HL]
    void compare_a_with_immediate(void* args); // CP A,n8
    void decrement_register(void* args); // DEC r8
    void decrement_value_at_hl_address(void* args); // DEC [HL]
    void increment_register(void* args); // INC r8
    void increment_value_at_hl_address(void* args); // INC [HL]
    void subtract_with_carry_register_from_a(void* args); // SBC A,r8
    void subtract_with_carry_value_at_hl_address_from_a(void* args); // SBC A,[HL]
    void subtract_with_carry_immediate_from_a(void* args); // SBC A,n8
    void subtract_register_from_a(void* args); // SUB A,r8
    void subtract_value_at_hl_address_from_a(void* args); // SUB A,[HL]
    void subtract_immediate_from_a(void* args); // SUB A,n8

    // 16-bit arithmetic operations
    void add_16bit_register_to_HL(void* args); // ADD HL,r16
    void decrement_16bit_register(void* args); // DEC r16
    void increment_16bit_register(void* args); // INC r16

    // Bitwise logic instructions
    void and_a_with_register(void* args); // AND A,r8
    void and_a_with_value_at_hl_address(void* args); // AND A,[HL]
    void and_a_with_immediate(void* args);// AND A,n8
    void invert_a(void* args); // CPL
    void or_a_with_register(void* args); // OR A,r8
    void or_a_with_value_at_hl_address(void* args); // OR A,[HL]
    void or_a_with_immediate(void* args); // OR A,n8
    void xor_a_with_register(void* args); // XOR A,r8
    void xor_a_with_value_at_hl_address(void* args); // XOR A,[HL]
    void xor_a_with_immediate(void* args); // XOR A,n8

    // Bitflag instructions
    void set_zflag_if_register_bit_not_set(void* args); // BIT u3,r8
    void set_zflag_if_value_at_hl_address_bit_not_set(void* args); // BIT u3,[HL]
    void clear_register_bit(void* args); // RES u3,r8
    void clear_value_at_hl_address_bit(void* args); // RES u3,[HL]
    void set_register_bit(void* args); // SET u3,r8
    void set_value_at_hl_address_bit(void* args);// SET u3,[HL]

    // Bit shift instructions
    void rotate_register_left(void* args); // RL r8
    void rotate_value_at_hl_address_left(void* args); // RL [HL]
    void rotate_a_left(void* args); // RLA
    void rotate_register_left_carry(void* args);// RLC r8
    void rotate_value_at_hl_address_left_carry(void* args); // RLC [HL]
    void rotate_a_left_carry(void* args); // RLCA
    void rotate_register_right(void* args); // RR r8
    void rotate_value_at_hl_address_right(void* args); // RR [HL]
    void rotate_a_right(void* args); // RRA
    void rotate_register_right_with_carry(void* args); // RRC r8
    void rotate_value_at_hl_address_right_with_carry(void* args); // RRC [HL]
    void rotate_a_right_with_carry(void* args); // RRCA
    void shift_register_left_arithmetically(void* args); // SLA r8
    void shift_value_at_hl_address_left_arithmetically(void* args); // SLA [HL]
    void shift_register_right_arithmetically(void* args); // SRA r8
    void shift_value_at_hl_address_right_arithmetically(void* args); // SRA [HL]
    void shift_register_right_logically(void* args); // SRL r8
    void shift_value_at_hl_address_right_logically(void* args); // SRL [HL]
    void swap_register_nibbles(void* args); // SWAP r8
    void swap_value_at_hl_address_nibbles(void* args); // SWAP [HL]

    // Jump and Subroutine instructions
    void push_next_address_to_stack(void* args); // CALL n16
    void push_next_address_to_stack_conditionally(void* args); // CALL cc,n16
    void jump_to_value_at_hl_address(void* args); // JP HL
    void jump_to_immediate(void* args); // JP n16
    void jump_to_immediate_conditionally(void* args); // JP cc,n16
    void jump_relative_to_immediate(void* args);// JR n16
    void jump_relative_to_immediate_conditionally(void* args); // JR cc,n16
    void return_from_subroutine_conditionally(void* args); // RET cc
    void return_from_subroutine(void* args); // RET
    void return_from_interrupt_subroutine(void* args); // RETI
    void call_address(void* args); // RST vec

    // Carry Flag Instructions
    void invert_carry_flag(void* args); // CCF
    void set_carry_flag(void* args); // SCF

    // Stack instructions
    void add_hl_to_sp(void* args); // ADD HL,SP
    void add_signed_immediate_to_sp(void* args);// ADD SP,e8
    void decrement_sp(void* args); // DEC SP
    void increment_sp(void* args); // INC SP
    void load_sp_from_immediate_16bit(void* args); // LD SP,n16
    void store_sp_at_immediate_address(void* args); // LD [n16],SP
    void load_hl_from_sp_plus_signed_immediate(void* args);// LD HL,SP+e8
    void copy_hl_to_sp(void* args); // LD SP,HL
    void pop_stack_to_af(void* args); // POP AF
    void pop_stack_to_16bit_register(void* args); // POP r16
    void push_af_to_stack(void* args); // PUSH AF
    void push_16bit_register_to_stack(void* args); // PUSH r16

    // Interrupt Instructions
    void disable_interrupts(void* args); // DI
    void enable_interrupts(void* args); // EI
    void halt(void* args); // HALT

    // Miscellaneous
    void decimal_adjust_accumulator(void* args);
    void nop(void* args);
    void stop(void* args);
};

#endif
