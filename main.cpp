#include "Emulator.h"
#include "Cpu.h"
#include <iostream>

int main() {
    auto instance_1 = Emulator::get_instance();
    auto instance_2 = Emulator::get_instance();
    auto cpu = std::make_unique<Cpu>("THIS CPU", 1, 0);

    int cpu_id = instance_1->register_device(std::move(cpu));
    instance_1->print_devices();
    instance_2->print_devices();

    instance_2->tick_devices();

    return 0;
}
