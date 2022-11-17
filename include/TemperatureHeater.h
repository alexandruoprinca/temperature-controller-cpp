#pragma once

#include "ITemperatureHeater.h"

class TemperatureHeater : public ITemperatureHeater
{
public:
    // this could be marked const as it doesn't change any inside state
    // but in a real case scenario i think it will make changes over it's internal state
    bool raiseTemperature(float target_temperature) override;
};