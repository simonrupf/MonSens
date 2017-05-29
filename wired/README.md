Wired Network
=============

To make sensors accessible over a wired network we use a DigiSpark MCU. It offers
few GPIO pins to connect your sensor(s) to and a USB interface to connect to a
server.

Use cases
---------

If the location you want to monitor already has a physical server in it, the MCU
can be connected to it and made accessible over that servers network connection.

If you have a network port available, but no device or if you want to separate
existing servers from the monitoring devices, use a small single board system
like a RaspberryPi, VoCore, etc. instead. What ever the system, if it has a USB-
port and runs Linux, you may use it.

Limitations
-----------

You need access to a wired network connection and a source of power. Some single
board computers may offer power over ethernet (PoE) support, which lets you use
the network cable as a power source.
