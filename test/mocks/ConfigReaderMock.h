#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/IConfigReader.h"

class ConfigReaderMock : public IConfigReader {
public:
    MOCK_METHOD(std::optional<Config>, readConfig, (), (override));
};