#include "Ppu.h"
#include "../../gui/fast_emu_gui/fast_emu_gui.h"

void Ppu::render_frame_buffer() {

};
void Ppu::write_to_oam_dma_register(uint8_t value) {
	this->oam_dma_register = value;
	uint16_t source_address = value << 8;
	this->data_bus->get_memory(source_address);
};