#include <iostream>

#include "include/TemperatureController.h"
#include "include/ConfigReader.h"
#include "include/TemperatureSensor.h"
#include "include/TemperatureCooler.h"
#include "include/TemperatureHeater.h"
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
        std::unique_ptr<ITemperatureCooler> temp_cooler = std::make_unique<TemperatureCooler>();
        std::unique_ptr<ITemperatureHeater> temp_heater = std::make_unique<TemperatureHeater>();
        std::unique_ptr<ITemperatureController> temp_controller = std::make_unique<TemperatureController>(
            std::move(config), std::move(temp_sensor), std::move(temp_cooler), std::move(temp_heater));
        std::cout << "Starting \n";
        while (1)
        {
            temp_controller->updateTemperature();
        }
    }
    catch (std::exception &ex)
    {
        std::cout << "Something went wrong: " << ex.what() << '\n';
        std::cout << "Stopping \n";
        return -1;
    }
    std::cout << "Stopping \n";
    return 0;
}