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

The serial device needs to be initialized with the following settings:

```bash
stty -F $2 min 60 time 1 ignbrk -onlcr  -iexten -echo -echoe -echok -echoctl -echoke
```

If you have the ModemManager installed, it might interfere with the device and
set incorrect modes. To avoid this, you can add the following udev rule in to
a file like `/etc/udev/rules.d/49-digispark.rules`:

```
ATTRS{idVendor}=="16d0", ATTRS{idProduct}=="087e", ENV{ID_MM_DEVICE_IGNORE}="1"
```

The vendor and product ID can be discovered using `lsusb`. Usually udev needs to
be reloaded and the device replugged, before the new rule is applied:

```bash
sudo udevadm control --reload-rules
```

Telnet-ish server
-----------------

To make the measurements accessible via telnet (as may be used by Zabbix) you
could use netcat for a one-shot or xinetd or socat for a permanent solution.

```bash
$ exec 3<>/dev/ttyACM0; echo C >&3; head -n1 <&3 | netcat -l 4000; exec 3<&-
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
    server_args     = -c "exec 3<>/dev/ttyACM0; echo C >&3; head -n1 <&3; exec 3<&-"
} 
```

And the socat variant:

```bash
$ socat tcp-l:4000,reuseaddr,fork system:"exec 3<>/dev/ttyACM0; echo C >&3; head -n1 <&3; exec 3<&-"
```

Instead of using the root user, another user that is in the `dialout` group may
be used.

In all these example the TCP port 4000 is used, which you may change as you
like. If you would prefer the measurement in Kelvin instead of Celsius, change
the "echo C" bit to "echo K".

Zabbix agent
------------

If you have the zabbix agent installed on the system, your DigiSpark-based
sensor is plugged into, then you can directly expose the reading to Zabbix.

In the `/etc/zabbix/zabbix_agentd.conf` file you just need to add an additional
UserParameter:

```
UserParameter=MonSens[*],stty -F $2 min 60 time 1 ignbrk -onlcr  -iexten -echo -echoe -echok -echoctl -echoke; exec 3<>$2; echo $1 >&3; head -n1 <&3; exec 3<&-
```

Then add the zabbix user to the dialout group and restart the agent.

In your template or host configuration on the server you can now configure an
item using a key like this one:

```
MonSens[C,/dev/ttyACM0]
```

In this example the temperature in `C` (Celsius) was requested, from the device
attached on /dev/ttyACM0.
