#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/ITemperatureSensor.h"

class TemperatureSensorMock : public ITemperatureSensor {
public:
    MOCK_METHOD(std::optional<float>, getCurrentValue, (), (override, const));
};