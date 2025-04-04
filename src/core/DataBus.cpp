#include "DataBus.h"

Cpu *DataBus::get_cpu() {
	return this->cpu;
}
// uint8_t (*)(uint16_t) DataBus::memory_map(uint_16_t address) {
// 	/// todo add the memory map here
// 	return this->ram->get_memory;
// };