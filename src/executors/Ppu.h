#pragma once
#include "../memory/DataBus.h"

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
	void temp_track_tiles();
	Ppu(VideoRam*, ObjectAttributeMemory*);
};
