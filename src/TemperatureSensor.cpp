#include "TemperatureSensor.h"
#include "TemperatureValueProvider.h"

std::optional<float> TemperatureSensor::getCurrentValue() const
{
    return TemperatureValueProvider::getCurrentValue();
}