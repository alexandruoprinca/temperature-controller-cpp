#pragma once
#include "IConfigReader.h"

#include <string>

class ConfigReader : public IConfigReader
{
public:
    ConfigReader(std::string config_file_name);
    std::optional<Config> readConfig() override;

private:
    std::string config_file_name_;
};