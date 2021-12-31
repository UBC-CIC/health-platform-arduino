/* Adapted from the code provided by 
 * https://medium.com/accenture-the-dock/esp8266-aws-iot-core-guide-c640f2622a51
 * and https://github.com/odelot/aws-mqtt-websockets
 */

#include <Arduino.h>
#include <Stream.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//AWS
#include "sha256.h"
#include "Utils.h"


//WEBSockets
#include <Hash.h>
#include <WebSocketsClient.h>

//MQTT PUBSUBCLIENT LIB 
#include <PubSubClient.h>

//AWS MQTT Websocket
#include "Client.h"
#include "AWSWebSocketClient.h"
#include "CircularByteBuffer.h"

extern "C" {
  #include "user_interface.h"
}

#include "arduino_secrets.h"

// delay between sensor readings (ms)
int interval = 10000;

//AWS IOT config
char wifi_ssid[]       = SECRET_SSID;
char wifi_password[]   = SECRET_PASS;
char aws_endpoint[]    = SECRET_ENDPOINT;
char aws_key[]         = SECRET_AWS_KEY;
char aws_secret[]      = SECRET_AWS_SECRET_KEY;

char aws_region[]      = "ca-central-1";
const char* aws_topic  = "arduino/simple";
int port = 443;

//AWS root certificate
const char ca[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
REPLACE THIS WITH YOUR ROOT CERTIFICATE
-----END CERTIFICATE-----
)EOF";

//MQTT config
const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 1;

ESP8266WiFiMulti WiFiMulti;

AWSWebSocketClient awsWSclient(1000);

PubSubClient client(awsWSclient);

//# of connections
long connection = 0;

//generate random mqtt clientID
char* generateClientID () {
  char* cID = new char[23]();
  for (int i=0; i<22; i+=1)
    cID[i]=(char)random(1, 256);
  return cID;
}

//count messages arrived
int arrivedcount = 0;

//callback to handle mqtt messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

//connects to websocket layer and mqtt layer
bool connect () {
    if (client.connected()) {   
        client.disconnect ();
    }  
    //delay is not necessary... it just help us to get a "trustful" heap space value
    delay (1000);
    Serial.print (millis ());
    Serial.print (" - conn: ");
    Serial.print (++connection);
    Serial.print (" - (");
    Serial.print (ESP.getFreeHeap ());
    Serial.println (")");

    //creating random client id
    char* clientID = generateClientID ();

    client.setServer(aws_endpoint, port);

    if (client.connect(clientID)) { // this is what triggers the exceptions mentioned in the instructions
      Serial.println("connected");     
      return true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      return false;
    }
}

//subscribe to a mqtt topic
void subscribe () {
    client.setCallback(callback);
    client.subscribe(aws_topic);
   //subscript to a topic
    Serial.println("MQTT subscribed");
}

//send a message to a mqtt topic
void sendmessage () {
    //send a message   
    char buf[100];
    strcpy(buf, "{\"msg\": \"Hello world!\"}");   
    int rc = client.publish(aws_topic, buf); 
}

void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void setup() {   
    wifi_set_sleep_type(NONE_SLEEP_T);
    Serial.begin (115200);
    delay (2000);
    Serial.setDebugOutput(1);

    //fill with ssid and wifi password
    WiFiMulti.addAP(wifi_ssid, wifi_password);

    Serial.println ("connecting to wifi");
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
        Serial.print (".");
    }
    Serial.println ("\nconnected");
    
    setClock(); // Required for X.509 certificate  validation

    //fill AWS parameters    
    awsWSclient.setAWSRegion(aws_region);
    awsWSclient.setAWSDomain(aws_endpoint);
    awsWSclient.setAWSKeyID(aws_key);
    awsWSclient.setAWSSecretKey(aws_secret);
    awsWSclient.setUseSSL(true);
    awsWSclient.setCA(ca);
    //as we had to configurate ntp time to validate the certificate, we can use it to validate aws connection as well
    awsWSclient.setUseAmazonTimestamp(false);

    if (connect ()){
      subscribe ();
    }
}

void loop() {
  //keep the mqtt up and running
  if (awsWSclient.connected ()) {
      sendmessage (); 
      client.loop ();
  } else {
    //handle reconnection
    if (connect ()){
      subscribe ();      
    }
  }
  delay(interval);
}
