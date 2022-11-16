#include <iostream>

#include "src/TemperatureController.h"
#include "src/ConfigReader.h"
#include "src/TemperatureSensor.h"

namespace
{
    constexpr auto CONFIG_FILE_PATH = "../config.txt";
}

int main()
{
    try
    {
        std::unique_ptr<IConfigReader> config = std::make_unique<ConfigReader>(CONFIG_FILE_PATH);
        std::unique_ptr<ITemperatureSensor> temp_sensor = std::make_unique<TemperatureSensor>();
        std::unique_ptr<ITemperatureController> temp_controller = std::make_unique<TemperatureController>(std::move(config), std::move(temp_sensor));
        std::cout << "Starting \n";
        while (1)
        {
            temp_controller->updateTemperature();
        }
    }
    catch (std::exception &ex)
    {
        std::cout << "Something went wrong: " << ex.what() << '\n';
        return -1;
    }
    return 0;
}