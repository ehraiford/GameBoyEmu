#include <iostream>
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <fstream>
#include "Cpu.h"
#include "Ram.h"
#include "Opcodes.h"
#include "../gui/fast_emu_gui/fast_emu_gui.h"

class FetchedInstruction
{
    JumpTableEntry jump_table_entry;
    std::string disassembly;

public:
    FetchedInstruction(std::array<uint8_t, 3> bytes)
    {
        if (bytes[0] == 0xCB)
        {
            this->jump_table_entry = jump_table_cb[bytes[1]];
        }
        else
        {
            this->jump_table_entry = jump_table[bytes[0]];
        }
        this->disassembly = this->jump_table_entry.get_disassembly(bytes);
    };
    uint8_t get_instruction_length()
    {
        return this->jump_table_entry.op_code->get_length();
    };
    std::string get_disassembly()
    {
        return this->disassembly;
    }
};
class Fetcher
{
    std::queue<FetchedInstruction> instruction_list;
    uint16_t lift_pointer;
    Ram *ram;

public:
    Fetcher(Ram *ram)
    {
        this->ram = ram;
        this->lift_pointer = 0;
        instruction_list = std::queue<FetchedInstruction>();
    };

    void fetch_next_instruction()
    {
        std::array<uint8_t, 3> bytes = this->ram->get_instruction(this->lift_pointer);
        FetchedInstruction instruction = FetchedInstruction(bytes);
        this->instruction_list.push(instruction);

        this->lift_pointer += instruction.get_instruction_length();
    };
    FetchedInstruction get_next_entry()
    {
        if (this->instruction_list.empty())
        {
            this->fetch_next_instruction();
        }
        FetchedInstruction entry = this->instruction_list.front();
        this->instruction_list.pop();
        return entry;
    };
};

void load_binary_to_ram(Ram &ram, const std::string &file_path)
{
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Failed to open binary file: " << file_path << std::endl;
        return;
    }

    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    ram.load_data(buffer);
    file.close();
}

void emulator(const std::string &file_path)
{
    Cpu cpu = Cpu();
    Ram ram = Ram();

    load_binary_to_ram(ram, file_path);
    Fetcher fetcher = Fetcher(&ram);
    for (int i = 0; i < 100; i++)
    {
        fetcher.fetch_next_instruction();
    }

    for (int i = 0; i < 110; i++)
    {
        FetchedInstruction entry = fetcher.get_next_entry();
        std::cout << "Next Instruction: " << entry.get_disassembly() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path_to_binary_file>" << std::endl;
        return 1;
    }

    std::string file_path = argv[1];
    std::thread emu_thread(emulator, file_path);
    // start_fast_emu_gui();
    emu_thread.join();
    return 0;
};