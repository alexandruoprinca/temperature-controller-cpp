#pragma once

class ITemperatureController
{
public:
    virtual void updateTemperature() = 0;
    virtual ~ITemperatureController(){};
};