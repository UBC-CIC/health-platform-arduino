# Arduino Setup

## Step 1: Install the Arduino IDE
Download [Arduino IDE](https://www.arduino.cc/en/software)
* Select instructions from [here](https://www.arduino.cc/en/Guide) based on OS

## Step 2: Set up the IDE
Before we can run any code on the Arduino, there are a few things to set up.

### Step 2.1: Board Selection
The board we want to use is the Arduino Uno Rev2 Wifi, which is not supported by the basic board manager that is automatically installed with the IDE.  We will need to install a new board manager.
1. In the Arduino IDE, go to Tools->Board->Boards Manager.
2. In the Boards Manager, type "Arduino Uno Rev2" into the search bar.  This should bring up a board manager called *Arduino megaAVR Boards*.  Install this.
<img src="../images/board_manager.png">

3. Go to Tools->Board->Arduino Mega AVR Boards and select *Arduino Uno Wifi Rev2*.

### Step 2.2: Install a Libary
To use the current code, the DFRobot_CCS811 library is required.
1. In the Arduino IDE, go to Sketch->Include Libary->Manage Libraries.
2. In the Library Manager, type "DFRobot_CCS811" into the search bar.  Install the library.
<img src="../images/library_manager.png">

## Step 3: Test the Arduino
To make sure everything is working correctly, follow [this](https://learn.adafruit.com/adafruit-arduino-lesson-1-blink/the-l-led?view=all) guide to make an LED blink.

## Step 4: Create the CCS811-Arduino Circuit
For this step, you will need some wires and a breadboard, as well as the CCS811 sensor and Arduino board provided by the CIC.  Colour-coding the wires is highly recommended, particularly for ground and power wires.  In the example below, black is ground, red is power, blue is SDA, and green is SCL.

1. Place the chip on a breadboard.
<img src="../images/CCS811.jpeg">

2. Connect the GND pin on the chip to a GND pin on the Arduino (note that there are multiple GND pins on the Arduino, it doesn't matter which one you choose).
<img src="../images/GND.jpeg">

3. Connect the VCC pin on the chip to the 5V pin on the Arduino.
<img src="../images/VCC.jpeg">

4. Connect the SDA pin on the chip to the SDA pin on the Arduino.
<img src="../images/SDA.jpeg">

5. Connect the SCL pin on the chip to the SCL pin on the Arduino.
<img src="../images/SCL.jpeg">

6.  Connect the WAKE pin on the chip to a GND pin on the Arduino (again doesn't matter which GND pin you choose).
<img src="../images/WAKE.jpeg">

## Step 5: Run the Sensor Code
#TODO
