#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/TemperatureController.h"
#include "../include/TemperatureValueProvider.h"

#include "mocks/ConfigReaderMock.h"
#include "mocks/TemperatureSensorMock.h"
#include "mocks/TemperatureCoolerMock.h"
#include "mocks/TemperatureHeaterMock.h"

#include <memory>

using namespace ::testing;

TEST(TemperatureControllerTest, TemperatureIsWithinParameters)
{
  std::unique_ptr<ConfigReaderMock> config_reader = std::make_unique<ConfigReaderMock>();
  std::unique_ptr<TemperatureSensorMock> temperature_sensor = std::make_unique<TemperatureSensorMock>();
  std::unique_ptr<TemperatureCoolerMock> temperature_cooler = std::make_unique<TemperatureCoolerMock>();
  std::unique_ptr<TemperatureHeaterMock> temperature_heater = std::make_unique<TemperatureHeaterMock>();

  Config read_config_return_value;
  read_config_return_value.min_temperature = 20;
  read_config_return_value.max_temperature = 35;
  constexpr float get_current_value_return_value{30};
  EXPECT_CALL(*config_reader, readConfig()).WillOnce(::testing::Return(read_config_return_value));
  EXPECT_CALL(*temperature_sensor, getCurrentValue()).WillOnce(::testing::Return(get_current_value_return_value));
  TemperatureController temperature_controller{
      std::move(config_reader), std::move(temperature_sensor), std::move(temperature_cooler), std::move(temperature_heater)};

  temperature_controller.updateTemperature();
  constexpr auto expected_system_state = SystemState::Idle;
  EXPECT_TRUE(temperature_controller.getCurrentState() == expected_system_state);
}

TEST(TemperatureControllerTest, TempBelowMinimum)
{
  std::unique_ptr<ConfigReaderMock> config_reader = std::make_unique<ConfigReaderMock>();
  std::unique_ptr<TemperatureSensorMock> temperature_sensor = std::make_unique<TemperatureSensorMock>();
  std::unique_ptr<TemperatureCoolerMock> temperature_cooler = std::make_unique<TemperatureCoolerMock>();
  std::unique_ptr<TemperatureHeaterMock> temperature_heater = std::make_unique<TemperatureHeaterMock>();

  Config read_config_return_value;
  read_config_return_value.min_temperature = 20;
  read_config_return_value.max_temperature = 35;
  EXPECT_CALL(*config_reader, readConfig()).Times(2).WillRepeatedly(Return(read_config_return_value));

  constexpr float get_current_value_return_value{10};
  constexpr float get_current_value_return_value_after_heating{21};
  EXPECT_CALL(*temperature_sensor, getCurrentValue())
      .Times(2)
      .WillOnce(Return(get_current_value_return_value))
      .WillOnce(Return(get_current_value_return_value_after_heating));

  constexpr bool raise_temperature_return_value{true};
  constexpr float raise_temperature_argument_value{21};
  EXPECT_CALL(*temperature_heater, raiseTemperature(raise_temperature_argument_value)).WillOnce(Return(raise_temperature_return_value));
  TemperatureController temperature_controller{
      std::move(config_reader), std::move(temperature_sensor), std::move(temperature_cooler), std::move(temperature_heater)};

  temperature_controller.updateTemperature();
  constexpr auto expected_system_state = SystemState::Heating;
  EXPECT_TRUE(temperature_controller.getCurrentState() == expected_system_state);

  temperature_controller.updateTemperature();
  constexpr auto expected_system_state_after_heating = SystemState::Idle;
  EXPECT_TRUE(temperature_controller.getCurrentState() == expected_system_state_after_heating);
}

TEST(TemperatureControllerTest, TempAboveMaximum)
{
  std::unique_ptr<ConfigReaderMock> config_reader = std::make_unique<ConfigReaderMock>();
  std::unique_ptr<TemperatureSensorMock> temperature_sensor = std::make_unique<TemperatureSensorMock>();
  std::unique_ptr<TemperatureCoolerMock> temperature_cooler = std::make_unique<TemperatureCoolerMock>();
  std::unique_ptr<TemperatureHeaterMock> temperature_heater = std::make_unique<TemperatureHeaterMock>();

  Config read_config_return_value;
  read_config_return_value.min_temperature = 20;
  read_config_return_value.max_temperature = 35;
  EXPECT_CALL(*config_reader, readConfig()).Times(2).WillRepeatedly(Return(read_config_return_value));

  constexpr float get_current_value_return_value{40};
  constexpr float get_current_value_return_value_after_cooling{34};
  EXPECT_CALL(*temperature_sensor, getCurrentValue())
      .Times(2)
      .WillOnce(Return(get_current_value_return_value))
      .WillOnce(Return(get_current_value_return_value_after_cooling));
  
  constexpr bool lower_temperature_return_value{true};
  constexpr float lower_temperature_argument_value{34};
  EXPECT_CALL(*temperature_cooler, lowerTemperature(lower_temperature_argument_value)).WillOnce(Return(lower_temperature_return_value));

  TemperatureController temperature_controller{
      std::move(config_reader), std::move(temperature_sensor), std::move(temperature_cooler), std::move(temperature_heater)};

  temperature_controller.updateTemperature();
  constexpr auto expected_system_state = SystemState::Cooling;
  EXPECT_TRUE(temperature_controller.getCurrentState() == expected_system_state);

  temperature_controller.updateTemperature();
  constexpr auto expected_system_state_after_cooling = SystemState::Idle;
  EXPECT_TRUE(temperature_controller.getCurrentState() == expected_system_state_after_cooling);
}
