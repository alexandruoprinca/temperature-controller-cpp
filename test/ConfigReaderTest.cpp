#include <gtest/gtest.h>
#include "../src/ConfigReader.h"

TEST(ConfigReaderTest, DataIsReadSuccessfullyFromFile) {

    const std::string config_path{"../test/config/correct_data.txt"};
    ConfigReader config_reader{config_path};
    const auto result = config_reader.readConfig();
    EXPECT_TRUE(result);
    const auto config = *result;
    EXPECT_NEAR(config.min_temperature, -5, 1E-6);
    EXPECT_NEAR(config.max_temperature, 35, 1E-6);
}

TEST(ConfigReaderTest, FailToReadPartialData) {
    const std::string config_path{"../test/config/partial_data.txt"};
    ConfigReader config_reader{config_path};
    const auto result = config_reader.readConfig();
    EXPECT_FALSE(result);
}

TEST(ConfigReaderTest, FailToReadNoData) {
    const std::string config_path{"../test/config/no_data.txt"};
    ConfigReader config_reader{config_path};
    const auto result = config_reader.readConfig();
    EXPECT_FALSE(result);
}

TEST(ConfigReaderTest, FileDoesNotExist) {
    const std::string config_path{"../test/config/non_existing_file"};
    ConfigReader config_reader{config_path};
    const auto result = config_reader.readConfig();
    EXPECT_FALSE(result);
}