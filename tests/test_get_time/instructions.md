# Test Get Time Instructions

The test code provided [here](test_get_time.ino) will connect to a specified WiFi network, send a request for a timestamp to an NTP server every 10 seconds, and print the timestamps in Unix format to the serial output.

1. Connect the Arduino board to your computer using the USB blaster cord.

2. In the test_get_time directory in htis repo, create a new file called arduino_secrets.h.  Open this new file, and paste in the following, replacing YOUR_WIFI_NAME with the name of the WiFi network you want to connect the Arduino to, and YOUR_WIFI_PASSWORD with the network password.

```
#define SECRET_SSID "YOUR_WIFI_NAME"
#define SECRET_PASS "YOUR_WIFI_PASSWORD"
```

3. Open tests/test_get_time/test_get_time.ino from this repo in the Arduino IDE.

4. Upload the code to the Arduino, the way you did for the Blink example in **Step 3** in the [setup instructions](../../docs/arduino_setup.md).

5. Open the Serial Monitor.  Make sure the baud rate is set to 115200, since that is what the code uses.
<img src="../../images/CCS811_test.png">
<img src="../../images/baud.png">
