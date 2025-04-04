#include "DataBus.h"

class Ppu {
	DataBus *data_bus;
	uint8_t vram[0x1800] = {};
	uint8_t tile_map_0[0x400] = {};
	uint8_t tile_map_1[0x400] = {};
	uint8_t oam[0xA0] = {};
	uint8_t scy;
	uint8_t scx;

  public:
	void render_frame_buffer();
};
