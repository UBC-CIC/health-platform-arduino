# Test CCS811 Instructions

The test code provided [here](test_CCS811.ino) will read from the CCS811 CO2 and TVOC sensor every second and print the results to the serial output.

1. Connect the Arduino board and the CCS811 sensor (see **Step 4** in the [setup instructions](../../docs/arduino_setup.md)) to your computer using the USB blaster cord.

2. Open the tests/test_CCS811/test_CCS811.ino file from this repo in the Arduino IDE.

3. Upload the code to the Arduino, the way you did for the Blink example in **Step 3** in the [setup instructions](../../docs/arduino_setup.md).

4. Open the Serial Monitor.  Make sure the baud rate is set to 115200, since that is what the code uses.
<img src="../../images/CCS811_test.png">
<img src="../../images/baud.png">
