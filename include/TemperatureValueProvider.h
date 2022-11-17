#pragma once

// static class created in order to have a mechanism that can store the sensor's temperature easily
// without having to use a db or a file
//(in real life this would have been replaced by the actual room temperature provided by the sensor)
class TemperatureValueProvider
{
public:
    static float getCurrentValue();
    static void setCurrentValue(float current_temperature);

private:
    static float current_value;
};