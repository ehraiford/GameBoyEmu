#ifndef FETCH_DECODE_H
#define FETCH_DECODE_H

#include "Opcodes.h"
#include "Ram.h"
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
  Ram *ram;

public:
  Fetcher(Ram *ram);
  void fetch_next_instruction();
  FetchedInstruction get_next_entry();
};

#endif // FETCH_DECODE_H
