#include "DataBus.h"
#include "Ppu.h" // Include the header file for the Ppu class

Cpu *DataBus::get_cpu() {
	return this->cpu;
}

void DataBus::set_memory(uint16_t address, uint8_t value) {
	auto device = this->determine_device_from_address(address);
	if (device.has_value()) {
		(*device)->set_memory(address, value);
	} else {
		std::cerr << "Invalid address: " << std::hex << address << std::endl;
	}
};

uint8_t DataBus::get_memory(uint16_t address) {
	auto device = this->determine_device_from_address(address);
	if (device.has_value()) {
		return (*device)->get_memory(address);
	} else {
		std::cerr << "Invalid address: " << std::hex << address << std::endl;
		return 0;
	}
}

std::optional<Memory *> DataBus::determine_device_from_address(uint16_t address) {
	if (address > 0xFFFF) {
		return std::nullopt;
	}
	auto ram_ranges = this->get_ram()->get_address_ranges();
	for (auto range : ram_ranges) {
		if (address >= std::get<0>(range) && address < std::get<1>(range)) {
			return this->get_ram();
		}
	};
	auto ppu_ranges = this->get_ppu()->get_address_ranges();
	for (auto range : ppu_ranges) {
		if (address >= std::get<0>(range) && address < std::get<1>(range)) {
			return this->get_ppu();
		}
	}
};