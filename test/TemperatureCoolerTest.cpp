#include <gtest/gtest.h>
#include "../include/TemperatureCooler.h"
#include "../include/TemperatureValueProvider.h"

namespace
{
    constexpr float FLOATNG_POINT_PRECISION = 1E-6;
}

TEST(TemperatureCoolerTest, CoolToACertainDegree)
{
    TemperatureCooler cooler{};
    constexpr float initial_temperature{30};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{20};
    constexpr float expected_temperature_after_cooling{20};
    cooler.lowerTemperature(target_temperature);
    EXPECT_NEAR(target_temperature, expected_temperature_after_cooling, FLOATNG_POINT_PRECISION);
}

TEST(TemperatureCoolerTest, CoolToSameTemperature)
{
    TemperatureCooler cooler{};
    constexpr float initial_temperature{20};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{20};
    constexpr float expected_temperature_after_cooling{20};
    cooler.lowerTemperature(target_temperature);
    EXPECT_NEAR(target_temperature, expected_temperature_after_cooling, FLOATNG_POINT_PRECISION);
}

TEST(TemperatureCoolerTest, CoolToHigherTemperature)
{
    TemperatureCooler cooler{};
    constexpr float initial_temperature{20};
    TemperatureValueProvider::setCurrentValue(initial_temperature);
    constexpr float target_temperature{30};
    constexpr float expected_temperature_after_cooling{20};
    cooler.lowerTemperature(target_temperature);
    EXPECT_NEAR(initial_temperature, expected_temperature_after_cooling, FLOATNG_POINT_PRECISION);
}