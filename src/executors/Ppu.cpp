#include "Ppu.h"

Ppu::Ppu(VideoRam* v_ram, ObjectAttributeMemory* oam) : v_ram(v_ram), oam(oam) {
}

void Ppu::render_frame_buffer() {

};

uint8_t isolate_bit(uint8_t byte, uint8_t bit_index) {
	return ((byte >> bit_index) & 1);
};

void temp_render_tile(uint8_t* starting_byte) {
	bool is_empty = true;
	std::string tile = "";
	for (int i = 0; i < 16; i += 2) {
		uint8_t byte_0 = *(starting_byte + i);
		uint8_t byte_1 = *(starting_byte + i + 1);
		if (byte_0 != 0 || byte_1 != 0) {
			is_empty = false;
		}
		for (int bit_index = 7; bit_index >= 0; bit_index--) {
			uint8_t value = isolate_bit(byte_0, bit_index) + (isolate_bit(byte_1, bit_index) * 2);
			tile += value;
		}
		tile += '\n';
	}
	if (!is_empty) {
		std::cout << tile << std::endl;
	}
};

void Ppu::temp_track_tiles() {
	for (int i = 0; i < 0x17ff; i += 16) {
		temp_render_tile(this->v_ram->get_memory_ptr(i));
	}
};