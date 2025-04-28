#pragma once
#include "../memory/DataBus.h"

class Tile {
	std::array<uint8_t, 16> bytes;

  public:
	Tile();
	Tile(uint8_t* ptr);
	void display();
};

class Sprite {
	alignas(uint32_t) uint8_t y_position;
	uint8_t x_position;
	uint8_t tile_index;
	uint8_t attributes;
};

enum SpriteFlags { Priority = 128, YFlip = 64, XFlip = 32, DmgPalette = 16, Bank = 8, CGBPalette = 0 };

class Ppu {
	VideoRam* v_ram;
	ObjectAttributeMemory* oam;

  public:
	void render_frame_buffer();
	Ppu(VideoRam*, ObjectAttributeMemory*);
	std::array<Tile, 384> get_tiles();
};
