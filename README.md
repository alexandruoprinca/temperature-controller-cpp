# temperature-controller-cpp

Build and Run project:

1.(Tested and implemented on MacOS)
2.Go into the project's root folder.
3.Open a terminal.
4.Run `mkdir build && cd build`, `cmake ..`, `make` in the mentioned order (assuming cmake and make are already added to your path)
5.Run './TemperatureController' for the application and './TemperatureControllerTest' for the unit tests.

Mentions:
1.Currently the minimum and maximum temperatures are read from the config.txt file, meaning that someone can change the desired temperature interval
by changing the data in the config.txt (min is first val, max is second). The app will read the config every few seconds and it will try to adjust the temperature accordingly.

2.The "TemperatureSensor" component reads the data from the TemperatureValueProvider class which is created to simulate real changes in temperature. 
The initial value is random between -35 and 35.


