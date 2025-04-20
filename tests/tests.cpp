#include "../src/memory/Memory.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

TEST(tests, test_cartridge) {
	uint8_t test_cartridge[] = {
		// empty logo
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		// Title
		'M',
		'Y',
		' ',
		'C',
		'A',
		'R',
		'T',
		'R',
		'I',
		'D',
		'G',
		'E',
		' ',
		' ',
		' ',
		' ',
		// New Licensee Code
		'0',
		'1',
		// SGB Flag
		0x00,
		// Cartridge Type
		0x03,
		// ROM Size
		0x01,
		// RAM Size
		0x05,
		// Destination Code
		0x01,
		// Old Licensee Code
		0x33,
		// Version Number
		0x01,
		// Header Checksum
		0x00,
		// Global Checksum
		0x23,
		0x14,
	};
	CartridgeHeader cartridge = CartridgeHeader(test_cartridge);
	ASSERT_EQ(cartridge.title, "MY CARTRIDGE    ");
	ASSERT_EQ(cartridge.licensee_code, "Nintendo Research & Development 1");
	ASSERT_EQ(cartridge.cgb_flag, ' ');
	ASSERT_EQ(cartridge.sgb_flag, 0x00);
	ASSERT_EQ(cartridge.cartridge_type, "MBC1+RAM+BATTERY");
	ASSERT_EQ(cartridge.num_rom_banks, 4);
	ASSERT_EQ(cartridge.num_ram_banks, 8);
	ASSERT_EQ(cartridge.destination, "Overseas Only");
	ASSERT_EQ(cartridge.version_number, 1);
	ASSERT_EQ(cartridge.header_checksum, 0x00);
	ASSERT_EQ(cartridge.global_checksum, 0x1423);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
