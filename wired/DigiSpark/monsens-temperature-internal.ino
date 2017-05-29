/**
 * MonSens DigiSpark sketchbook for internal temperature sensor
 *
 * This sketchbook exposes the DigiSparks internal temperature sensor on USB
 * serial interface.
 */

#include <DigiCDC.h>

#define prompt "> "

String input;

/**
 * initialize USB interface
 */
void setup() {                
  SerialUSB.begin(); 
  SerialUSB.write(prompt);
  analogReference(INTERNAL1V1);
}

/**
 * main loop
 *
 * read characters off the serial interface until a line break is received,
 * then evaluate it and print an according result or usage instructions
 */
void loop() {
  while (SerialUSB.available()) {
    SerialUSB.delay(3);             // delay to allow buffer to fill
    if (SerialUSB.available() > 0) {
      char c = SerialUSB.read();    // gets one byte from serial buffer
      if (c == F("\n")) {
        break;
      }
      input += c;
    }
  }

  if (input.length() > 0) {
    int temp = analogRead(A0+15);
    if (input == F("C") || input == F("K")) {
      if (input == F("C")) {
        temp -= 273;
      }
      SerialUSB.println(temp);
    } else {
      SerialUSB.println(F("Returns temperature as Celsius or Kelvin. List of commands:"));
      SerialUSB.println(F("C"));
      SerialUSB.println(F("K"));
    }
    SerialUSB.write(prompt);
    input = "";
  }

  SerialUSB.delay(100);
}

