# Health Platform Arduino

## Description
The Health Platform Sensor is an Arduino-based air quality sensor.  Currently, it measures CO2 and TVOCs (total volatile organic compounds).

## Materials
This project uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) and an [Arduino Uno Rev2 Wifi](https://docs.arduino.cc/hardware/uno-wifi-rev2), both of which the CIC provides.

You will also need some wires, a breadboard, a USB-B connector, and a power cord.  If you have a DE1-SoC FPGA board, the cords that come with it are compatible.

## Setup
See the [Arduino Setup doc](./docs/arduino_setup.md).

## Current Progress
The Arduino uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) to measure CO2 and TVOCs.  CO2 is measured in ppm, and TVOCs are measured in ppb.

## Future Considerations
* Add other sensors, eg. temperature, humidity, PM2.5

## Other Resources
* [Sensor research](./docs/sensor_research.md)
