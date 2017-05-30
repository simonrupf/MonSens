/**
 * MonSens DigiSpark sketchbook for internal temperature sensor
 *
 * This sketchbook exposes the DigiSparks internal temperature sensor on USB
 * serial interface.
 */

#include <DigiCDC.h>

const char prompt[] = "> ";

/**
 * initialize USB interface
 */
void setup() {
  SerialUSB.begin();
  pinMode(1, OUTPUT); // LED on Model A
  analogReference(INTERNAL1V1);
  SerialUSB.refresh();
  SerialUSB.print(prompt);
}

/**
 * print characters and return cursor
 */
void println(char output[]) {
  //SerialUSB.refresh();
  SerialUSB.print(output);
  //SerialUSB.refresh();
  //SerialUSB.print("\r");
  //SerialUSB.refresh();
  SerialUSB.print("\n");
  //SerialUSB.refresh();
}

/**
 * main loop
 *
 * read characters off the serial interface until a line break is received,
 * then evaluate it and print an according result or usage instructions
 */
void loop() {
  if (SerialUSB.available()) {
    char c[1];
    c[0] = SerialUSB.read();  // gets one byte from serial buffer
    digitalWrite(1, HIGH);    // turn the LED on (HIGH is the voltage level)
    println(c);
    if (c[0] == 'C' || c[0] == 'K') {
      int temp = analogRead(A0+15);
      SerialUSB.refresh();
      if (c[0] == 'C') {
        temp -= 273;
      }
      char val[5];
      sprintf(val, "%d", temp + 8);
      println(val);
/*    } else {
      println("commands:");
      println("C");
      println("K");
*/    }
    SerialUSB.delay(50);
    digitalWrite(1, LOW);     // turn the LED off by making the voltage LOW
    SerialUSB.print(prompt);
  }
  SerialUSB.delay(3);
}

