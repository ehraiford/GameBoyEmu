#ifndef RAM_H
#define RAM_H

#include "Device.h"
#include <memory>
#include <optional>

template <typename T>
class Ram : public Device {
    std::unique_ptr<T[]> memory;
    size_t length;

public:
    Ram(const std::string& name, int length);
    std::optional<T> read_from_address(size_t address);
    bool write_to_address(size_t address, T value);
};

#include "Ram.tpp" // Include template implementation

#endif // RAM_H
