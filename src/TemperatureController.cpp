#include "../include/TemperatureController.h"

#include "../include/TemperatureValueProvider.h"

#include <iostream>
#include <thread>

TemperatureController::TemperatureController(std::unique_ptr<IConfigReader> config,
                                             std::unique_ptr<ITemperatureSensor> temp_sensor,
                                             std::unique_ptr<ITemperatureCooler> cooler,
                                             std::unique_ptr<ITemperatureHeater> heater)
    : config_{std::move(config)}, temp_sensor_{std::move(temp_sensor)}, cooler_{std::move(cooler)}, heater_{std::move(heater)}
{
}

void TemperatureController::updateTemperature()
{
    const auto config_reader_result = config_->readConfig();
    if (!config_reader_result)
    {
        throw "Failed to read config data";
    }
    const auto sensor_result = temp_sensor_->getCurrentValue();
    if (!sensor_result)
    {
        throw "Failed to read sensor data";
    }
    const auto current_temperature = *sensor_result;
    const auto current_config = *config_reader_result;
    switch (current_state_)
    {
    case SystemState::Idle:
    {
        if (current_config.min_temperature >= current_temperature)
        {
            std::cout << "Current temperature " << current_temperature << " is equal or lower than minimum value of " << current_config.min_temperature << ", raising temperature to one degree above minimum \n";
            changeState(SystemState::Heating);
        }
        else if (current_config.max_temperature <= current_temperature)
        {
            std::cout << "Current temperature " << current_temperature << " is equal or higher than maximum value of " << current_config.max_temperature << ", lowering temperature to one degree below maximum \n";
            changeState(SystemState::Cooling);
        }
        else
        {
            std::cout << "Current temperature " << current_temperature << " within parameters " << current_config.min_temperature << " and " << current_config.max_temperature << '\n';
            waitUntilNextPoll();
        }
        break;
    }
    case SystemState::Cooling:
    {
        const auto success = lowerTemperature(current_config.max_temperature - 1);
        if (success)
        {
            std::cout << "Lowered temperature\n";
            changeState(SystemState::Idle);
        }
        else
        {
            throw "Failed to lower temperature";
        }
        break;
    }
    case SystemState::Heating:
    {
        const auto success = raiseTemperature(current_config.min_temperature + 1);
        if (success)
        {
            std::cout << "Raised temperature\n";
            changeState(SystemState::Idle);
        }
        else
        {
            throw "Failed to raise temperature";
        }

        break;
    }
    default:
    {
        assert(false);
    }
    }
}

SystemState TemperatureController::getCurrentState() const {
    return current_state_;
}

bool TemperatureController::temperatureIsWithinParameters(float current_temperature, Config parameters) const
{
    return current_temperature > parameters.min_temperature && current_temperature < parameters.max_temperature;
}

bool TemperatureController::raiseTemperature(float target_temperature)
{
    return heater_->raiseTemperature(target_temperature);
}

bool TemperatureController::lowerTemperature(float target_temperature)
{
   return cooler_->lowerTemperature(target_temperature);
}

void TemperatureController::changeState(SystemState new_state)
{
    current_state_ = new_state;
}

void TemperatureController::waitUntilNextPoll() const
{
    // added sleep time since it would be useless to poll continuously
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
}