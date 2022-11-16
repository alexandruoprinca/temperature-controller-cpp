cmake_minimum_required(VERSION 3.1...3.24)

project(
  temperature-controller-app-cpp
  VERSION 1.0
  LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB APP_SOURCES "src/*.cpp")
add_executable(TemperatureController main.cpp ${APP_SOURCES})

enable_testing()
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(TemperatureControllerTest ${APP_SOURCES} ${TEST_SOURCES})

target_link_libraries(TemperatureControllerTest GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(TemperatureControllerTest)