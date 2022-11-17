#pragma once
#include <optional>

class ITemperatureSensor
{
public:
    virtual std::optional<float> getCurrentValue() const = 0;
    virtual ~ITemperatureSensor(){};
};