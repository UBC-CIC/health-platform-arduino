# Health Platform Arduino

## Description
The Health Platform Sensor is an Arduino-based air quality sensor.  Currently, it measures CO2 and TVOCs (total volatile organic compounds).

## Materials
This project uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) and an [Arduino Uno Rev2 Wifi](https://docs.arduino.cc/hardware/uno-wifi-rev2), both of which the CIC provides.

You will also need some wires, a breadboard, a USB-B connector, and a power cord.  If you have a DE1-SoC FPGA board, the cords that come with it are compatible.

## Setup
See the [Arduino Setup doc](./docs/arduino_setup.md).

## Current Progress
The Arduino uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) to measure CO2 and TVOCs.  CO2 is measured in ppm, and TVOCs are measured in ppb.  Each time the sensor takes a reading, the Arduino sends the data (along with a Unix timestamp) to an AWS IoT endpoint (configured by https://github.com/UBC-CIC/health-platform-iot) (work-in-progress).

A sensor reading sent to the IoT endpoint should look something like this:
```
{
	sensorId: '152',
	timestamp: 1639591755,
	co2: 410,
	tvoc: 1,
}
```

## Future Considerations
* Add other sensors, eg. temperature, humidity, PM2.5
* How to assign sensorIds (coordinate with https://github.com/UBC-CIC/health-platform-iot)

## Other Resources
* Tests for individual components of the project: see the [tests folder](./tests)
* [Sensor research](./docs/sensor_research.md)
* [Repo for iot data collection](https://github.com/UBC-CIC/health-platform-iot)
* [Arduino specs](https://docs.arduino.cc/hardware/uno-wifi-rev2)
* [Get a Unix timestamp on Arduino](https://www.arduino.cc/en/Tutorial/LibraryExamples/WiFiNINAUdpNTPClient)
