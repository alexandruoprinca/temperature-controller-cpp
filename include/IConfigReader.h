#pragma once
#include "Config.h"

#include <optional>

class IConfigReader
{
public:
    virtual std::optional<Config> readConfig() = 0;
    virtual ~IConfigReader(){};
};