#include "Ram.h"

template <typename T>
Ram<T>::Ram(const std::string& name, int length) {
    this->name = name;
    this->length = length;
    this->memory = std::make_unique<T[]>(length);

    for (size_t i = 0; i < length; i++) {
        this->memory[i] = 0;
    }
}

template <typename T>
std::optional<T> Ram<T>::read_from_address(size_t address) {
    if (address < this->length) {
        return this->memory.get()[address];
    }
    return std::nullopt;
}

template <typename T>
bool Ram<T>::write_to_address(size_t address, T value) {
    if (address < this->length) {
        this->memory.get()[address] = value;
        return true;
    }
    return false;
}
