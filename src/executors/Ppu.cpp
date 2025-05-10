#include "Ppu.h"

uint8_t isolate_bit(uint8_t byte, uint8_t bit_index) {
	return ((byte >> bit_index) & 1);
};

Tile::Tile() {
}
Tile::Tile(uint8_t* ptr) {
	this->bytes = std::array<uint8_t, 16>();
	for (int i = 0; i < 16; i++) {
		this->bytes[i] = *ptr;
		ptr += 1;
	}
}

void Tile::display() {
	std::string tile = "";
	for (int i = 0; i < 16; i += 2) {
		uint8_t byte_0 = this->bytes[i];
		uint8_t byte_1 = this->bytes[i + 1];
		for (int bit_index = 7; bit_index >= 0; bit_index--) {
			uint8_t value = isolate_bit(byte_0, bit_index) + (isolate_bit(byte_1, bit_index) * 2);
			std::string pixel;
			switch (value) {
			case 0:
				pixel = ' ';
				break;
			case 1:
				pixel = "\033[38;5;82m█\033[0m";
				break;
			case 2:
				pixel = "\033[38;5;40m█\033[0m";
				break;
			case 3:
				pixel = "\033[38;5;34m█\033[0m";
				break;
			};
			tile += pixel;
		}
		tile += '\n';
	}
	std::cout << tile << std::endl;
}

Ppu::Ppu(VideoRam* v_ram, ObjectAttributeMemory* oam) : v_ram(v_ram), oam(oam) {
}

void Ppu::render_frame_buffer() {

};

std::array<Tile, 384> Ppu::get_tiles() {
	uint8_t* ptr = this->v_ram->get_memory_ptr(0);
	std::array<Tile, 384> tiles = std::array<Tile, 384>();
	for (int i = 0; i < 384; i++) {
		tiles[i] = Tile(ptr);
		ptr += 16;
	}
	return tiles;
};