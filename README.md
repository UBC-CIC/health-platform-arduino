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
* [Micro-USB connector](https://www.amazon.ca/%E3%80%906-6Feet%E3%80%91USB-Android-Charger-Motorola-Smartphones/dp/B099K78GW4/ref=sr_1_5?keywords=micro+usb+cable&qid=1651254543&sprefix=micro+usb+%2Caps%2C120&sr=8-5)
* [Wires](https://www.amazon.ca/breadboard-Breadboard-Protoboard-Solderless-Electronic/dp/B07YQ1XBC1/ref=sr_1_7?crid=26OAVGTALK5WT&keywords=small+breadboard+wires&qid=1651254615&sprefix=small+breaboard+wire%2Caps%2C111&sr=8-7) + [breadboard](https://www.amazon.ca/BusBoard-Prototype-Systems-Solderless-BreadBoard/dp/B00M2CK0JA/ref=sr_1_8?keywords=breadboard&qid=1651254657&sprefix=breadb%2Caps%2C128&sr=8-8)

* [Wall Adapter](https://www.amazon.ca/Charger-LUOATIP-Adapter-Charging-Replacement/dp/B07TK6MPNB/ref=sr_1_1_sspa?crid=31ENFA5R6MP8Z&keywords=wall+adapter+usb&qid=1651255327&sprefix=wall+adapte%2Caps%2C5225&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyREdINkVINU5JWVMwJmVuY3J5cHRlZElkPUEwNTg2MjYwMlRaRk0yTk5OMjYxNiZlbmNyeXB0ZWRBZElkPUEwNDYzNDMzUzcwRlpYRjAzSVEmd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) 

## Deployment Guide
The Node MCU boards come with the code and certificates already uploaded to the devices. Simply plug the USB cable into a wall adapter or your laptop, open up the [Arduino Sensor Setup doc](./docs/arduino_sensor_setup.md), and follow from Step #5 in the 'Connecting Sensor To Cloud' section.  

If you are registering and deploying the solution into your AWS Account, firstly, follow the steps in the [AWS Environment Setup doc](./docs/aws_environment_setup.md) and
then proceed to the [Arduino Sensor Setup doc](./docs/arduino_sensor_setup.md).

## Future Considerations/TODO List
* Add other sensors, eg. temperature, humidity, PM2.5
* How to assign sensorIds (coordinate with https://github.com/UBC-CIC/health-platform-iot)
* Combine the CCS811 and MQTT tests for the NodeMCU board to create the source code for taking sensor readings and sending them to AWS IoTCore

## Other Resources
* Tests for individual components of the project: see the [tests folder](./tests).  Each test has a set of instructions with it.
* [Sensor research](./docs/sensor_research.md)

* [Repo for iot data collection](https://github.com/UBC-CIC/health-platform-iot)

* [Connect NodeMCU board to AWS IoT](https://medium.com/@jgillard/marrying-esp8266-aws-iot-69f1ab219c2)

* [Arduino IDE issues with Mac OS Big Sur](https://www.esp8266.com/viewtopic.php?f=32&t=21692&start=4)
