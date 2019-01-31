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
The ESP8266 can be set up through the Arduino IDE. Download the latest Arduino IDE here. At the time of developement, Arduino 1.8.4 was used. After downloading the IDE, go to "File" -> "Preferences" and add http://arduino.esp8266.com/stable/package_esp8266com_index.json to the "Additional Boards Manager URLs" field. Then go to "Tools" -> "Board: XXX" pullout and select "Boards Manager...". Search for "esp8266" and install the latest version. Then in the "Board: XXX" pullout, select "NodeMCU 1.0 (ESP-12E Module)".

At the time of posting, the board setting in the tools drop down was set to Board: "NodeMCU 1.0 (ESP-12E Module)".
The programmer was set to Programmer: "AVRISP mkII".

# Uploading code
Utilize the Arduino IDE to upload code to the ESP8266.

# ESPMacAddrTool
This tool can be used to verify a connection to a network prior. This tool will provide the mac address of the ESP and the assigned IP address after connecting to the specified network. The tool will also periodically display the status code of the WiFi module when the WiFi connection has not yet succeeded.


