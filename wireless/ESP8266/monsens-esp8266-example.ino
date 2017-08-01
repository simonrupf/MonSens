/**
 * MonSens ESP8266 example sketchbook
 *
 * This sketchbook shows you how to use multiple sensors and expose them via TCP
 * port 30303 to read sensor data.
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

#include <MonSens_ESP8266.h>

/* uncomment and adjust the below section when using the BME280 sensor
#include <MonSens_BME280.h>

// hardware SPI pins on NodeMCU v1, v2 & v3
#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme(BME_CS); // comment when not using hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // uncomment when using software SPI
//Adafruit_BME280 bme; // uncomment when using I2C
MonSens_BME280 bme280;
*/

/* uncomment the below section for using the Photoresistor
#include <MonSens_Photoresistor.h>

MonSens_Photoresistor photo;
*/

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

  /* uncomment the below section when using the BME280 sensor
  bme280.setBme(bme);
  mcu.addSensor(bme280);
  */

  /* uncomment the below section when using the Photoresistor
  // analog pin the Photoresistor is plugged in to
  photo.setAnalogPin(A0);
  mcu.addSensor(photo);
  */
}
 
/**
 * main loop
 *
 * read string sent to server, then evaluate it and print an according result
 */
void loop() {
  mcu.communicate();
}

