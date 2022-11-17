#pragma once

#include "ITemperatureCooler.h"

class TemperatureCooler: public ITemperatureCooler
{
public:
    bool lowerTemperature(float target_temperature) override;
};