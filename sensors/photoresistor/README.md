Photoresistor
=============

Photoresistors change their resistance depending on the light level in the
environment. Typical photoresisters have a very high resistance of up to a few
MΩ in the dark and only a few hundred Ω in bright conditions.

Use cases
---------

This sensor can be used to measure if a light was switched on in a room, how
light levels change throughout the day at a location or as a rudamentatiry cloud
coverage indicator in a weather station.

Limitations
-----------

For the voltage measurement an analog input is used and on the ESP8266 there is only one such pin, which limits you to only one sensor per ESP8266 that uses analog input. Also an additional resistor is needed to complete the resistor bridge towards ground.  In the examples below a 220 Ω resistor is used.

Wiring
------

The following is an example for connecting a photoresistor to a NodeMCU using
the MCU's `A0` analog pin.

![photoresistor connected to a NodeMCU](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/photoresistor/photoresistor%20nodemcu.png)

Here below is an example for connecting the Adafruit BME280 breakout board to
a DigiSpark on pin `2` (which is the analog input `1`).

![photoresistor connected to a DigiSpark](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/photoresistor/photoresistor%20digispark.png)

