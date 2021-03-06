# NodeMCU Setup (hardware)
### NodeMCU ESP8266
For this step, you will need some wires and a breadboard, as well as the CCS811 sensor and NodeMCU ESP8266 board.  Colour-coding the wires is highly recommended, particularly for ground and power wires.  In the example below, black is ground, red is power, blue is SDA, and green is SCL.

1. Place the chip and NodeMCU on a breadboard.
<img src="../images/CCS811_node.jpg">

2. Connect the GND pin on the chip to a GND pin on the Arduino (note that there are multiple GND pins on the Arduino, it doesn't matter which one you choose).
<img src="../images/GND_node.jpg">

3. Connect the VCC pin on the chip to the 3V3 pin on the Arduino.
<img src="../images/VCC_node.jpg">

4. Connect the SDA pin on the chip to the D2 pin on the Arduino.
<img src="../images/SDA_node.jpg">

5. Connect the SCL pin on the chip to the D1 pin on the Arduino.
<img src="../images/SCL_node.jpg">

6. Connect the WAKE pin on the chip to a GND pin on the Arduino (again, doesn't matter which GND pin you choose).
<img src="../images/WAKE_node.jpg">

7. Once setup, connect the Micro USB cable to your device and plug it into your laptop. 
<img src="../images/esp8266_usb_connection.jpg">





# NodeMCU Setup (software)

## Step 1: Install the Arduino IDE
Download [Arduino IDE](https://www.arduino.cc/en/software)
* Select instructions from [here](https://www.arduino.cc/en/Guide) based on OS

## Step 2: Board Selection
### Install the NodeMCU ESP8266 Board
This board is not supported by the basic board manager that is automatically installed with the IDE.  We will need to install a new board manager.
1. In the IDE, go to File->Preferences, and paste the following url into the *Additional Boards Manager URLs*, then click **OK**:
```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
<img src="../images/preferences.png">
2. Go to Tools->Board->Boards Manager, and search for esp8266.  When you install this, select the 2.7.3 version.
<img src="../images/board_manager_esp8266.png">
3. Go to Tools->Board->ESP8266 Boards (2.7.3) and select *NodeMCU 1.0 (ESP-12E Module)*.

## Step 3: Downloading the code to upload to the board
1. In the Arduino IDE, copy the file contents of the [Arduino sketch in this directory](../src/NodeMCU/aws_sensor_connection_with_authentication/aws_sensor_connection_with_authentication.ino) and paste it into the IDE.

2. Once the code contents have been copied, save your sketch in the Arduino directory that was installed on your computer like this:
<img src="../images/save_arduino_sketch.png">


## Step 4: Installing the ESP8266 File System Uploader
The certificates and keys that we downloaded in the [previous section](./aws_environment_setup.md) need to now be uploaded to the board. This is done using the [following plugin](https://github.com/esp8266/arduino-esp8266fs-plugin). The Github page provides the necessary instructions for installation.

1. Once installation is finished, navigate to the Arduino directory where your sketch is saved. Open it and create a new directory/folder called ???data???. Paste the 'cert', 'private', and 'ca' files in there. 
<img src="../images/certs_upload_setup.png">

3. Open up the 'aws_sensor_authentication.ino' sketch. Go to Tools -> Sketch Data Upload. This should start uploading the files into ESP8266 flash file system. When done, IDE status bar will display SPIFFS Image Uploaded message.
<img src="../images/sketch_upload_setup.png">

## Step 5: Installing the libraries
It is very important that these exact libraries be installed onto the Arduino IDE in order to for the sketch to compile and be uploaded to the board. You can use the 'Library Manager' in the IDE and install them. 

- The following are installed by going into the IDE, then clicking on Sketch -> Library Manager -> 'Library Name' and then install. 
  - PubSub Client by Nick O' Leary (v. 2.8.0)
  - NTP Client by Fabrice Weinberg (v. 3.2.1)
  - DFRobot CCS811 by Fary DF Robot (v. 1.0.1)
  - ArduinoJSON by Benoit Blanchon (v. 6.19.4)
  - WiFiManager by tablatronix (v. 2.0.11-beta)


# Connecting the Sensor to the Cloud
1. In order to connect the sensor to AWS and integrate it with the website, we need the IOT endpoint value. Retrieve this value by going back into your AWS Console -> AWS IOT -> Settings. Make sure to note the endpoint value.
<img src="../images/console/settings_iot.png">
<img src="../images/console/aws_iot_endpoint.png">




2. Now we can proceed to uploading the code to the device. In the IDE with the code file, set the topic value to "iot_device_analytics" and the endpoint value to the one that was retrieved from the AWS Console. Once edited, make sure to save your code.
<img src="../images/endpoint_topic_setup.png">

3. From the Menu bar, select Tools -> Port. If a board is currently selected it will be displayed here. If you don't see your board in the list, checkout [this link](https://support.arduino.cc/hc/en-us/articles/4412955149586-If-your-board-does-not-appear-in-the-port-menu). Although the Port varies by system, the rest of your Tools configurations should look something like this.
<img src="../images/esp8266_tools_config.png">

4. Ensure your sketch compiles by clicking on the Verify button (top left). If there are no errors, proceed to click the upload button and wait for your sketch to be uploaded to the board (Might take a few minutes). 

5. Open up the serial monitor which is set at the baud rate of 115200.

6. Using any WiFi enabled device, find the access point called ESP8266APConnect and click connect.
<img src="../images/wifi_ap_setup.png" width="250">


7. You will be directed to a landing page where you can find your configure your WiFi credentials (SSID/WiFi Name and WiFi Password). Once configured, the page will close and you will get confirmation in the 'Serial Monitor' that your device has successfully connected and sending data in the Serial Monitor.
<img src="../images/wifi_cred_setup.png" width="250">
<img src="../images/wifi_connected_setup.png">


8. We can test this by opening up the MQTT Test Client in the AWS IOT Core Console. Enter the the topic name which is "iot_device_analytics" in the field, click subscribe, and see the TVOC and CO2 readings show up. Make sure to take note of the Sensor Id as it will be needed to register the device on the Health Platform Website
<img src="../images/console/mqtt_console.png">
<img src="../images/console/mqtt_test_client_console.png">


# Connecting the Sensor to the Health Platform Website 

1. Log into the Health Platform website and navigate to the Patients page
<img src="../images/patients_dashboard_gas_sensor.png">

2. Find the patient you want to add the sensor to, navigate to the sensor column, click on Manage -> Add Sensor
<img src="../images/select_add_gas_sensor.png">


3. Select the sensor type to be a Gas Sensor. Then enter the Sensor ID and select Add. 
<img src="../images/add_gas_sensor.png">

4. You will now be able to see CO2 and TVOC readings on the main dashboard page. 

