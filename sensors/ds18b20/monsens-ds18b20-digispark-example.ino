/**
 * MonSens Dallas 18B20 temperature sensor on a ESP8266 MCU example sketchbook
 *
 * This sketchbook shows you how to use the Dallas 18B20 on a DigiSpark and
 * expose it via USB serial interface to read the sensor data.
 */

// (optional) conserve memory by reducing the reserved space for the following
// variables
// maximum sensors supported, defaults to 10 (this example only uses 1)
#define MONSENS_MAX_SENSORS 10

#include <MonSens_DigiSpark.h>
MonSens_DigiSpark mcu;

#include <MonSens_DallasTemperature.h>

// Digital pin connected to the serial pin of the Dallas temperature sensor
OneWire oneWire(1);
MonSens_DallasTemperature temp;

/**
 * initialize DigiSpark and sensors
 */
void setup() {
  mcu.init();
  temp.setWire(&oneWire);
  mcu.addSensor(temp);
}
 
/**
 * main loop
 *
 * read characters off the serial interface, then evaluate it and print an
 * according result
 */
void loop() {
  mcu.communicate();
}

