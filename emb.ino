// Define libraries
//-----------------------------
#include <WiFi.h>           // Library to use the wifi of esp
#include <DHT.h>            // Library to be used to read the DHT22 sensor
#include <PubSubClient.h>   // Library to connect to mqtt server and subscribe to topics
#include <ThingSpeak.h>
#include <WebServer.h>

// Define constants and global variables
//-----------------------------
#define DHTPIN 23 // To what pin is the sensor connected
#define DHTTYPE DHT22 // Type of the sensor
float currentTemp = 0;
float currentHum = 0;
float topTemp = 50;   // T1T0 temperature threshold
float topHum = 50;   // H1H0 humidity threshold
int measurementDelay = 1000;          // This will be set every time I receive "updateConfig" D1D0
char testTopicEsp32[150], testTopicServer[150], topicControl[150], topicData[150], topicDataCrc[150];
int measure = 0;
long lastTimeSendData = 0;
const int outputPin = 22;  // Assign output variable to GPIO pin 14 to switch led


// WiFi connection parameters (WPA security protocol)
//-----------------------------
const char* WIFI_SSID = "rsc32";
const char* WIFI_PASSWORD = "esp32#@pass";


// ThingSpeak
//-----------------------------
const char * myIotApiKeyWrite = "CJ6BY323PC7KQZH1";
unsigned long myIotChannel = 796650;  // ThinkSpeak Channel


// Multitasking. declaration of task handlers
//-----------------------------
TaskHandle_t taskHandlerZero;
TaskHandle_t taskHandlerOne;


// MQTT connection parameters
//-----------------------------
const char* MQTT_USER = "testUser";           // *** Replace with your username, e.g. user2, user3 etc. (leave it as it is for the test)
const char* MQTT_CLIENT = "user4";              // *** Must be unique, replace with your username, e.g. user2, user3 etc. (same as MQTT_USER)
const char* MQTT_TOPIC_ESP32 = "esp32";
const char* MQTT_TOPIC_SERVER = "server";
const char* MQTT_TOPIC_CONTROL = "control";
const char* MQTT_TOPIC_DATA = "data";
const char* MQTT_TOPIC_DATACRC = "dataCrc";
const char* MQTT_ADDRESS = "esp-32.zapto.org";


// Standard messages
//-----------------------------
const char* CMD_UPDATE = "updateConfig";
const char* CMD_MEASURE = "startMeasurements";
const char* CMD_CRC_ERROR = "crcError";
const char* CMD_REQUEST_CONFIG = "sendConfig";
const char* INCOMING = "incoming";
const char* OUTGOING = "outgoing";


// Definitions of callback functions
//-----------------------------
void sorting(char*, byte*, unsigned int);


// Instantiation of objects
//-----------------------------
DHT dht(DHTPIN, DHTTYPE);
//WiFiClient wifiClient;                                                           // Construct wifiClient
WiFiClient connectionForMQTT;
WiFiClient connectionForThingSpeak;
PubSubClient client(MQTT_ADDRESS, 1883, sorting, connectionForMQTT);                    // Construct mqtt client
WebServer serverObj(8082);
