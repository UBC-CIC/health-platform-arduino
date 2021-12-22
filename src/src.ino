/* Adapted from code provided by:
 * https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor 
 * https://github.com/DFRobot/DFRobot_CCS811/blob/master/examples/readData/readData.ino 
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/WiFiNINAUdpNTPClient
 */

#include <DFRobot_CCS811.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

// time between readings (ms), must be at least 1000ms
int interval = 5000;

// TODO: CHANGE THIS! Needs to be generated elsewhere to prevent duplicates and map to a patient
// unique id for the sensor
char sensorId[3] = "152";

DFRobot_CCS811 sensor;

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;    // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;             // your network key Index number (needed only for WEP)

unsigned int localPort = 2390; // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

WiFiUDP Udp; // A UDP instance to let us send and receive packets over UDP

void setup(void)
{
    // set up serial connection
    Serial.begin(115200);
    while (!Serial) {
        ;
    }

    setup_wifi();
    setup_CCS811();
}

void loop() {
    // TODO: send reading to AWS IoT endpoint
    if(sensor.checkDataReady() == true){
        Serial.print("CO2: ");
        Serial.print(sensor.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(sensor.getTVOCPPB());
        Serial.print("ppb, timestamp: ");
        Serial.println(get_timestamp());
    } else {
        Serial.println("Data is not ready!");
    }

    /*!
     * @brief Set baseline
     * @param get from getBaseline.ino
     */
    sensor.writeBaseLine(0x847B);

    // delay cannot be less than measurement cycle
    // subtract 1s due to the delay in receiving the time from the NTP server
    delay(interval - 1000);
}

void setup_wifi() {
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
    }

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);

        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }

    Serial.println("Connected to wifi");
    printWifiStatus();

    Serial.println("\nStarting connection to server...");
    Udp.begin(localPort);
}

void setup_CCS811() {
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sensor.begin() != 0) {
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);

    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision

    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12]  = 49;
    packetBuffer[13]  = 0x4E;
    packetBuffer[14]  = 49;
    packetBuffer[15]  = 52;

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp.beginPacket(address, 123); //NTP requests are to port 123
    Udp.write(packetBuffer, NTP_PACKET_SIZE);
    Udp.endPacket();
}

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

unsigned long get_timestamp() {
    sendNTPpacket(timeServer); // send an NTP packet to a time server

    // wait to see if a reply is available
    delay(1000);

    if (Udp.parsePacket()) {
        // We've received a packet, read the data from it
        Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

        //the timestamp starts at byte 40 of the received packet and is four bytes,
        // or two words, long. First, extract the two words:
        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

        // combine the four bytes (two words) into a long integer
        // this is NTP time (seconds since Jan 1 1900):
        unsigned long secsSince1900 = highWord << 16 | lowWord;

        // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
        const unsigned long seventyYears = 2208988800UL;

        // subtract seventy years:
        unsigned long epoch = secsSince1900 - seventyYears;

        return epoch;
    }

    return 0;
}