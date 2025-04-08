#pragma once
#include "../memory/DataBus.h"
#include "Opcodes.h"
#include <array>
#include <queue>
#include <string>

class FetchedInstruction {
	JumpTableEntry jump_table_entry;
	std::string disassembly;

  public:
	FetchedInstruction(std::array<uint8_t, 3> bytes);
	uint8_t get_instruction_length();
	std::string get_disassembly();
};

class Fetcher {
	std::queue<FetchedInstruction> instruction_list;
	uint16_t lift_pointer;
	DataBus* databus;

  public:
	Fetcher(DataBus* databus);
	void fetch_another_instruction();
	FetchedInstruction get_next_instruction_to_execute();
	int get_lift_pointer();
	void set_lift_pointer(uint16_t new_address);
};
