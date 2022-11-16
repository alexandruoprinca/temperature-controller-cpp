#include "TemperatureValueProvider.h"

#include <random>

namespace
{
    //dummy function used to get 
    float generateRandomValue()
    {
        constexpr float lower_bound = -35;
        constexpr float upper_bound = 35;
        std::random_device rd;
        std::uniform_real_distribution<float> unif(lower_bound, upper_bound);
        return unif(rd);
    }
}
float TemperatureValueProvider::current_value = generateRandomValue();

float TemperatureValueProvider::getCurrentValue()
{
    return current_value;
}

void TemperatureValueProvider::setCurrentValue(float current_temperature)
{
    current_value = current_temperature;
}
