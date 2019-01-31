# rfid-reader
This repository contains code to run on ESP8266 microprocessor used to interface HID Prox Pro II RFID Readers with the WJRH door access systsm.

Developed by Hayden Dodge and Clement Hathaway.

Based on https://create.arduino.cc/projecthub/shakataganai/hid-prox-rfid-to-arduino-bd9b8a
    
    HID RFID Reader Wiegand Interface for Arduino Uno
    Originally by  Daniel Smith, 2012.01.30 -- http://www.pagemac.com/projects/rfid/arduino_wiegand

    Updated 2016-11-23 by Jon "ShakataGaNai" Davis.
    See https://obviate.io/?p=7470 for more details & instructions

    https://gist.github.com/ShakataGaNai/4319d3e82a858c9d00c1d80f20da81a3#file-hid-prox-weigand-ino

# Setting up your workspace
The ESP8266 can be set up through the Arduino IDE. Download the latest Arduino IDE at https://www.arduino.cc/. At the time of developement, Arduino 1.8.4 was used. After downloading the IDE, go to "File" -> "Preferences" and add http://arduino.esp8266.com/stable/package_esp8266com_index.json to the "Additional Boards Manager URLs" field. Then go to "Tools" -> "Board: XXX" pullout and select "Boards Manager...". Search for "esp8266" and install the latest version. Then in the "Board: XXX" pullout, select "NodeMCU 1.0 (ESP-12E Module)".

At the time of posting, the board setting in the tools drop down was set to Board: "NodeMCU 1.0 (ESP-12E Module)".
The programmer was set to Programmer: "AVRISP mkII".

# Uploading code
Utilize the Arduino IDE to upload code to the ESP8266.

# ESPMacAddrTool
This tool can be used to verify a connection to a network prior. This tool will provide the mac address of the ESP and the assigned IP address after connecting to the specified network. The tool will also periodically display the status code of the WiFi module when the WiFi connection has not yet succeeded.

If there are issues with changing the hostname, comment out the hostname section of the code and run again. If this succeeds, uncomment the hostname change code and reupload.

WiFi Module status codes descriptions:

    0 : WL_IDLE_STATUS when Wi-Fi is in process of changing between statuses
    1 : WL_NO_SSID_AVAILin case configured SSID cannot be reached
    3 : WL_CONNECTED after successful connection is established
    4 : WL_CONNECT_FAILED if password is incorrect
    6 : WL_DISCONNECTED if module is not configured in station mode

# WJRH-TagReaderPlus26
This code runs on an ESP8266 wired to an HID HID Prox Pro II RFID Reader.
When uploading to a tag reader, replace the network password, hostname for this unit, ip address of the door system server and the port.
