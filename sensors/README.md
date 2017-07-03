Sensors
=======

Most of these sensors are easy to connect to an MCU on their own, often
requiring one or more resistors or capacitors to adjust for the MCU power level
or analog input capabilities. For easier use and less soldering it is therefore
easier to use one of the many breakout boards available online. These will
package the sensor with all the required components (usually in SMD formats) and
leads out clearly labelled pins to solder it onto the MCU with a few short wires
or to stick it to a breadboard for testing.

Illustrations
-------------

Included with the supported sensors description are Fritzing project files that
show working examples for wiring these to the various MCUs. You may extend these
with your own modifications.

As a convention the following wire colors are used throughout these sketches:

- power:
  - red: 3.3 V (ESP8266) / 5 V (DigiSpark)
  - black: ground
- SPI bus:
  - orange: serial clock (SCLK or SCK)
  - yellow: master input, slave output (MISO or SDO on the sensor side)
  - green: master output, slave input (MOSI or SDI on the sensor side)
  - blue: chip select (CS or SS for slave select)
- I²C bus:
  - brown: signal clock (SCL)
  - white: signal data (SDA)

