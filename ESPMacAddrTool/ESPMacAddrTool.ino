#include <ESP8266WiFi.h>

const char* ssid     = "WJRH";
const char* password = "password";
const char* hostnamex = "WJRH-ESP";

byte mac[6];
char macAddr[18];


void setup() {
  // Wait for user to pull up Ardiono IDE Serial Monitor
  delay(1000);
  
  // Open Serial port
  Serial.begin(115200);

  delay(500);
  
  // Get mac address
  WiFi.macAddress(mac); // Assign MAC address to the byte array variable
  printMAC();

  // Change hostname
  Serial.printf("Changing hostname ... %s\n", WiFi.hostname(hostnamex) ? "" : "Failed!");
  Serial.printf("Hostname: %s\n", WiFi.hostname().c_str());

  // Set ESP8266 to be a station
  Serial.printf("Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");

  delay(500); // needed to allow the mode to change
  
  // Connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting ...\n");

  // Wait for connection
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
    if(i > 9){
      Serial.printf("   %d\n", WiFi.status());
      i = 0;
    } else {
      i++;
    }
  }
  for(; i < 10; i++){
    Serial.print(' ');
  }
  Serial.printf("   %d\n", WiFi.status());

  // Report IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    
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
  Serial.print(mac[5],HEX);
  Serial.print("\n");
}


