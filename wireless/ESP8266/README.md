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
configured) of the devices IP:

```bash
$ telnet 1.2.3.4 30303
```

