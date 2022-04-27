# Health Platform Arduino

## Description
The Arduino uses the [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) to measure CO2 and TVOCs (total volatile organic compounds).  CO2 is measured in ppm, and TVOCs are measured in ppb.  Each time the sensor takes a reading, the Arduino sends the data (along with a Unix timestamp) to an AWS IoT endpoint (configured by https://github.com/UBC-CIC/health-platform-iot) (work-in-progress).

A sensor reading sent to the IoT endpoint looks like this:
```
{
  "sensorId": "1657229",
  "measurementType": "TVOC",
  "measurement": "38.00",
  "timestamp": "2022-04-27 23:11:37.000Z"
}
```

## Materials
* [Keyestudio CCS811 sensor](https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor) (from the CIC)

* [NodeMCU ESP8266](https://www.amazon.ca/KeeYees-Internet-Development-Wireless-Compatible/dp/B07HF44GBT)
	* Micro-USB connector
	* Wires + breadboard

## Follow the instructions in these two documents for TESTING
Firstly, follow the steps in the [AWS Environment Setup doc](./docs/aws_environment_setup.md) and
then, proceed to the [Arduino Sensor Setup doc](./docs/arduino_sensor_setup.md).

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
