#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/ITemperatureHeater.h"

class TemperatureHeaterMock : public ITemperatureHeater {
public:
    MOCK_METHOD(bool, raiseTemperature, (float target_temperature), (override));
};