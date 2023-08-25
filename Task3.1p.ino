#include <DHT.h>          // DHT library
#include <WiFiNINA.h>     // WiFiNINA library
#include <ThingSpeak.h>   // ThingSpeak library

// Define pin and sensor type for DHT sensor
#define DHTPIN 3       
#define DHTTYPE DHT22  

// ThingSpeak Channel settings
unsigned long channelID = 2250608;         // ThingSpeak Channel ID
const char *apiKey = "5O0P55WVR8XH3OIE";   // ThingSpeak API Key

char ssid[] = "Kartik";    // WiFi SSID
char pass[] = "12345678";  // WiFi password

DHT dht(DHTPIN, DHTTYPE);   // Create a DHT object
WiFiClient client;         // Create a WiFi client object

void setup() 
{
  Serial.begin(9600);     // Initialize the serial port
  dht.begin();            // Initialize the DHT sensor
  connectWiFi();          // Connect to the WiFi network
  ThingSpeak.begin(client); // Initialize the ThingSpeak library
}

void loop() 
{
  delay(2000);  // 2 second delay between readings

  float temperature = dht.readTemperature();     // Retrieve temperature in Celsius
  if (!isnan(temperature)) 
  {
    sendDataToThingSpeak(temperature); // Send the temperature data to ThingSpeak
  } 
  else 
  {
    Serial.println("Failed to retrieve data from DHT sensor!");
  }
  delay(30000); // Wait for 30 seconds
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Connecting to WiFi network...");
    WiFi.begin(ssid, pass);
    delay(1500);
  }
  Serial.println("Connected to WiFi network!");
}

void sendDataToThingSpeak(float temp) 
{
  ThingSpeak.setField(1, temp);       // Set field 1 with temperature data
  int httpCode = ThingSpeak.writeFields(channelID, apiKey);
  if (httpCode == 200) 
  {
    Serial.println("Data forwarded to ThingSpeak");
  } 
  else 
  {
    Serial.println("Error sending data to ThingSpeak");
  }
}
