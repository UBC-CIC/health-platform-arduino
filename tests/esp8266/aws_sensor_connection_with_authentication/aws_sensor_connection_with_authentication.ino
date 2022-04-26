/* Adapted from the code provided from ESP8266 AWS IoT example by Evandro Luis Copercini
   Public Domain - 2017
   This example needs https://github.com/esp8266/arduino-esp8266fs-plugin

   Sends TVOC and C02 data using MQTT to an AWS endpoint authenticated
   by previously uploading the device cert, private key and root CA to the board memory

*/

// To be able to read files from board's non volatile file system
#include "FS.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Needed for time sync and AWS authentication
#include <NTPClient.h>

#include <WiFiUdp.h>
#include <DFRobot_CCS811.h>

// To be able to publish messages to MQTT in the JSON schema format
#include <ArduinoJson.h>

// Enables dynamic configuration of wifi credentials through wifi enabled device
#include <WiFiManager.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Insert the AWS IOT provided endpoint for interacting with the device 
const char *AWS_endpoint = ""; 

float co2;
float tvoc;
char nowbuf[100];

// Declares sensor readings 
DFRobot_CCS811 sensor;
int interval = 10000;

// Insert the topic name that you want to publish/subscribe to for data sending and recieving 
const char *aws_topic = "";

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Utilizes the uploaded certificates in the '/data' folder to allow for a secure connection
WiFiClientSecure espClient;

// Creates a fully initialized client instance with server address, port to connect to, 
// message callback pointer and stream to write messages to 
PubSubClient client(AWS_endpoint, 8883, callback, espClient); // set  MQTT port number to 8883 as per standard
long lastMsg = 0;
char msg[50];
int value = 0;

// Time sync to allow for X509 Certificate validation and get UTC timestamp values 
void setClock()
{
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
  Serial.print(strftime(nowbuf, sizeof(nowbuf), "%Y-%m-%d %T", gmtime_r(&now, &timeinfo)));
  strcat(nowbuf, ".000Z");
}

void publishMessage()
{
  StaticJsonDocument<200> docCO2;
  StaticJsonDocument<200> docTVOC;
  char jsonBuffer[512];

  docCO2["sensorId"] = String(ESP.getChipId());
  docCO2["measurementType"] = "CO2";
  docCO2["measurement"] = String(co2);
  docCO2["timestamp"] = nowbuf;

  serializeJson(docCO2, jsonBuffer); // print to client
  client.publish(aws_topic, jsonBuffer);

  docTVOC["sensorId"] = String(ESP.getChipId());
  docTVOC["measurementType"] = "TVOC";
  docTVOC["measurement"] = String(tvoc);
  docTVOC["timestamp"] = nowbuf;

  serializeJson(docTVOC, jsonBuffer); // print to client
  client.publish(aws_topic, jsonBuffer);
}

void setup_wifi()
{

  WiFiManager wifiManager;

  // if uncommented, will reset stored wifi credentials on every boot
  // wifiManager.resetSettings();

  wifiManager.autoConnect("ESP8266ConnectAP", "password");
  WiFiManagerParameter custom_text_endpoint("key_num", "Enter your endpoint here", "", 60); 
  delay(10);
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }

  espClient.setX509Time(timeClient.getEpochTime());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESPthing"))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      publishMessage();

    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf, 256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  setup_wifi();

  while (sensor.begin() != 0)
  {
    Serial.println("failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }

  delay(1000);

  if (!SPIFFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());

  // Load certificate file
  File cert = SPIFFS.open("/cert.der", "r"); // replace cert.crt with your uploaded file name
  if (!cert)
  {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Success to open cert file");

  delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");

  // Load private key file
  File private_key = SPIFFS.open("/private.der", "r"); // replace private.der with your uploaded file name
  if (!private_key)
  {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Success to open private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");
  // Load CA file
  File ca = SPIFFS.open("/ca.der", "r"); // replace ca with your uploaded file name

  if (!ca)
  {
    Serial.println("Failed to open ca ");
  }
  else
    Serial.println("Success to open ca");

  delay(1000);

  if (espClient.loadCACert(ca))
    Serial.println("ca loaded");
  else
    Serial.println("ca failed");

  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());
}

void loop()
{

  setClock();
  co2 = sensor.getCO2PPM();
  tvoc = sensor.getTVOCPPB();

  if (sensor.checkDataReady() == true)
  {
    co2 = sensor.getCO2PPM();
    tvoc = sensor.getTVOCPPB();
  }

  else
  {

    Serial.println("Data is not ready!");
  }

  if (client.connected())
  {
    publishMessage();
    client.loop();
  }
  else
  {
    reconnect();
  }

  sensor.writeBaseLine(0x447B);
  delay(interval);
}
