DigiSpark
=========

We use the DigiSpark MCU by DigiStump as a simple bridge to make your sensor
accessible as a serial interface via USB.

Preparations
------------

The following guide is based on this document by DigiStump:
https://digistump.com/wiki/digispark/tutorials/connecting

You need to install the Arduino IDE to compile the program and flash it on to
the DigiSpark. Download the version for your operating system at:
https://www.arduino.cc/en/Main/Software

If using Windows, you will need to install the following drivers manually:
https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip

Install or unpack the Arduino IDE and start it. Select the menu "File" >
"Preferences". In the text area labeled as "Additional Boards Manager URLs" add
the following URL:
http://digistump.com/package_digistump_index.json

Save this change by clicking on the "OK" button on the bottom right.

Now select the menu "Tools" > "Board" > "Boards Manager". In the type drop down
on the top left select "Contributed". Finally select "Digistump AVR Boards" and
click the "Install" button.

After all is downloaded and installed into your Arduino IDE, you can close this
window and select "Digispark (Default - 16.5mhz)" in the menu "Tools" > "Boards".

You can now either create a new sketchbook (as projects are called in the Arduino
IDE) or use the provided script to copy the provided sketchbooks into your
sketchbook folder:

```bash
$ ./initialize-sketchbooks.sh ~/Arduino
```

You should
