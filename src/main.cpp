#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
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

class Lifter
{
    std::vector<JumpTableEntry> instruction_list;
    uint16_t lift_pointer;
    Ram *ram;

    void lift_next_instruction()
    {
        std::array<uint8_t, 3> bytes = this->ram->get_instruction(this->lift_pointer);
        JumpTableEntry instruction;
        if (bytes[0] == 0xCB)
        {
            instruction = jump_table_cb[bytes[1]];
        }
        else
        {
            instruction = jump_table[bytes[0]];
        }

        this->lift_pointer += instruction.op_code->get_length();
    };

public:
};
