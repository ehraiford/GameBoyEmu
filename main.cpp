#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

class Device {
public:
    int tick_frequency; 
    string name;

    virtual void tick() = 0;
    virtual ~Device() = default;
};

class Emulator {
    static std::shared_ptr<Emulator> instance;
    std::unordered_map<int, std::shared_ptr<Device>> devices;
    int next_device_id;

    Emulator() : next_device_id(0) {}

    int get_next_device_id() {
        int next_id = next_device_id;
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

    std::optional<std::shared_ptr<Device>> get_device_by_id(int id) {
        auto maybe_found = devices.find(id);
        if (maybe_found != devices.end()) {
            return maybe_found->second;
        } else {
            return std::nullopt;
        }
    }
};

class Cpu : public Device {
public:
    Cpu(const string& name) {
        this->name = name;
    }

    void tick() override {
        auto instance = Emulator::get_instance();
        instance.get()->print_devices();
    }
};
class Ram: public Device {
    std::unique_ptr<uint8_t[]> memory;
    size_t word_size_in_bytes;
    size_t length;

    public:
    Ram(const string& name, int word_size_in_bytes, int length) {
        this->name = name;
        this->length = length;
        this->word_size_in_bytes = word_size_in_bytes;
    }
};

std::shared_ptr<Emulator> Emulator::instance = nullptr;

int main() {
    auto instance_1 = Emulator::get_instance();
    auto instance_2 = Emulator::get_instance();
    auto cpu = std::make_unique<Cpu>("THIS CPU");

    int cpu_id = instance_1->register_device(std::move(cpu));
    instance_1->print_devices(); 
    instance_2->print_devices();

    instance_2.get()->tick_devices();

    return 0;
}
