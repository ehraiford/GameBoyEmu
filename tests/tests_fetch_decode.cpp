#include "../src/core/Memory.h"
#include "../src/instructions/FetchDecode.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

TEST(FetchDecodeTests, TestDecoding) {
	Rom ram = Rom();
	std::vector<uint8_t> data = {
		0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32, 0xcb, 0x7c, 0x20, 0xfb, 0x21, 0x26, 0xff, 0x0e, 0x11, 0x3e,
		0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3, 0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0, 0x47, 0x11, 0x04, 0x01,
		0x21, 0x10, 0x80, 0x1a, 0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b, 0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8,
		0x00, 0x06, 0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9, 0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99,
		0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20, 0xf9, 0x2e, 0x0f, 0x18, 0xf3, 0x67, 0x3e, 0x64, 0x57, 0xe0,
		0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04, 0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20,
		0xf7, 0x1d, 0x20, 0xf2, 0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62, 0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64,
		0x20, 0x06, 0x7b, 0xe2, 0x0c, 0x3e, 0x87, 0xe2, 0xf0, 0x42, 0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
		0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04, 0xc5, 0xcb, 0x11, 0x17, 0xc1, 0xcb, 0x11, 0x17, 0x05, 0x20,
		0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9, 0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
		0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd,
		0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e,
		0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c, 0x21, 0x04, 0x01, 0x11, 0xa8, 0x00, 0x1a, 0x13, 0xbe, 0x20,
		0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20, 0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe,
		0x3e, 0x01, 0xe0, 0x50,
	};
	ram.load_data(data);
	Fetcher fetcher = Fetcher(&ram);

	std::vector<std::tuple<std::string, uint8_t>> expected_disassemblies = {
		{"LD SP,$fffe", 0x00},
		{"XOR A", 0x03},
		{"LD HL,$9fff", 0x04},
		{"LD [HLD],A", 0x07},
		{"BIT 7,H", 0x08},
		{"JR NZ,$fb", 0x0a},
		{"LD HL,$ff26", 0x0c},
		{"LD C,$11", 0x0f},
		{"LD A,$80", 0x11},
		{"LD [HLD],A", 0x13},
		{"LDH [C],A", 0x14},
		{"INC C", 0x15},
		{"LD A,$f3", 0x16},
		{"LDH [C],A", 0x18},
		{"LD [HLD],A", 0x19},
		{"LD A,$77", 0x1a},
		{"LD [HL],A", 0x1c},
		{"LD A,$fc", 0x1d},
		{"LDH [$47],A", 0x1f},
		{"LD DE,$0104", 0x21},
		{"LD HL,$8010", 0x24},
		{"LD A,[DE]", 0x27},
		{"CALL $0095", 0x28},
		{"CALL $0096", 0x2b},
		{"INC DE", 0x2e},
		{"LD A,E", 0x2f},
		{"CP $34", 0x30},
		{"JR NZ,$f3", 0x32},
		{"LD DE,$00d8", 0x34},
		{"LD B,$08", 0x37},
		{"LD A,[DE]", 0x39},
		{"INC DE", 0x3a},
		{"LD [HLI],A", 0x3b},
		{"INC HL", 0x3c},
		{"DEC B", 0x3d},
		{"JR NZ,$f9", 0x3e},
		{"LD A,$19", 0x40},
		{"LD [$9910],A", 0x42},
		{"LD HL,$992f", 0x45},
		{"LD C,$0c", 0x48},
		{"DEC A", 0x4a},
		{"JR Z,$08", 0x4b},
		{"LD [HLD],A", 0x4d},
		{"DEC C", 0x4e},
		{"JR NZ,$f9", 0x4f},
		{"LD L,$0f", 0x51},
		{"JR $f3", 0x53},
		{"LD H,A", 0x55},
		{"LD A,$64", 0x56},
		{"LD D,A", 0x58},
		{"LDH [$42],A", 0x59},
		{"LD A,$91", 0x5b},
		{"LDH [$40],A", 0x5d},
		{"INC B", 0x5f},
		{"LD E,$02", 0x60},
		{"LD C,$0c", 0x62},
		{"LDH A,[$44]", 0x64},
		{"CP $90", 0x66},
		{"JR NZ,$fa", 0x68},
		{"DEC C", 0x6a},
		{"JR NZ,$f7", 0x6b},
		{"DEC E", 0x6d},
		{"JR NZ,$f2", 0x6e},
		{"LD C,$13", 0x70},
		{"INC H", 0x72},
		{"LD A,H", 0x73},
		{"LD E,$83", 0x74},
		{"CP $62", 0x76},
		{"JR Z,$06", 0x78},
		{"LD E,$c1", 0x7a},
		{"CP $64", 0x7c},
		{"JR NZ,$06", 0x7e},
		{"LD A,E", 0x80},
		{"LDH [C],A", 0x81},
		{"INC C", 0x82},
		{"LD A,$87", 0x83},
		{"LDH [C],A", 0x85},
		{"LDH A,[$42]", 0x86},
		{"SUB B", 0x88},
		{"LDH [$42],A", 0x89},
		{"DEC D", 0x8b},
		{"JR NZ,$d2", 0x8c},
		{"DEC B", 0x8e},
		{"JR NZ,$4f", 0x8f},
		{"LD D,$20", 0x91},
		{"JR $cb", 0x93},
		{"LD C,A", 0x95},
		{"LD B,$04", 0x96},
		{"PUSH BC", 0x98},
		{"RL C", 0x99},
		{"RLA", 0x9b},
		{"POP BC", 0x9c},
		{"RL C", 0x9d},
		{"RLA", 0x9f},
		{"DEC B", 0xa0},
		{"JR NZ,$f5", 0xa1},
		{"LD [HLI],A", 0xa3},
		{"INC HL", 0xa4},
		{"LD [HLI],A", 0xa5},
		{"INC HL", 0xa6},
		{"RET", 0xa7},
		// ... //
		{"LD HL,$0104", 0xe0},
		{"LD DE,$00a8", 0xe3},
		{"LD A,[DE]", 0xe6},
		{"INC DE", 0xe7},
		{"CP A,[HL]", 0xe8},
		{"JR NZ,$fe", 0xe9},
		{"INC HL", 0xeb},
		{"LD A,L", 0xec},
		{"CP $34", 0xed},
		{"JR NZ,$f5", 0xef},
		{"LD B,$19", 0xf1},
		{"LD A,B", 0xf3},
		{"ADD A,[HL]", 0xf4},
		{"INC HL", 0xf5},
		{"DEC B", 0xf6},
		{"JR NZ,$fb", 0xf7},
		{"ADD A,[HL]", 0xf9},
		{"JR NZ,$fe", 0xfa},
		{"LD A,$01", 0xfc},
		{"LDH [$50],A", 0xfe},
	};

	for (int i = 0; i < 101; i++) {
		int address = fetcher.get_lift_pointer();
		FetchedInstruction instruction = fetcher.get_next_instruction_to_execute();
		std::array<uint8_t, 3> bytes = ram.get_instruction(address);
		std::cout << instruction.get_disassembly() << ": ";
		for (int j = 0; j < 3; j++) {
			std::cout << std::format("0b{:08b}, ", bytes[j]);
		}
		std::cout << std::endl;
		ASSERT_EQ(instruction.get_disassembly(), std::get<0>(expected_disassemblies[i]));
		ASSERT_EQ(address, std::get<1>(expected_disassemblies[i]));
	}

	fetcher.set_lift_pointer(0xe0);
	for (int i = 0; i < 20; i++) {
		int address = fetcher.get_lift_pointer();
		FetchedInstruction instruction = fetcher.get_next_instruction_to_execute();
		std::array<uint8_t, 3> bytes = ram.get_instruction(address);
		ASSERT_EQ(instruction.get_disassembly(), std::get<0>(expected_disassemblies[i + 101]));
		ASSERT_EQ(address, std::get<1>(expected_disassemblies[i + 101]));
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
