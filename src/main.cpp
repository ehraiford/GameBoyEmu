#include <iostream>
#include <iostream>
#include <thread>
#include "Cpu.h"
#include "Ram.h"
#include "Opcodes.h"
#include "../gui/fast_emu_gui/fast_emu_gui.h"

void emulator()
{
    update_register_value("General Purpose", "R1", 0x1000);
    Cpu cpu = Cpu();
    Ram ram = Ram();
}

int main()
{

    std::thread emu_thread(emulator);
    start_fast_emu_gui();
    emu_thread.join();
    return 0;
};
