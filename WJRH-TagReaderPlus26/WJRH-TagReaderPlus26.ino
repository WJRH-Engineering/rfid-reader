#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#define MAX_BITS 100                 // max number of bits 
#define WEIGAND_WAIT_TIME  3000      // time to wait for another weigand pulse.  

////////////////////////////////////////////////////////////////// CONSTANTS

const char* ssid     = "WJRH";
const char* password = "password";
const char* hostnamex = "WJRH-<specify>Door";

WiFiClient client;
IPAddress server(none, of, ur, buisness);
int port = hoy;

unsigned char databits[MAX_BITS];    // stores all of the data bits
unsigned char bitCount;              // number of bits currently captured
unsigned char flagDone;              // goes low when data is currently being captured
unsigned int weigand_counter;        // countdown until we assume there are no more bits
unsigned long cardCode = 0;          // decoded card code

String HTTPData;                     // Variable in memory for data about to be sent over HTTP

////////////////////////////////////////////////////////////////// INTERRUPTS

// interrupt that happens when INTO goes low (0 bit)
void ISR_INT0() {
  //Serial.print("0");   // uncomment this line to display raw binary
  bitCount++;
  flagDone = 0;
  weigand_counter = WEIGAND_WAIT_TIME;

}

// interrupt that happens when INT1 goes low (1 bit)
void ISR_INT1() {
  //Serial.print("1");   // uncomment this line to display raw binary
  databits[bitCount] = 1;
  bitCount++;
  flagDone = 0;
  weigand_counter = WEIGAND_WAIT_TIME;
}

////////////////////////////////////////////////////////////////// SETUP

void setup() {
  Serial.begin(115200);
  Serial.println("Addressing Pins!");
  pinMode(5, INPUT);     // D1 on the board
  pinMode(4, INPUT);     // D2 on the board

  // binds the ISR functions to the falling edge of INTO and INT1
  attachInterrupt(digitalPinToInterrupt(5), ISR_INT0, FALLING);
  attachInterrupt(digitalPinToInterrupt(4), ISR_INT1, FALLING);

  weigand_counter = WEIGAND_WAIT_TIME;

  WiFi.hostname(hostnamex);

  Serial.println("Starting WiFi!");

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


  delay(1000);
  Serial.print("IP Local Address: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
}

////////////////////////////////////////////////////////////////// MAIN LOOP

void loop() {
  if (attemptReadID() == 1) {
    Serial.println("");
    Serial.print("BIN = ");
    Serial.print(cardCode, BIN);
    Serial.print(" | HEX = ");
    Serial.println(cardCode, HEX);
    Serial.print("");

    prepareHTTPData();
    sendHTTPData();
  }
}

////////////////////////////////////////////////////////////////// HELPER FUNCTIONS

void prepareHTTPData() {
  HTTPData = "";
  HTTPData += "GET /esp?id=";
  HTTPData += String(cardCode, HEX);
}

void sendHTTPData() {
  Serial.println("Attempting to connect");

  // Try to connect
  if (client.connect(server, port)) {
    Serial.println("Connected!");
    client.println(HTTPData); // Send HTTPData

    Serial.print("Sent ");
    Serial.print(HTTPData + "\n");


    // Close the connection
    client.println("Connection: close");
    client.println();
    Serial.println("Closed!");
  }
}

int attemptReadID() {
  unsigned char i;
  // This waits to make sure that there have been no more data pulses before processing data
  if (!flagDone) {
    if (--weigand_counter == 0)
      flagDone = 1;
  } else {
    // if we have bits and we the weigand counter went out
    if (bitCount > 0 && flagDone) {
      cardCode = 0;
      if (bitCount == 36) {
        // 36 bit HID Corporate 1000 format
        // for lafayette checkpoints

        // limted bit window based of Renan
        for (i = 2; i < 34; i++) {
          cardCode <<= 1;
          cardCode |= databits[i];
        }

        bitCount = 0;
        for (unsigned char i = 0; i < MAX_BITS; i++) {
          databits[i] = 0;
        }

          Serial.println("READ");
          return 1;
        } else if (bitCount == 26) {
        // 36 bit HID Corporate 1000 format
        // for lafayette checkpoints

        // limted bit window based of Renan
        for (i = 2; i < 26; i++) {
          cardCode <<= 1;
          cardCode |= databits[i];
        }

        bitCount = 0;
        for (unsigned char i = 0; i < MAX_BITS; i++) {
          databits[i] = 0;
        }

          Serial.println("READ");
          return 1;
        }
      } else {
        bitCount = 0;
        for (unsigned char i = 0; i < MAX_BITS; i++) {
          databits[i] = 0;
        }
        return 0;
      }
    }
  }
