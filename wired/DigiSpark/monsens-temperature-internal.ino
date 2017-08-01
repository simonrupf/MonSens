/**
 * MonSens DigiSpark sketchbook for internal temperature sensor
 *
 * This sketchbook exposes the DigiSparks internal temperature sensor on USB
 * serial interface.
 */

// (optional) conserve memory by reducing the reserved space for the following
// variables
// maximum sensors supported, defaults to 10 (this example only uses 2)
#define MONSENS_MAX_SENSORS 10

#include <MonSens_DigiSpark.h>
MonSens_DigiSpark mcu;

#include <MonSens_DigiSpark_Temperature.h>

MonSens_DigiSpark_Temperature temp;

#include <MonSens_DigiSpark_Vcc.h>

MonSens_DigiSpark_Vcc vcc;

/**
 * initialize USB interface
 */
void setup() {
  mcu.init();
  mcu.addSensor(temp);
  mcu.addSensor(vcc);
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

