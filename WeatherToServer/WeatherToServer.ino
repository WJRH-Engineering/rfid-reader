#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN  5

const char* ssid     = "LC";
//const char* password = "";

// Initialize the client library
WiFiClient client;
IPAddress server(192,168,1,104);
String data;

DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp;         // Values read from sensor
float AVGhumidity, AVGtemp;   // Average Values
const long interval = 2000;   // interval at which to read sensor

unsigned long previousMillis;
unsigned long currentMillis;
byte mac[6];
char macAddr[18];


void setup() {
  
  // Basics
  Serial.begin(115200);
  dht.begin();

  // Connect
  WiFi.mode(WIFI_STA);
  //WiFi.softAPdisconnect(true);
  
  WiFi.begin(ssid);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.macAddress(mac); // Assign MAC address to the byte array variable
  sprintf(macAddr, "%2X:%2X:%2X:%2X:%2X:%2X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); // Normal Case
  //sprintf(macAddr, "%2X:%2X:%2X:%2X:%2X:%2X", mac[0], mac[1], mac[2], mac[3], mac[5], mac[5]); // Special Case
  printMAC();
}

void loop() {
    //// Start Averaing Process for better results
    AVGhumidity = 0.0;
    AVGtemp = 0.0;

    delay(10000);   // So the whole thing takes 30 seconds between reports
    addToAverage(); // 1
    addToAverage(); // 2
    addToAverage(); // 3
    addToAverage(); // 4
    addToAverage(); // 5
    addToAverage(); // 6
    addToAverage(); // 7
    addToAverage(); // 8
    addToAverage(); // 9
    addToAverage(); // 10

    //// Divide to calculate the averages
    AVGhumidity = AVGhumidity/10;
    AVGtemp = AVGtemp/10;

    Serial.println(AVGhumidity);
    Serial.println(AVGtemp);
    
    
    //// Send off our data to the server
    Serial.println("Attempting to Connect...");
    if(client.connect(server, 80)){
      Serial.println("Connected");
      
      updateData();
      client.println(data);
      client.println("Connection: close");
      client.println();

      Serial.println(AVGhumidity);
      Serial.println(AVGtemp);
    }
}

void addToAverage(){
    gettemperature();
    AVGhumidity += humidity;
    AVGtemp += temp;
    delay(2000);
}

void updateData(){
      data = "";
      data += "GET /esp?mac=";
      data += macAddr;
      data += "&temp=";
      data += String(AVGtemp);
      data += "&humidity=";
      data += String(AVGhumidity);
      data += " HTTP/1.1";
}

void printMAC(){
  Serial.print("\nMAC: ");
  Serial.print(mac[0],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.println(mac[5],HEX);
  Serial.print("\n");
}

void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  previousMillis;
  currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
 
    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp = dht.readTemperature(false);      // Read temperature as C
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
