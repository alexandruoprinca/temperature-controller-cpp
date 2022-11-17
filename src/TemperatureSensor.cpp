#include "../include/TemperatureSensor.h"

#include "../include/TemperatureValueProvider.h"

std::optional<float> TemperatureSensor::getCurrentValue() const
{
    return TemperatureValueProvider::getCurrentValue();
}