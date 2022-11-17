#pragma once
#include "SystemState.h"
class ITemperatureController
{
public:
    virtual void updateTemperature() = 0;
    virtual SystemState getCurrentState() const = 0;
    virtual ~ITemperatureController(){};
};