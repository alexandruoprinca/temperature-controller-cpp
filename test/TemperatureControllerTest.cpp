#include <gtest/gtest.h>

#include "../src/TemperatureController.h"
#include "../src/IConfigReader.h"

#include "ConfigReaderMock.h"
#include "TemperatureSensorMock.h"

#include <memory>

TEST(TemperatureControllerTest, TemperatureIsWithinParameters) {
    std::unique_ptr<IConfigReader> config_reader_mock = std::make_unique<ConfigReaderMock>();
    std::unique_ptr<ITemperatureSensor> temperature_sensor_mock = std::make_unique<TemperatureSensorMock>();

    std::unique_ptr<ITemperatureController> temperature_controller = std::make_unique<TemperatureController>(std::move(config_reader_mock), std::move(temperature_sensor_mock));
    temperature_controller->updateTemperature();
}
