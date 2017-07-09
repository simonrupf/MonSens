/**
 * MonSens photoresistor on a ESP8266 MCU example sketchbook
 *
 * This sketchbook shows you how to use a photoresistor on a ESP8266 and
 * expose it via TCP port 30303 to read the sensor data.
 */

// the following constants need to be changed according to your WiFi settings
const char* ssid = "your WiFi's SSID";
const char* password = "your own super secret WiFi password";

// this is the port that your monitoring system may read the sensors at
const int port = 30303;

// (optional) conserve memory by reducing the reserved space for the following
// variables
// maximum sensors supported, defaults to 10 (this example only uses 2)
#define MONSENS_MAX_SENSORS 10
// maximum length of measurement strings, defaults to 9 (5 digits, 1 decimal
// point, 2 digits after the point and 1 string termination character)
#define MONSENS_MAX_MEASUREMENT_WIDTH 9

#include <MonSens_ESP8266.h>
#include <MonSens_Photoresistor.h>

MonSens_Photoresistor photo;
MonSens_ESP8266 mcu;

/**
 * initialize ESP8266 and sensors
 */
void setup() {
  Serial.begin(115200);
  delay(10);

  mcu.setSsid(ssid);
  mcu.setPassword(password);
  mcu.setPort(port);
  mcu.init();

  // analog pin the Photoresistor is plugged in to
  photo.setAnalogPin(A0);
  mcu.addSensor(photo);
}
 
/**
 * main loop
 *
 * read string sent to server, then evaluate it and print an according result
 */
void loop() {
  mcu.communicate();
}

