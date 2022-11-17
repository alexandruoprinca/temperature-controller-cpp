#include "../include/TemperatureHeater.h"

#include "../include/TemperatureValueProvider.h"

#include <chrono>
#include <thread>
#include <cmath>

bool TemperatureHeater::raiseTemperature(float target_temperature)
{
    // added sleep since in real life the temperature is raised gradually
    using namespace std::chrono_literals;
    while (std::isless(TemperatureValueProvider::getCurrentValue(), target_temperature))
    {
        TemperatureValueProvider::setCurrentValue(TemperatureValueProvider::getCurrentValue() + 1);
        std::this_thread::sleep_for(300ms);
    }
    return true;
}