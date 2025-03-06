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


    // OpCodes - Following https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#LD_r8,r8 but with more meaningful (for me, at least) names
    void nop();
    // Load/Store operations
    void copy(); // LD r8,r8
    void load_immediate_8bit(); // LD r8,n8
    void load_immediate_16bit(); // LD r16,n16
    void store_at_HL_address(); // LD [HL],r8
    void store_immediate_at_HL_address(); // LD [HL],n8
    void load_from_HL_address(); // LD r8,[HL]
    void store_a_at_register_address(); // LD [r16],A
    void store_a_at_immediate_address(); // LD [n16],A
    void store_a_at_immediate_hardware_address(); // LDH [n16],A
    void store_a_at_offset_hardware_address(); // LDH [C],A
    void load_a_from_register_address(); // LD A,[r16]
    void load_a_from_immediate_address(); // LD A,[n16]
    void load_a_from_immediate_hardware_address(); // LDH A,[n16]
    void load_a_from_offset_hardware_address(); // LDH A,[C]
    void store_a_at_HL_address_increment(); // LD [HLI],A
    void store_a_at_HL_address_decrement(); // LD [HLD],A
    void load_a_from_HL_address_increment(); // LD A,[HLI]
    void load_a_from_HL_address_decrement(); // LD A,[HLD]

    // 8-bit arithmetic instructions
    void add_with_carry_register_to_a(); // ADC A,r8
    void add_with_carry_from_HL_address_to_a(); // ADC A,[HL]
    void add_with_carry_immediate_to_a(); // ADC A,n8
    void add_register_to_a(); // ADD A,r8
    void add_value_at_HL_address_to_a(); // ADD A,[HL]
    void add_immediate_to_a(); // ADD A,n8
    void compare_a_with_register(); // CP A,r8
    void compare_a_with_value_at_HL_address(); // CP A,[HL]
    void compare_a_with_immediate(); // CP A,n8
    void decrement_register(); // DEC r8
    void decrement_value_at_HL_address(); // DEC [HL]
    void increment_register(); // INC r8
    void increment_value_at_HL_address(); // INC [HL]
    void subtract_with_carry_register_from_a(); // SBC A,r8
    void subtract_with_carry_value_at_HL_address_from_a(); // SBC A,[HL]
    void subtract_with_carry_immediate_from_a(); // SBC A,n8
    void subtract_register_from_a(); // SUB A,r8
    void subtract_value_at_HL_address_from_a(); // SUB A,[HL]
    void subtract_immediate_from_a(); // SUB A,n8

    // 16-bit arithmetic operations
    void add_16bit_register_to_HL(); // ADD HL,r16
    void decrement_16bit_register(); // DEC r16
    void increment_16bit_register(); // INC r16

    // Bitwise logic instructions
    void and_a_with_register(); // AND A,r8
    void and_a_with_value_at_HL_address(); // AND A,[HL]
    void and_a_with_immediate();// AND A,n8
    void invert_a(); // CPL
    void or_a_with_register(); // OR A,r8
    void or_a_with_value_at_HL_address(); // OR A,[HL]
    void or_a_with_immediate(); // OR A,n8
    void xor_a_with_register(); // XOR A,r8
    void xor_a_with_value_at_HL_address(); // XOR A,[HL]
    void xor_a_with_immediate(); // XOR A,n8

    // Bitflag instructions
    void set_zflag_if_register_bit_not_set(); // BIT u3,r8
    void set_zflag_if_value_at_HL_address_bit_not_set(); // BIT u3,[HL]
    void clear_register_bit(); // RES u3,r8
    void clear_value_at_HL_address_bit(); // RES u3,[HL]
    void set_register_bit(); // SET u3,r8
    void set_value_at_HL_address_bit();// SET u3,[HL]

    // Bit shift instructions
    void rotate_register_left(); // RL r8
    void rotate_value_at_HL_address_left(); // RL [HL]
    void rotate_a_left(); // RLA
    void rotate_register_left_carry();// RLC r8
    void rotate_value_at_HL_address_left_carry(); // RLC [HL]
    void rotate_a_left_carry(); // RLCA
    void rotate_register_right(); // RR r8
    void rotate_value_at_HL_address_right(); // RR [HL]
    void rotate_a_right(); // RRA
    void rotate_register_right_with_carry(); // RRC r8
    void rotate_value_at_HL_address_right_with_carry(); // RRC [HL]
    void rotate_a_right_with_carry(); // RRCA
    void shift_register_left_arithmetically(); // SLA r8
    void shift_value_at_HL_address_left_arithmetically(); // SLA [HL]
    void shift_register_right_arithmetically(); // SRA r8
    void shift_value_at_HL_address_right_arithmetically(); // SRA [HL]
    void shift_register_right_logically(); // SRL r8
    void shift_value_at_HL_address_right_logically(); // SRL [HL]
    void swap_register_nibbles(); // SWAP r8
    void swap_value_at_HL_address_nibbles(); // SWAP [HL]

    // Jump and Subroutine instructions
    void push_next_address_to_stack(); // CALL n16
    void push_next_address_to_stack_conditionally(); // CALL cc,n16
    void jump_to_value_at_HL_address(); // JP HL
    void jump_to_immediate(); // JP n16
    void jump_to_immediate_conditionally(); // JP cc,n16
    void jump_relative_to_immediate();// JR n16
    void jump_relative_to_immediate_conditionally(); // JR cc,n16
    void return_from_subroutine_conditionally(); // RET cc
    void return_from_subroutine(); // RET
    void return_from_interrupt_subroutine(); // RETI
    void call_address(); // RST vec

    // Carry Flag Instructions
    void invert_carry_flag(); // CCF
    void set_carry_flag(); // SCF


public:
    Cpu();      
    ~Cpu();
    
};

#endif
