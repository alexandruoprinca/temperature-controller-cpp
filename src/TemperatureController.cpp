#include "TemperatureController.h"

#include "TemperatureValueProvider.h"

#include <iostream>
#include <thread>

TemperatureController::TemperatureController(std::unique_ptr<IConfigReader> config, std::unique_ptr<ITemperatureSensor> temp_sensor)
    : config_{std::move(config)}, temp_sensor_{std::move(temp_sensor)}
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
        lowerTemperature();
        const auto new_sensor_result = temp_sensor_->getCurrentValue();
        if (!new_sensor_result)
        {
            throw "Failed to read sensor data for new value while cooling";
        }
        if (temperatureIsWithinParameters(*new_sensor_result, current_config))
        {
            changeState(SystemState::Idle);
        }
        break;
    }
    case SystemState::Heating:
    {
        raiseTemperature();
        const auto new_sensor_result = temp_sensor_->getCurrentValue();
        if (!new_sensor_result)
        {
            throw "Failed to read sensor data for new value while heating";
        }
        if (temperatureIsWithinParameters(*new_sensor_result, current_config))
        {
            changeState(SystemState::Idle);
        }
        break;
    }
    default:
    {
        assert(false);
    }
    }
}

bool TemperatureController::temperatureIsWithinParameters(float current_temperature, Config parameters) const
{
    return current_temperature > parameters.min_temperature && current_temperature < parameters.max_temperature;
}

void TemperatureController::raiseTemperature() const
{
    // added sleep since in real life this operation is never instantaneous
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    TemperatureValueProvider::setCurrentValue(TemperatureValueProvider::getCurrentValue() + 1);
    std::cout << "Raised temperature to " << TemperatureValueProvider::getCurrentValue() << " degrees \n";
}

void TemperatureController::lowerTemperature() const
{
    // added sleep since in real life this operation is never instantaneous
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    TemperatureValueProvider::setCurrentValue(TemperatureValueProvider::getCurrentValue() - 1);
    std::cout << "Lowered temperature to " << TemperatureValueProvider::getCurrentValue() << " degrees \n";
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