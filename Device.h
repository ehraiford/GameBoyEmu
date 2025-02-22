#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
public:
    std::string name;
    int tick_frequency; 

    virtual void tick() = 0;
    virtual ~Device() = default;
};

#endif // DEVICE_H
