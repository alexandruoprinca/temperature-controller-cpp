#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/ITemperatureCooler.h"

class TemperatureCoolerMock : public ITemperatureCooler {
public:
    MOCK_METHOD(bool, lowerTemperature, (float target_temperature), (override));
};