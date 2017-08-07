/**
 * MonSens Dallas 18B20 temperature sensor on a ESP8266 MCU example sketchbook
 *
 * This sketchbook shows you how to use the Dallas 18B20 on a ESP8266 and
 * expose it via TCP port 30303 to read the sensor data.
 */

// the following constants need to be changed according to your WiFi settings
const char* ssid = "your WiFi's SSID";
const char* password = "your own super secret WiFi password";

// this is the port that your monitoring system may read the sensors at
const int port = 30303;

// (optional) conserve memory by reducing the reserved space for the following
// variables
// maximum sensors supported, defaults to 10 (this example only uses one)
#define MONSENS_MAX_SENSORS 10

#include <MonSens_ESP8266.h>
MonSens_ESP8266 mcu;

#include <MonSens_DS18B20.h>

// Digital pin connected to the serial pin of the Dallas temperature sensor
OneWire oneWire(D4);
MonSens_DS18B20 temp;

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

  temp.setWire(&oneWire);
  mcu.addSensor(temp);
}
 
/**
 * main loop
 *
 * read string sent to server, then evaluate it and print an according result
 */
void loop() {
  mcu.communicate();
}

