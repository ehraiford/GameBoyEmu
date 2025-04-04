#include "DataBus.h"

class Sprite {
	alignas(uint32_t) uint8_t y_position;
	uint8_t x_position;
	uint8_t tile_index;
	uint8_t attributes;
};

class Oam {
	Sprite sprites[40] = {};
};

enum SpriteFlags { Priority = 128, YFlip = 64, XFlip = 32, DmgPalette = 16, Bank = 8, CGBPalette = 0 };
class Ppu : public Memory {
	DataBus *data_bus;
	uint8_t vram[0x1800] = {};
	uint8_t tile_map_0[0x400] = {};
	uint8_t tile_map_1[0x400] = {};
	uint8_t oam_dma_register = 0;
	Oam oam;
	uint8_t scy;
	uint8_t scx;

  public:
	void render_frame_buffer();
	void write_to_oam_dma_register(uint8_t value);
};
