#include <gtest/gtest.h>
#include "../include/TemperatureHeater.h"
#include "../include/TemperatureValueProvider.h"

namespace
{
    constexpr float FLOATNG_POINT_PRECISION = 1E-6;
}

TEST(TemperatureHeaterTest, HeatToACertainDegree)
{
    TemperatureHeater heater{};
    constexpr float initial_temperature{20};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{30};
    constexpr float expected_temperature_after_heating{30};
    heater.raiseTemperature(target_temperature);
    EXPECT_NEAR(target_temperature, expected_temperature_after_heating, FLOATNG_POINT_PRECISION);
}

TEST(TemperatureHeaterTest, HeatToSameTemperature)
{
    TemperatureHeater heater{};
    constexpr float initial_temperature{20};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{20};
    constexpr float expected_temperature_after_heating{20};
    heater.raiseTemperature(target_temperature);
    EXPECT_NEAR(target_temperature, expected_temperature_after_heating, FLOATNG_POINT_PRECISION);
}

TEST(TemperatureHeaterTest, HeatToLowerTemperature)
{
    TemperatureHeater heater{};
    constexpr float initial_temperature{30};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{20};
    constexpr float expected_temperature_after_heating{30};
    heater.raiseTemperature(target_temperature);
    EXPECT_NEAR(initial_temperature, expected_temperature_after_heating, FLOATNG_POINT_PRECISION);
}