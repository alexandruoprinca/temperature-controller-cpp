#include <gtest/gtest.h>
#include "../src/TemperatureSensor.h"
#include "../src/TemperatureValueProvider.h"

// Demonstrate that the sensor returns the correct value (which is fed from the TemperatureValueProvider)
TEST(TemperatureSensorTest, BasicAssertions) {
    TemperatureSensor sensor{};
    TemperatureValueProvider::setCurrentValue(30);
    const auto sensor_result = sensor.getCurrentValue();
    EXPECT_TRUE(sensor_result);
    const auto current_value = *sensor_result;
    EXPECT_NEAR(current_value, 30, 1E-6);
}