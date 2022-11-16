#include "ConfigReader.h"

#include <fstream>
#include <exception>
#include <iostream>

ConfigReader::ConfigReader(std::string config_file_name)
    : config_file_name_{std::move(config_file_name)}
{
}

std::optional<Config> ConfigReader::readConfig()
{
    Config result;
    float min_temperature = 0;
    float max_temperature = 0;

    std::ifstream config_file{config_file_name_};
    if (config_file.is_open())
    {
        if(!(config_file >> min_temperature >> max_temperature)){
            return {};
        }
    }
    else
    {
        return {};
    }
    result.max_temperature = max_temperature;
    result.min_temperature = min_temperature;
    return result;
}