/**
 * MonSens DigiSpark sketchbook for internal temperature sensor
 *
 * This sketchbook exposes the DigiSparks internal temperature sensor on USB
 * serial interface.
 */

#include <DigiCDC.h>

/**
 * initialize USB interface
 */
void setup() {
  SerialUSB.begin();
  analogReference(INTERNAL1V1);
}

/**
 * main loop
 *
 * read characters off the serial interface, then evaluate it and print an
 * according result
 */
void loop() {
  if (SerialUSB.available()) {
    char c;
    c = SerialUSB.read(); // gets one byte from serial buffer
    SerialUSB.delay(50);  // wait for the shell to be ready to read
    if (c == 'C' || c == 'K') {
      int temp = analogRead(A0+15);
      SerialUSB.refresh();
      if (c == 'C') {
        temp -= 273;
      }
      char val[5];
      sprintf(val, "%d", temp + 8);
      SerialUSB.print(val);
      SerialUSB.print("\n");
    }
  }
  SerialUSB.delay(3);
}

