#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

class Device {
public:
    string name;
    int tick_frequency; 

    virtual void tick() = 0;
    virtual ~Device() = default;
};

class Emulator {
    static std::shared_ptr<Emulator> instance;
    std::unordered_map<uint16_t, std::shared_ptr<Device>> devices;
    uint16_t next_device_id;

    Emulator() : next_device_id(0) {}

    int get_next_device_id() {
        uint16_t next_id = next_device_id;
        next_device_id += 1;
        return next_id;
    }
    
    public:
    static std::shared_ptr<Emulator> get_instance() {
        static std::shared_ptr<Emulator> instance(new Emulator());
        return instance;
    }
    
    void tick_devices() {
        for (const auto& [id, device] : devices) {
            device.get()->tick();
        }
    }

    int register_device(std::unique_ptr<Device> device) {
        int id = get_next_device_id();
        devices.insert({id, std::move(device)});  // Move the unique_ptr into the map
        return id;
    }

    void unregister_device(int id) {
        devices.erase(id);
    }

    void print_devices() const {
        for (const auto& [id, device] : devices) {
            std::cout << "Device: " << id << " -> " << device->name << std::endl;
        }
    }

    std::optional<std::shared_ptr<Device>> get_device_by_id(uint16_t id) {
        auto maybe_found = devices.find(id);
        if (maybe_found != devices.end()) {
            return maybe_found->second;
        } else {
            return std::nullopt;
        }
    }
};

class Cpu : public Device {
    uint32_t program_counter;
    uint32_t instruction_pointer;
    uint16_t ram_id;
public:
    Cpu(const string& name, uint16_t ram_id, uint32_t starting_instruction_pointer) {
        this->program_counter = 0;
        this->instruction_pointer = starting_instruction_pointer;
        this->name = name;
        this->ram_id = ram_id;
    }

    void tick() override {
        
    }
};

template <typename T>
class Ram: public Device {
    std::unique_ptr<T[]> memory;
    size_t length;

    public:
    Ram(const string& name, int length) {
        this->emulator_ptr = Emulator::get_instance();
        this->name = name;
        this->length = length;
        this->memory = std::make_unique<T[]>(length);
        
        for (size_t i=0;i<length;i++) {
            this->memory[i] = 0;
        }
    }
    std::optional<T> read_from_address(size_t address) {
        if (address < this->length) {
            return this->memory.get()[address];
        } else {
            return std::nullopt;
        }
    }
    bool write_to_address(size_t address, T value) {
        if (address < this->length) {
            this->memory.get()[address] = value;
            return true;
        } else {
            return false;
        }
    }
    
};

std::shared_ptr<Emulator> Emulator::instance = nullptr;

int main() {
    auto instance_1 = Emulator::get_instance();
    auto instance_2 = Emulator::get_instance();
    auto cpu = std::make_unique<Cpu>("THIS CPU", 1, 0);

    int cpu_id = instance_1->register_device(std::move(cpu));
    instance_1->print_devices(); 
    instance_2->print_devices();

    instance_2.get()->tick_devices();

    return 0;
}
