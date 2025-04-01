#include "FetchDecode.h"
#include <iostream>

FetchedInstruction::FetchedInstruction(std::array<uint8_t, 3> bytes) {
	if (bytes[0] == 0xCB) {
		this->jump_table_entry = jump_table_cb[bytes[1]];
	} else {
		this->jump_table_entry = jump_table[bytes[0]];
	}
	this->disassembly = this->jump_table_entry.get_disassembly(bytes);
}

uint8_t FetchedInstruction::get_instruction_length() {
	return this->jump_table_entry.op_code->get_length();
}

std::string FetchedInstruction::get_disassembly() {
	return this->disassembly;
}

Fetcher::Fetcher(Ram *ram) {
	this->ram = ram;
	this->lift_pointer = 0;
	instruction_list = std::queue<FetchedInstruction>();
}

void Fetcher::fetch_another_instruction() {
	std::array<uint8_t, 3> bytes = this->ram->get_instruction(this->lift_pointer);
	FetchedInstruction instruction = FetchedInstruction(bytes);
	this->instruction_list.push(instruction);

	std::cout << "Was pointing to:" << this->lift_pointer;
	this->lift_pointer += instruction.get_instruction_length();
	std::cout << ". Now pointing to: " << this->lift_pointer << std::endl;
}

FetchedInstruction Fetcher::get_next_instruction_to_execute() {
	if (this->instruction_list.empty()) {
		this->fetch_another_instruction();
	}
	FetchedInstruction entry = this->instruction_list.front();
	this->instruction_list.pop();
	return entry;
}

int Fetcher::get_lift_pointer() {
	return this->lift_pointer;
};
