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

You should now find a sketchbook called "monsens-temperature-internal" in the
Arduino IDE and can compile it. The Arduino IDE will tell you when you have to
plug in the DigiSpark into any USB port for the upload to start.

Each time you plugin the DigiSpark, a serial interface will appear after about
5 seconds, the time window for programming the device. Check the output of dmesg
to find the name of the device on your system; Usually it will be called
/dev/ttyACM0.

To make the measurments accessible via telnet (as may be used by Zabbix) you
could use netcat for a one-shot or xinetd or socat for a permanent solution.

```bash
echo -n C > /dev/ttyACM0; head -n1 /dev/ttyACM0 | nc -l 4000
```

For xinetd create a file with the following content in the /etc/xinetd.d folder
and restart the service. If possible use a user from the dialup group instead of
root. The user just needs access to the USB device.

```xinetd
service testservice
{
    port            = 4000
    socket_type     = stream
    protocol        = tcp
    wait            = no
    user            = root
    server          = /bin/sh
    server_args     = -c "echo -n C > /dev/ttyACM0; head -n1 /dev/ttyACM0"
} 
```

And the socat variant:

```bash
socat tcp-l:4000,reuseaddr,fork system:"echo -n C > /dev/ttyACM0; head -n1 /dev/ttyACM0"
```

In all these example the TCP port 4000 is used, which you may change as you
like. If you would prefer the measurement in Kelvin instead of Celsius, change
the "echo -n C" bit to "echo -n K".


