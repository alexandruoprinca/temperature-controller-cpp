#pragma once
#include "IConfigReader.h"
#include "ITemperatureSensor.h"
#include "ITemperatureController.h"

enum class SystemState
{
    Idle,
    Heating,
    Cooling
};

class TemperatureController : public ITemperatureController
{
public:
    TemperatureController(std::unique_ptr<IConfigReader> config, std::unique_ptr<ITemperatureSensor> temp_sensor);
    void updateTemperature();

private:
    void changeState(SystemState new_state);
    bool temperatureIsWithinParameters(float current_temperature, Config parameters) const;
    void raiseTemperature() const;
    void lowerTemperature() const;
    void waitUntilNextPoll() const;

private:
    std::unique_ptr<IConfigReader> config_;
    std::unique_ptr<ITemperatureSensor> temp_sensor_;
    SystemState current_state_{SystemState::Idle};
};