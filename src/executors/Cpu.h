#pragma once
#include "../memory/DataBus.h"
#include <iostream>

enum Flag {
	Z_FLAG = 128, // Zero
	N_FLAG = 64,  // Subtract
	H_FLAG = 32,  // Half Carry
	C_FLAG = 16,  // Carry
};
enum Condition : std::uint8_t {
	NZ = 0,
	Z = 1,
	NC = 2,
	C = 3,
};

enum CpuState {
	RUNNING,
	STOPPED,
	HALTED,
};

class JumpTableEntry;

struct CurrentOperation {
	JumpTableEntry* jump_table_entry;
	uint8_t remaining_cycles;
	std::string disassembly;

	uint8_t get_length();
	uint8_t get_total_cycles();
};

// TODO Check runtime alignment...
class Cpu {
  private:
	CpuState state;
	CurrentOperation current_operation;
	alignas(uint16_t) uint8_t b;
	uint8_t c;
	alignas(uint16_t) uint8_t d;
	uint8_t e;
	alignas(uint16_t) uint8_t a;
	uint8_t f;
	alignas(uint16_t) uint8_t h;
	uint8_t l;
	uint16_t sp;
	uint16_t pc;
	bool interrupts_enabled;
	DataBus* databus;

	uint16_t get_hl();
	void set_hl(uint16_t value);

	void push_to_stack(uint16_t value);
	uint16_t pop_from_stack();

	bool get_flag(Flag flag);
	void set_flag(Flag flag, bool value);
	void set_flags_addition(uint16_t op0, uint16_t op1, uint16_t result);
	void set_flags_subtraction(uint16_t op0, uint16_t op1, uint16_t result);
	bool condition_is_met(Condition condition);

	void fetch_next_instruction();

  public:
	Cpu(DataBus* databus);
	~Cpu();

	void tick_machine_cycle();

	std::string get_instruction_disassembly();

	uint8_t* get_b_pointer();
	uint8_t* get_c_pointer();
	uint8_t* get_d_pointer();
	uint8_t* get_e_pointer();
	uint8_t* get_a_pointer();
	uint8_t* get_f_pointer();
	uint8_t* get_h_pointer();
	uint8_t* get_l_pointer();
	uint8_t* get_mem_pointer_from_hl();

	uint16_t* get_bc_pointer();
	uint16_t* get_de_pointer();
	uint16_t* get_af_pointer();
	uint16_t* get_hl_pointer();
	uint16_t* get_sp_pointer();

	// OpCodes - Following https://rgbds.gbdev.io/docs/v0.9.1/gbz80.7#LD_r8,r8 but with more meaningful (for me, at
	// least) names Load/Store operations
	void copy(uint8_t* dest, uint8_t* src);							// LD r8,r8
	void load_immediate_8bit(uint8_t* dest, uint8_t* src);			// LD r8,n8
	void load_immediate_16bit(uint16_t* dest, uint16_t* src);		// LD r16,n16
	void store_at_hl_address(uint8_t* src);							// LD [HL],r8
	void store_immediate_at_hl_address(uint8_t* src);				// LD [HL],n8
	void load_from_hl_address(uint8_t* dest);						// LD r8,[HL]
	void store_a_at_register_address(uint16_t* address);			// LD [r16],A
	void store_a_at_immediate_address(uint16_t* address);			// LD [n16],A
	void store_a_at_immediate_hardware_address(uint8_t* address);	// LDH [n16],A
	void store_a_at_hardware_address_offset_by_c();					// LDH [C],A
	void load_a_from_register_address(uint16_t* address);			// LD A,[r16]
	void load_a_from_immediate_address(uint16_t* address);			// LD A,[n16]
	void load_a_from_immediate_hardware_address(uint8_t* addr_low); // LDH A,[n16]
	void load_a_from_hardware_address_offset_by_c();				// LDH A,[C]
	void store_a_at_hl_address_increment();							// LD [HLI],A
	void store_a_at_hl_address_decrement();							// LD [HLD],A
	void load_a_from_hl_address_increment();						// LD A,[HLI]
	void load_a_from_hl_address_decrement();						// LD A,[HLD]

	// 8-bit arithmetic instructions
	void add_with_carry_register_to_a(uint8_t* src);		 // ADC A,r8
	void add_with_carry_from_hl_address_to_a();				 // ADC A,[HL]
	void add_with_carry_immediate_to_a(uint8_t* src);		 // ADC A,n8
	void add_register_to_a(uint8_t* src);					 // ADD A,r8
	void add_value_at_hl_address_to_a();					 // ADD A,[HL]
	void add_immediate_to_a(uint8_t* src);					 // ADD A,n8
	void compare_a_with_register(uint8_t* src);				 // CP A,r8
	void compare_a_with_value_at_hl_address();				 // CP A,[HL]
	void compare_a_with_immediate(uint8_t* src);			 // CP A,n8
	void decrement_register(uint8_t* src);					 // DEC r8
	void decrement_value_at_hl_address();					 // DEC [HL]
	void increment_register(uint8_t* src);					 // INC r8
	void increment_value_at_hl_address();					 // INC [HL]
	void subtract_with_carry_register_from_a(uint8_t* src);	 // SBC A,r8
	void subtract_with_carry_value_at_hl_address_from_a();	 // SBC A,[HL]
	void subtract_with_carry_immediate_from_a(uint8_t* src); // SBC A,n8
	void subtract_register_from_a(uint8_t* src);			 // SUB A,r8
	void subtract_value_at_hl_address_from_a();				 // SUB A,[HL]
	void subtract_immediate_from_a(uint8_t* src);			 // SUB A,n8

	// 16-bit arithmetic operations
	void add_16bit_register_to_HL(uint16_t* src); // ADD HL,r16
	void decrement_16bit_register(uint16_t* src); // DEC r16
	void increment_16bit_register(uint16_t* src); // INC r16

	// Bitwise logic instructions
	void and_a_with_register(uint8_t* src);	 // AND A,r8
	void and_a_with_value_at_hl_address();	 // AND A,[HL]
	void and_a_with_immediate(uint8_t* src); // AND A,n8
	void invert_a();						 // CPL
	void or_a_with_register(uint8_t* src);	 // OR A,r8
	void or_a_with_value_at_hl_address();	 // OR A,[HL]
	void or_a_with_immediate(uint8_t* src);	 // OR A,n8
	void xor_a_with_register(uint8_t* src);	 // XOR A,r8
	void xor_a_with_value_at_hl_address();	 // XOR A,[HL]
	void xor_a_with_immediate(uint8_t* src); // XOR A,n8

	// Bitflag instructions
	void set_zflag_if_register_bit_not_set(uint8_t* bit_position, uint8_t* reg); // BIT u3,r8
	void set_zflag_if_value_at_hl_address_bit_not_set(uint8_t* bit_position);	 // BIT u3,[HL]
	void clear_register_bit(uint8_t* bit_position, uint8_t* reg);				 // RES u3,r8
	void clear_value_at_hl_address_bit(uint8_t* bit_position);					 // RES u3,[HL]
	void set_register_bit(uint8_t* bit_position, uint8_t* reg);					 // SET u3,r8
	void set_value_at_hl_address_bit(uint8_t* bit_position);					 // SET u3,[HL]

	// Bit shift instructions
	void rotate_register_left(uint8_t* reg);				// RL r8
	void rotate_value_at_hl_address_left();					// RL [HL]
	void rotate_a_left();									// RLA
	void rotate_register_left_with_carry(uint8_t* reg);		// RLC r8
	void rotate_value_at_hl_address_left_with_carry();		// RLC [HL]
	void rotate_a_left_with_carry();						// RLCA
	void rotate_register_right(uint8_t* reg);				// RR r8
	void rotate_value_at_hl_address_right();				// RR [HL]
	void rotate_a_right();									// RRA
	void rotate_register_right_with_carry(uint8_t* reg);	// RRC r8
	void rotate_value_at_hl_address_right_with_carry();		// RRC [HL]
	void rotate_a_right_with_carry();						// RRCA
	void shift_register_left_arithmetically(uint8_t* reg);	// SLA r8
	void shift_value_at_hl_address_left_arithmetically();	// SLA [HL]
	void shift_register_right_arithmetically(uint8_t* reg); // SRA r8
	void shift_value_at_hl_address_right_arithmetically();	// SRA [HL]
	void shift_register_right_logically(uint8_t* reg);		// SRL r8
	void shift_value_at_hl_address_right_logically();		// SRL [HL]
	void swap_register_nibbles(uint8_t* reg);				// SWAP r8
	void swap_value_at_hl_address_nibbles();				// SWAP [HL]

	// Jump and Subroutine instructions
	void call(uint16_t* call_address);													 // CALL n16
	void call_conditionally(Condition* condition, uint16_t* call_address);				 // CALL cc,n16
	void jump_to_value_at_hl_address();													 // JP HL
	void jump_to_immediate(uint16_t* jump_address);										 // JP n16
	void jump_to_immediate_conditionally(Condition* condition, uint16_t* jump_address);	 // JP cc,n16
	void jump_relative_to_immediate(int8_t* offset);									 // JR n16
	void jump_relative_to_immediate_conditionally(Condition* condition, int8_t* offset); // JR cc,n16
	void return_from_subroutine_conditionally(Condition* condition);					 // RET cc
	void return_from_subroutine();														 // RET
	void return_from_interrupt_subroutine();											 // RETI
	void call_vec(uint8_t* vec);														 // RST vec

	// Carry Flag Instructions
	void invert_carry_flag(); // CCF
	void set_carry_flag();	  // SCF

	// Stack instructions
	void add_sp_to_hl();									   // ADD HL,SP
	void add_signed_immediate_to_sp(int8_t* value);			   // ADD SP,e8
	void decrement_sp();									   // DEC SP
	void increment_sp();									   // INC SP
	void load_sp_from_immediate_16bit(uint16_t* src);		   // LD SP,n16
	void store_sp_at_immediate_address(uint16_t* address);	   // LD [n16],SP
	void load_hl_from_sp_plus_signed_immediate(int8_t* value); // LD HL,SP+e8
	void copy_hl_to_sp();									   // LD SP,HL
	void pop_stack_to_af();									   // POP AF
	void pop_stack_to_16bit_register(uint16_t* dest);		   // POP r16
	void push_af_to_stack();								   // PUSH AF
	void push_16bit_register_to_stack(uint16_t* reg);		   // PUSH r16

	// Interrupt Instructions
	void disable_interrupts(); // DI
	void enable_interrupts();  // EI
	void halt();			   // HALT

	// Miscellaneous
	void decimal_adjust_accumulator(); // DAA
	void nop();						   // NOP
	void stop();					   // STOP

	void unsupported_op();
};
