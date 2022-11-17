#pragma once

class ITemperatureHeater
{
public:
    virtual bool raiseTemperature(float target_temperature) = 0;
    virtual ~ITemperatureHeater(){};
};