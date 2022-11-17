#pragma once
#include "IConfigReader.h"
#include "ITemperatureSensor.h"
#include "ITemperatureController.h"
#include "ITemperatureCooler.h"
#include "ITemperatureHeater.h"
class TemperatureController : public ITemperatureController
{
public:
    TemperatureController(std::unique_ptr<IConfigReader> config,
                          std::unique_ptr<ITemperatureSensor> temp_sensor,
                          std::unique_ptr<ITemperatureCooler> cooler,
                          std::unique_ptr<ITemperatureHeater> heater);
    void updateTemperature() override;
    SystemState getCurrentState() const override;

private:
    void changeState(SystemState new_state);
    bool temperatureIsWithinParameters(float current_temperature, Config parameters) const;
    bool raiseTemperature(float target_temperature);
    bool lowerTemperature(float target_temperature);
    void waitUntilNextPoll() const;

private:
    std::unique_ptr<IConfigReader> config_;
    std::unique_ptr<ITemperatureSensor> temp_sensor_;
    std::unique_ptr<ITemperatureCooler> cooler_;
    std::unique_ptr<ITemperatureHeater> heater_;
    SystemState current_state_{SystemState::Idle};
};