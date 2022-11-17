#include <gtest/gtest.h>
#include "../include/TemperatureSensor.h"
#include "../include/TemperatureValueProvider.h"

// Demonstrate that the sensor returns the correct value (which is fed from the TemperatureValueProvider)
TEST(TemperatureSensorTest, BasicAssertions) {
    TemperatureSensor sensor{};
    TemperatureValueProvider::setCurrentValue(30);
    const auto sensor_result = sensor.getCurrentValue();
    EXPECT_TRUE(sensor_result);
    const auto current_value = *sensor_result;
    constexpr float expected_result = 30;
    EXPECT_NEAR(current_value, expected_result, 1E-6);
}