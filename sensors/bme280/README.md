BME280
======

The Bosch BME280 sensor offers humidity, barometric pressure and temperature
sensing in a single chip. Adafruit offers a breakout board to easily connect the
BME280 to an MCU: <https://www.adafruit.com/product/2652>

There are other similar breakout boards that may be used with the Adafruit
libraries, as long as they offer either I2C or SPI interfaces. Using hardware
SPI is preferred, if your MCU supports it.

Use cases
---------

This sensor is ideal for a weather station as it includes the three measurements
typically found in classic analog barometers.

Limitations
-----------

The sensor caches the measurements, which is why they are requested twice to get
an updated number. If using I2C reading all different values is quite slow, so
(hardware) SPI is the preferred interface on ESP8266 MCUs. The Digispark is only
supporting I2C, so do not expect to read out the values too frequently.

Wiring
------

The following is an example for connecting the Adafruit BME280 breakout board to
a NodeMCU using the ESP8266's hardware SPI pins. If the `D8` pin isn't pulled
HIGH during boot, the sensor connected to it interferes with the startup of the
ESP8266. This can be avoided by using a resistor of 2 - 10 kΩ between ground
and `D8` (the illustration below shows a 3.3 kΩ resistor).

![Adafruit BME280 breakout board connected to a NodeMCU using SPI](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/bme280/bme280%20nodemcu.png)

Here below is an example for connecting the Adafruit BME280 breakout board to
a DigiSpark using I2C pins. Although it seems possible to get software SPI
working on the DigiSpark, (software) I2C is better documented and therefore
easier to use.

![Adafruit BME280 breakout board connected to a DigiSpark using I2C](https://raw.githubusercontent.com/elrido/MonSens/master/sensors/bme280/bme280%20digispark.png)

