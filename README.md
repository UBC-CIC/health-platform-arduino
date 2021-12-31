# Health Platform Arduino

## Description
The Arduino uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) to measure CO2 and TVOCs (total volatile organic compounds).  CO2 is measured in ppm, and TVOCs are measured in ppb.  Each time the sensor takes a reading, the Arduino sends the data (along with a Unix timestamp) to an AWS IoT endpoint (configured by https://github.com/UBC-CIC/health-platform-iot) (work-in-progress).

A sensor reading sent to the IoT endpoint should look something like this:
```
{
	sensorId: '152',
	timestamp: 1639591755,
	co2: 410,
	tvoc: 1,
}
```

## Materials
* [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) (from the CIC)
* [Arduino Uno Rev2 Wifi](https://docs.arduino.cc/hardware/uno-wifi-rev2) (from the CIC)
	* USB-B connector (if you have a DE1-SoC FPGA board, the cords that come with it are compatible)
* [NodeMCU ESP8266](https://www.amazon.ca/KeeYees-Internet-Development-Wireless-Compatible/dp/B07HF44GBT)
	* Micro-USB connector
* Wires + breadboard

## Setup
See the [Arduino Setup doc](./docs/arduino_setup.md).

Note that in some steps, there are instructions both for an Arduino Uno Rev2 WiFi board and a NodeMCUU ESP8266 board.  Initially, the Rev2 WiFi board was used for testing the CCS811 sensor.  However, it did not have enough memory to support sending MQTT messages using SSL.  For future development, use the [NodeMCU ESP8266 board](https://www.amazon.ca/KeeYees-Internet-Development-Wireless-Compatible/dp/B07HF44GBT).

## Current Progress
* CCS811 sensor has been tested with both Arduinos: scripts are provided for each board
* MQTT messaging to AWS IoT has been tested for the NodeMCU board

## Future Considerations/TODO List
* Add other sensors, eg. temperature, humidity, PM2.5
* How to assign sensorIds (coordinate with https://github.com/UBC-CIC/health-platform-iot)
* Combine the CCS811 and MQTT tests for the NodeMCU board to create the source code for taking sensor readings and sending them to AWS IoTCore

## Other Resources
* Tests for individual components of the project: see the [tests folder](./tests).  Each test has a set of instructions with it.
* [Sensor research](./docs/sensor_research.md)
* [Repo for iot data collection](https://github.com/UBC-CIC/health-platform-iot)
* [Arduino Uno Rev2 Wifi specs](https://docs.arduino.cc/hardware/uno-wifi-rev2)
* [Get a Unix timestamp on Arduino (Uno Rev2 Wifi board)](https://www.arduino.cc/en/Tutorial/LibraryExamples/WiFiNINAUdpNTPClient)
* [Purchase Node MCU ESP8266 board](https://www.amazon.ca/KeeYees-Internet-Development-Wireless-Compatible/dp/B07HF44GBT)
* [Connect NodeMCU board to AWS IoT](https://medium.com/accenture-the-dock/esp8266-aws-iot-core-guide-c640f2622a51)
