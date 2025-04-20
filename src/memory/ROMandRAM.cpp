// TODO: All of these are currently stubbed out just to appease the linker.
// TODO: They will be implemented more properly in due time.

#include "Memory.h"
#include <iostream>

void CartridgeHeader::print_cartridge_data() {
	std::cout << this->title << std::endl;
	std::cout << "Licensee: " + this->licensee_code << std::endl;
	std::cout << "Cartridge Type: " + this->cartridge_type << std::endl;
	std::cout << "Number of ROM Banks: " << static_cast<int>(this->num_rom_banks) << std::endl;
	std::cout << "Number of RAM Banks: " << static_cast<int>(this->num_ram_banks) << std::endl;
	std::cout << "Destination: " + this->destination << std::endl;
	std::cout << "Version Number: " << static_cast<int>(this->version_number) << std::endl;
	std::cout << "Header Checksum: " << static_cast<int>(this->header_checksum) << std::endl;
	std::cout << "Global Checksum: " << this->global_checksum << std::endl;
	std::cout << "CGB Flag: " << static_cast<int>(this->cgb_flag) << std::endl;
	std::cout << "SGB Flag: " << static_cast<int>(this->sgb_flag) << std::endl;
}

std::string decode_new_licensee_code(std::string code) {
	if (code == "00")
		return "None";
	else if (code == "01")
		return "Nintendo Research & Development 1";
	else if (code == "08")
		return "Capcom";
	else if (code == "13")
		return "EA (Electronic Arts)";
	else if (code == "18")
		return "Hudson Soft";
	else if (code == "19")
		return "B-AI";
	else if (code == "20")
		return "KSS";
	else if (code == "22")
		return "Planning Office WADA";
	else if (code == "24")
		return "PCM Complete";
	else if (code == "25")
		return "San-X";
	else if (code == "28")
		return "Kemco";
	else if (code == "29")
		return "SETA Corporation";
	else if (code == "30")
		return "Viacom";
	else if (code == "31")
		return "Nintendo";
	else if (code == "32")
		return "Bandai";
	else if (code == "33")
		return "Ocean Software/Acclaim Entertainment";
	else if (code == "34")
		return "Konami";
	else if (code == "35")
		return "HectorSoft";
	else if (code == "37")
		return "Taito";
	else if (code == "38")
		return "Hudson Soft";
	else if (code == "39")
		return "Banpresto";
	else if (code == "41")
		return "Ubi Soft1";
	else if (code == "42")
		return "Atlus";
	else if (code == "44")
		return "Malibu Interactive";
	else if (code == "46")
		return "Angel";
	else if (code == "47")
		return "Bullet-Proof Software";
	else if (code == "49")
		return "Irem";
	else if (code == "50")
		return "Absolute";
	else if (code == "51")
		return "Acclaim Entertainment";
	else if (code == "52")
		return "Activision";
	else if (code == "53")
		return "Sammy USA Corporation";
	else if (code == "54")
		return "Konami";
	else if (code == "55")
		return "Hi Tech Expressions";
	else if (code == "56")
		return "LJN";
	else if (code == "57")
		return "Matchbox";
	else if (code == "58")
		return "Mattel";
	else if (code == "59")
		return "Milton Bradley Company";
	else if (code == "60")
		return "Titus Interactive";
	else if (code == "61")
		return "Virgin Games Ltd.";
	else if (code == "64")
		return "Lucasfilm Games";
	else if (code == "67")
		return "Ocean Software";
	else if (code == "69")
		return "EA (Electronic Arts)";
	else if (code == "70")
		return "Infogrames";
	else if (code == "71")
		return "Interplay Entertainment";
	else if (code == "72")
		return "Broderbund";
	else if (code == "73")
		return "Sculptured Software";
	else if (code == "75")
		return "The Sales Curve Limited";
	else if (code == "78")
		return "THQ";
	else if (code == "79")
		return "Accolade";
	else if (code == "80")
		return "Misawa Entertainment";
	else if (code == "83")
		return "lozc";
	else if (code == "86")
		return "Tokuma Shoten";
	else if (code == "87")
		return "Tsukuda Original";
	else if (code == "91")
		return "Chunsoft Co.";
	else if (code == "92")
		return "Video System";
	else if (code == "93")
		return "Ocean Software/Acclaim Entertainment";
	else if (code == "95")
		return "Varie";
	else if (code == "96")
		return "Yonezawa/s’pal";
	else if (code == "97")
		return "Kaneko";
	else if (code == "99")
		return "Pack-In-Video";
	else if (code == "9H")
		return "Bottom Up";
	else if (code == "A4")
		return "Konami (Yu-Gi-Oh!)";
	else if (code == "BL")
		return "MTO";
	else if (code == "DK")
		return "Kodansha";
	else
		return "Invalid New Licensee Code: " + code;
}

std::string decode_old_licensee_code(uint8_t code) {
	switch (code) {
	case 0x00:
		return "None";
	case 0x01:
		return "Nintendo";
	case 0x08:
		return "Capcom";
	case 0x09:
		return "HOT-B";
	case 0x0A:
		return "Jaleco";
	case 0x0B:
		return "Coconuts Japan";
	case 0x0C:
		return "Elite Systems";
	case 0x13:
		return "EA (Electronic Arts)";
	case 0x18:
		return "Hudson Soft";
	case 0x19:
		return "ITC Entertainment";
	case 0x1A:
		return "Yanoman";
	case 0x1D:
		return "Japan Clary";
	case 0x1F:
		return "Virgin Games Ltd.";
	case 0x24:
		return "PCM Complete";
	case 0x25:
		return "San-X";
	case 0x28:
		return "Kemco";
	case 0x29:
		return "SETA Corporation";
	case 0x30:
		return "Infogrames";
	case 0x31:
		return "Nintendo";
	case 0x32:
		return "Bandai";
	case 0x33:
		return "Indicates that the New licensee code should be used instead.";
	case 0x34:
		return "Konami";
	case 0x35:
		return "HectorSoft";
	case 0x38:
		return "Capcom";
	case 0x39:
		return "Banpresto";
	case 0x3C:
		return "Entertainment Interactive (stub)";
	case 0x3E:
		return "Gremlin";
	case 0x41:
		return "Ubi Soft";
	case 0x42:
		return "Atlus";
	case 0x44:
		return "Malibu Interactive";
	case 0x46:
		return "Angel";
	case 0x47:
		return "Spectrum HoloByte";
	case 0x49:
		return "Irem";
	case 0x4A:
		return "Virgin Games Ltd.";
	case 0x4D:
		return "Malibu Interactive";
	case 0x4F:
		return "U.S. Gold";
	case 0x50:
		return "Absolute";
	case 0x51:
		return "Acclaim Entertainment";
	case 0x52:
		return "Activision";
	case 0x53:
		return "Sammy USA Corporation";
	case 0x54:
		return "GameTek";
	case 0x55:
		return "Park Place";
	case 0x56:
		return "LJN";
	case 0x57:
		return "Matchbox";
	case 0x59:
		return "Milton Bradley Company";
	case 0x5A:
		return "Mindscape";
	case 0x5B:
		return "Romstar";
	case 0x5C:
		return "Naxat Soft";
	case 0x5D:
		return "Tradewest";
	case 0x60:
		return "Titus Interactive";
	case 0x61:
		return "Virgin Games Ltd.3";
	case 0x67:
		return "Ocean Software";
	case 0x69:
		return "EA (Electronic Arts)";
	case 0x6E:
		return "Elite Systems";
	case 0x6F:
		return "Electro Brain";
	case 0x70:
		return "Infogrames";
	case 0x71:
		return "Interplay Entertainment";
	case 0x72:
		return "Broderbund";
	case 0x73:
		return "Sculptured Software";
	case 0x75:
		return "The Sales Curve Limited";
	case 0x78:
		return "THQ";
	case 0x79:
		return "Accolade15";
	case 0x7A:
		return "Triffix Entertainment";
	case 0x7C:
		return "MicroProse";
	case 0x7F:
		return "Kemco";
	case 0x80:
		return "Misawa Entertainment";
	case 0x83:
		return "LOZC G.";
	case 0x86:
		return "Tokuma Shoten";
	case 0x8B:
		return "Bullet-Proof Software";
	case 0x8C:
		return "Vic Tokai Corp.";
	case 0x8E:
		return "Ape Inc.";
	case 0x8F:
		return "I’Max";
	case 0x91:
		return "Chunsoft Co.";
	case 0x92:
		return "Video System";
	case 0x93:
		return "Tsubaraya Productions";
	case 0x95:
		return "Varie";
	case 0x96:
		return "Yonezawa19/S’Pal";
	case 0x97:
		return "Kemco";
	case 0x99:
		return "Arc";
	case 0x9A:
		return "Nihon Bussan";
	case 0x9B:
		return "Tecmo";
	case 0x9C:
		return "Imagineer";
	case 0x9D:
		return "Banpresto";
	case 0x9F:
		return "Nova";
	case 0xA1:
		return "Hori Electric";
	case 0xA2:
		return "Bandai";
	case 0xA4:
		return "Konami";
	case 0xA6:
		return "Kawada";
	case 0xA7:
		return "Takara";
	case 0xA9:
		return "Technos Japan";
	case 0xAA:
		return "Broderbund";
	case 0xAC:
		return "Toei Animation";
	case 0xAD:
		return "Toho";
	case 0xAF:
		return "Namco";
	case 0xB0:
		return "Acclaim Entertainment";
	case 0xB1:
		return "ASCII Corporation or Nexsoft";
	case 0xB2:
		return "Bandai";
	case 0xB4:
		return "Square Enix";
	case 0xB6:
		return "HAL Laboratory";
	case 0xB7:
		return "SNK";
	case 0xB9:
		return "Pony Canyon";
	case 0xBA:
		return "Culture Brain";
	case 0xBB:
		return "Sunsoft";
	case 0xBD:
		return "Sony Imagesoft";
	case 0xBF:
		return "Sammy Corporation";
	case 0xC0:
		return "Taito";
	case 0xC2:
		return "Kemco";
	case 0xC3:
		return "Square";
	case 0xC4:
		return "Tokuma Shoten";
	case 0xC5:
		return "Data East";
	case 0xC6:
		return "Tonkin House";
	case 0xC8:
		return "Koei";
	case 0xC9:
		return "UFL";
	case 0xCA:
		return "Ultra Games";
	case 0xCB:
		return "VAP, Inc.";
	case 0xCC:
		return "Use Corporation";
	case 0xCD:
		return "Meldac";
	case 0xCE:
		return "Pony Canyon";
	case 0xCF:
		return "Angel";
	case 0xD0:
		return "Taito";
	case 0xD1:
		return "SOFEL (Software Engineering Lab)";
	case 0xD2:
		return "Quest";
	case 0xD3:
		return "Sigma Enterprises";
	case 0xD4:
		return "ASK Kodansha Co.";
	case 0xD6:
		return "Naxat Soft";
	case 0xD7:
		return "Copya System";
	case 0xD9:
		return "Banpresto";
	case 0xDA:
		return "Tomy";
	case 0xDB:
		return "LJN";
	case 0xDD:
		return "Nippon Computer Systems";
	case 0xDE:
		return "Human Ent.";
	case 0xDF:
		return "Altron";
	case 0xE0:
		return "Jaleco";
	case 0xE1:
		return "Towa Chiki";
	case 0xE2:
		return "Yutaka";
	case 0xE3:
		return "Varie";
	case 0xE5:
		return "Epoch";
	case 0xE7:
		return "Athena";
	case 0xE8:
		return "Asmik Ace Entertainment";
	case 0xE9:
		return "Natsume";
	case 0xEA:
		return "King Records";
	case 0xEB:
		return "Atlus";
	case 0xEC:
		return "Epic/Sony Records";
	case 0xEE:
		return "IGS";
	case 0xF0:
		return "A Wave";
	case 0xF3:
		return "Extreme Entertainment";
	case 0xFF:
		return "LJN";
	default:
		return "Invalid Old Licensee Code: " + code;
	}
}

std::string decode_cartridge_type(uint8_t byte) {
	switch (byte) {
	case 0x00:
		return "ROM ONLY";
	case 0x01:
		return "MBC1";
	case 0x02:
		return "MBC1+RAM";
	case 0x03:
		return "MBC1+RAM+BATTERY";
	case 0x05:
		return "MBC2";
	case 0x06:
		return "MBC2+BATTERY";
	case 0x08:
		return "ROM+RAM 9";
	case 0x09:
		return "ROM+RAM+BATTERY 9";
	case 0x0B:
		return "MMM01";
	case 0x0C:
		return "MMM01+RAM";
	case 0x0D:
		return "MMM01+RAM+BATTERY";
	case 0x0F:
		return "MBC3+TIMER+BATTERY";
	case 0x10:
		return "MBC3+TIMER+RAM+BATTERY 10";
	case 0x11:
		return "MBC3";
	case 0x12:
		return "MBC3+RAM 10";
	case 0x13:
		return "MBC3+RAM+BATTERY 10";
	case 0x19:
		return "MBC5";
	case 0x1A:
		return "MBC5+RAM";
	case 0x1B:
		return "MBC5+RAM+BATTERY";
	case 0x1C:
		return "MBC5+RUMBLE";
	case 0x1D:
		return "MBC5+RUMBLE+RAM";
	case 0x1E:
		return "MBC5+RUMBLE+RAM+BATTERY";
	case 0x20:
		return "MBC6";
	case 0x22:
		return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
	case 0xFC:
		return "POCKET CAMERA";
	case 0xFD:
		return "BANDAI TAMA";
	case 0xFE:
		return "HuC3";
	case 0xFF:
		return "HuC1+RAM+BATTERY";
	default:
		return "Unrecognized Cartridge Type: " + static_cast<int>(byte);
	}
}

/// @brief This should start at 0x104 of the ROM
/// @param header_ptr
CartridgeHeader::CartridgeHeader(uint8_t* header_ptr) {
	uint8_t* start_ptr = header_ptr;
	std::copy(header_ptr, header_ptr + 48, this->logo.begin());
	header_ptr += 48;

	// title is 0x134-143
	this->title = "";
	for (int i = 0; i < 16; i++, header_ptr++) {
		this->title += *header_ptr;
	}

	// cgb flag is 	0x143
	this->cgb_flag = *(header_ptr - 1);

	// new licensee (if we care about it) is 0x144-0x145
	// we're gonna set it as if we do and replace it later if we don't.
	std::string license_chars(reinterpret_cast<char*>(header_ptr), 2);
	this->licensee_code = decode_new_licensee_code(license_chars);
	header_ptr += 2;

	// sgb flag is 0x146
	this->sgb_flag = *header_ptr;
	header_ptr += 1;

	// cartridge type is at 0x147
	this->cartridge_type = decode_cartridge_type(*header_ptr);
	header_ptr += 1;

	// number of rom banks is at 0x148. It's 32 KB of ROM per bank. Num banks is 2 << value.
	this->num_rom_banks = (2 << *header_ptr);
	header_ptr += 1;

	// number of ram banks is at 0x149. Each bank has 8Kb of RAM.
	switch (*header_ptr) {
	case 0:
		this->num_ram_banks = 0;
		break;
	case 1:
		this->num_ram_banks = 0;
		break;
	case 2:
		this->num_ram_banks = 1;
		break;
	case 3:
		this->num_ram_banks = 4;
		break;
	case 4:
		this->num_ram_banks = 16;
		break;
	case 5:
		this->num_ram_banks = 8;
		break;
	default:
		this->num_ram_banks = 0;
		break;
	}
	header_ptr += 1;

	// Destination Code is at 0x14A
	if (*header_ptr == 0) {
		this->destination = "Japan";
	} else {
		this->destination = "Overseas Only";
	}
	header_ptr += 1;

	// Old Licensee is at 0x14b
	if (*header_ptr != 0x33) {
		this->licensee_code = decode_old_licensee_code(*header_ptr);
	}
	header_ptr += 1;

	// the version number of the ROM is at 0x14C
	this->version_number = *header_ptr;
	header_ptr += 1;

	// 0x14d is the header checksum.
	this->header_checksum = *header_ptr;
	header_ptr += 1;

	// Finally, 0x14e-0x14f is the global checksum
	this->global_checksum = static_cast<uint16_t>(header_ptr[0]) | (static_cast<uint16_t>(header_ptr[1]) << 8);
};

uint8_t Rom::get_memory(uint16_t address) {
	uint8_t value = this->bank_0[address];
	return value;
};
std::array<uint8_t, 3> Rom::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->bank_0[address], this->bank_0[address + 1], this->bank_0[address + 2]};
	return bytes;
}
uint8_t* Rom::get_memory_ptr(uint16_t address) {
	return &this->bank_0[address];
};
void Rom::set_memory(uint16_t address, uint8_t value) {
	if (address < 0x4000) {
		this->bank_0[address] = value;
	} else if (address < 0x8000) {
		this->bank_1[address - 0x4000] = value;
	} else {
		// TODO Handle data that goes beyond the first 2 banks here
	}
};

void Rom::load_data_as_cartridge(const std::vector<uint8_t>& data) {
	CartridgeHeader header = CartridgeHeader((uint8_t*)data.data() + 0x104);
	// header.print_cartridge_data();
	for (int i = 0; i < data.size(); ++i) {
		if (i > 32770) {
			printf("Cannot finish loading data because it extends beyond the scope of the first two banks and beyond "
				   "that has not been modeled yet.\n");
			return;
		}
		this->set_memory(i, data[i]);
	}
};

uint8_t VideoRam::get_memory(uint16_t address) {
	return this->memory[address];
};
std::array<uint8_t, 3> VideoRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
};
uint8_t* VideoRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
void VideoRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t ExternalRam::get_memory(uint16_t address) {
	return this->memory[address];
};
std::array<uint8_t, 3> ExternalRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
uint8_t* ExternalRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
void ExternalRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t WorkRam::get_memory(uint16_t address) {
	return this->bank_0[address];
};
uint8_t* WorkRam::get_memory_ptr(uint16_t address) {
	return &this->bank_0[address];
};
std::array<uint8_t, 3> WorkRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->bank_0[address], this->bank_0[address + 1], this->bank_0[address + 2]};
	return bytes;
}
void WorkRam::set_memory(uint16_t address, uint8_t value) {
	this->bank_0[address] = value;
};

uint8_t ObjectAttributeMemory::get_memory(uint16_t address) {
	return this->memory[address];
};
uint8_t* ObjectAttributeMemory::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
std::array<uint8_t, 3> ObjectAttributeMemory::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
void ObjectAttributeMemory::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};

uint8_t HighRam::get_memory(uint16_t address) {
	return this->memory[address];
};
uint8_t* HighRam::get_memory_ptr(uint16_t address) {
	return &this->memory[address];
};
std::array<uint8_t, 3> HighRam::get_instruction(uint16_t address) {
	std::array<uint8_t, 3> bytes = {this->memory[address], this->memory[address + 1], this->memory[address + 2]};
	return bytes;
}
void HighRam::set_memory(uint16_t address, uint8_t value) {
	this->memory[address] = value;
};
