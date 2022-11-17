#pragma once
#include "ITemperatureSensor.h"

class TemperatureSensor : public ITemperatureSensor
{
public:
    //returning an optional since in a real scenario this could fail and in case of temperature every value is a valid one
    std::optional<float> getCurrentValue() const override;
};