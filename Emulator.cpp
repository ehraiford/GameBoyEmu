#include "Emulator.h"
#include <iostream>

std::shared_ptr<Emulator> Emulator::instance = nullptr;

Emulator::Emulator() : next_device_id(0) {}

std::shared_ptr<Emulator> Emulator::get_instance() {
    static std::shared_ptr<Emulator> instance(new Emulator());
    return instance;
}

void Emulator::tick_devices() {
    for (const auto& [id, device] : devices) {
        device->tick();
    }
}

int Emulator::get_next_device_id() {  // Add this to Emulator.cpp
    uint16_t next_id = next_device_id;
    next_device_id += 1;
    return next_id;
}

int Emulator::register_device(std::unique_ptr<Device> device) {
    int id = get_next_device_id();
    devices[id] = std::move(device);
    return id;
}

void Emulator::unregister_device(int id) {
    devices.erase(id);
}

void Emulator::print_devices() const {
    for (const auto& [id, device] : devices) {
        std::cout << "Device: " << id << " -> " << device->name << std::endl;
    }
}
