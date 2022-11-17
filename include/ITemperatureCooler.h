#pragma once

class ITemperatureCooler
{
public:
    virtual bool lowerTemperature(float target_temperature) = 0;
    virtual ~ITemperatureCooler(){};
};