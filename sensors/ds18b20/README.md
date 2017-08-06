Dallas 18B20
============

The Maxim (formerly Dallas) Dallas 18B20 sensor measures temperature. There are
a few variants of the sensor around and it is available in multiple ready-to-use
packagings, like in a water-tight metal cylinder or on a break-out board.

Use cases
---------

This sensor is relatively precise and very cheap, making it ideal for remote
thermometer use.

Using it with DigiSpark MCUs and USB extension cables where needed, you could
place sensors in front and back, top and bottom of a server rack, to monitor
temperatures of the air in- and out-flow.

When used with ESP8266 MCUs, it could be used to monitor temperature in various
rooms, even without a network port. Optionally batteries could be used in such
a case, to make to project truly wireless.

Limitations
-----------

The sensor uses one wire protocol to both sending and receiving on a single pin.
Multiple sensors may be connected to the same wire and addressed by index, but
at this time only a single temperature can be requested, so multiple Dallas
18B20 on the same MCU can't be differenciated.

The default power mode requires three connections to the sensor: Vcc (both 3.3
and 5 V will work), ground and the serial signal. Optionally the sensor can be
used in "parasite" mode: You shorten the _sensors_ Vcc to ground and connect
ground and serial signal to the MCU (note that this still requires a resistor
between Vcc and the serial pin on the MCU side). This allows you to use just to
wires to the sensor. On the other hand, many issues were reported with
"parasite" mode and longer wire lengths between MCU and sensor, when this might
be considered a benefit.

Wiring
------

When using a bare Dallas 18B20 (TO-92 package, frequently used for transistors)
you need to have a 4.7 kΩ resistor between Vcc and the pin used for serial
communication. Breakout boards usually have such a resistor on board.

The following is an example for connecting Dallas 18B20 to a NodeMCU on `D4`.

![Dallas 18B20 connected to a NodeMCU](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/ds18b20/ds18b20%20nodemcu.png)

Here below is an example for connecting Dallas 18B20 to a DigiSpark on pin `2`.

![Dallas 18B20 connected to a DigiSpark](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/ds18b20/ds18b20%20digispark.png)

