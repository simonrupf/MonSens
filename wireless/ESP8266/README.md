ESP8266
=======

Using the Espressif ESP8266 as an MCU allows us to directly offer a service to
read sensor measurements over a wireless network (WiFi).

These MCUs come in many flavours. Easiest to use are the so called Development
boards which come with an integrated USB to serial converter. The documentation
below is focused on the usage of the NodeMCU, as it is one of the most widely
available and cheaper solutions, but when choosing the appropriate board
settings, these instructions will work just as well with the ESP-WROOM-02 or the
Wemos D1 family.


Preparations
------------

You need to install the Arduino IDE to compile the program and flash it on to
the NodeMCU. Download the version for your operating system at:
https://www.arduino.cc/en/Main/Software

Install or unpack the Arduino IDE and start it. Select the menu "File" >
"Preferences". In the text area labeled as "Additional Boards Manager URLs" add
the following URL:
http://arduino.esp8266.com/stable/package_esp8266com_index.json

Save this change by clicking on the "OK" button on the bottom right.

Now select the menu "Tools" > "Board" > "Boards Manager". In the "type" drop down
on the top left select "Contributed". Finally select "esp8266" and click the
"Install" button.

Similarly select the menu "Sketch" > "Include library" > "Manage Libraries...".
In the "Filter your search" text field type in "WiFiManager" and hit the return
key to start the search. Finally select the latest "WiFiManager" library and
click the "Install" button.

After all is downloaded and installed into your Arduino IDE, you can close this
window and select "NodeMCU 1.0 (ESP-12E Module)" in the menu "Tools" > "Boards".

You can now either create a new sketchbook (as projects are called in the Arduino
IDE) or use the provided script to copy the provided sketchbooks and libraries
into your sketchbook folder:

```bash
$ ./initialize-sketchbooks.sh ~/Arduino
```

You should now find a sketchbook called "monsens-nodemcu-example" in the
Arduino IDE. Don't forget to change your WiFi credentials and uncomment the code
blocks according to your sensor.

Before uploading connect your NodeMCU into any USB port and select the correct
one in "Tools" > "Ports" (use the dmesg command to figure out which it is). Then
you can compile and upload the sketchbook to the NodeMCU and its server will
start immediatly after the upload is finished.

To test the measurements you can telnet into the port 30303 (or the one you
configured) of the devices IP and then type in the command:

```bash
$ telnet [FQDN or IP] 30303
```

You can also use netcat or ncat to take a reading, here with the "C" command:

```bash
$ echo C | netcat -q -1 [FQDN or IP] 30303
$ echo C | ncat -C -d 1 [FQDN or IP] 30303 2> /dev/null
```

WiFi settings
-------------

This project makes use of the WiFiManager library that assists you configuring
your ESP8266's connection to your WLAN. To configure do either:

A) set your WiFi SSID and (optional) password using the setter functions:

```c++
// this is the port that your monitoring system may read the sensors at
const int port = 30303;

#include <MonSens_ESP8266.h>

MonSens_ESP8266 mcu;

// include and create your sensor object(s) here

void setup() {
  mcu.setSsid("your WiFi's SSID");
  // if your WiFi has no password (really?), skip this line
  mcu.setPassword("your own super secret WiFi password");
  mcu.setPort(port);
  mcu.init();
  // add your sensor(s) here
}

void loop() {
  mcu.communicate();
}
```

B) use the WiFiManager to configure your WiFi settings via a browser:

```c++
// this is the port that your monitoring system may read the sensors at
const int port = 30303;

#include <MonSens_ESP8266.h>

MonSens_ESP8266 mcu;

// include and create your sensor object(s) here

void setup() {
  // note that setSsid is not used here
  mcu.setPort(port);
  mcu.init();
  // add your sensor(s) here
}

void loop() {
  mcu.communicate();
}
```

After uploading the sketch without `setSsid()` you can see on the serial console
of the Arduino IDE if previous settings were detected and are used. If this is
the first time you upload a sketch to this MCU, WiFiManager won't find a
configuration and create a temporary new WiFi called "MonSens". Find and connect
to that WiFi with a Laptop, Tablet or Smartphone and you should be redirected to
a new browser window that lets you configure your WiFi settings. It should offer
you a list of nearby WiFi SSIDs and you can choose your own and set the password.
Once you set these values, they are persisted in the EEPROM of the unit and it
will reboot, connecting to that WiFi.

If these settings are no longer valid and connecting fails or if you move the
MCU out of range of your WiFi, it will fall back to the WiFiManager mode that
lets you reconfigure a new WiFi to use.

To reset any previous stored configuration, upload a sketch that sets an empty
SSID:

```c++
  mcu.setSsid("");
```

This will force the WiFiManager to run every time in AP mode, so you need to
remove this line again and reupload the sketch once more to restore its proper
behaviour.

Other boards
------------

If you use other boards then the NodeMCU, make sure that you select the correct
board type in the the menu "Tools" > "Boards". If the upload fails, you might
simply have selected the wrong board configuration.

For the **Wemos D1 mini lite**, which is based on the ESP8285 chip, you will also
need to add a new section to your `~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/boards.txt`
file as per this example, to make the `esptool` use the "dio" flash mode:
https://github.com/esp8266/Arduino/pull/3169/files#diff-fce09ad94aad2ba67472cd9142f00146
