#ifndef EMULATOR_H
#define EMULATOR_H

#include <unordered_map>
#include <memory>
#include "Device.h"

class Emulator {
    static std::shared_ptr<Emulator> instance;
    std::unordered_map <uint16_t, std::shared_ptr<Device> > devices;
    uint16_t next_device_id;

    Emulator();  // Private constructor

    int get_next_device_id();

public:
    static std::shared_ptr<Emulator> get_instance();
    void tick_devices();
    int register_device(std::unique_ptr<Device> device);
    void unregister_device(int id);
    void print_devices() const;
};

#endif // EMULATOR_H
