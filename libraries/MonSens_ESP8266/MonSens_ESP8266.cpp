/*
 * Copyright © 2017 Simon Rupf
 *
 * This file is part of MonSens.
 *
 * MonSens is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * MonSens is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with MonSens. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * @author Simon Rupf <simon@rupf.net>
 * @brief MonSens implementation for the wireless ESP8266 microcontroller board.
 *
 * The ESP8266 offers a large amount of dynamic and persistent memory and plenty
 * of pins to connect multiple sensors on a single unit. There are multiple
 * revisions of it, but all of them should be usable for MonSens applications.
 */

#include <MonSens_ESP8266.h>

/**
 * Set the SSID of the WiFi network.
 */
void MonSens_ESP8266::setSsid(const char* ssid) {
  wifiSsid = ssid;
}

/**
 * Set the password of the WiFi network.
 */
void MonSens_ESP8266::setPassword(const char* password) {
  wifiPassword = password;
}

/**
 * Inject the port the server should listen on.
 */
void MonSens_ESP8266::setPort(const uint16_t port) {
  tcpPort = port;
}

/**
 * Initialize the communicator, to be called in the MCUs setup routine.
 */
void MonSens_ESP8266::init() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");

  if (strlen(wifiSsid) > 0) {
    // Connect to WiFi network
    Serial.print("Connecting to ");
    Serial.println(wifiSsid);
 
    WiFi.begin(wifiSsid, wifiPassword);
 
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
   } else {
    // initialize the configuration portal or use a stored config
    WiFiManager wifiManager;
    wifiManager.autoConnect("MonSens");
  }

  // Start the server
  server = new WiFiServer(tcpPort);
  server->begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this command to connect: telnet ");
  Serial.print(WiFi.localIP());
  Serial.print(" ");
  Serial.println(tcpPort);
}

/**
 * Read inputs and respond to them, to be called in the MCUs loop routine.
 */
void MonSens_ESP8266::communicate() {
  // Check if a client has connected
  client = server->available();
  if (!client) {
    // wait a bit for a client to connect or send data
    delay(1);
    return;
  }
  Serial.println("new client");

  // Wait until the client sends some data, but not more then MONSENS_ESP8266_TIMEOUT ms
  uint16_t clientTimeout = 0;
  while (!client.available() && clientTimeout <= MONSENS_ESP8266_TIMEOUT) {
    ++clientTimeout;
    delay(1);
  }
  if (clientTimeout > MONSENS_ESP8266_TIMEOUT) {
    Serial.println("client timeout");
    return;
  }

  // Read the first line of the request
  char request[4];
  client.readStringUntil('\r').toCharArray(request, 4);
  client.flush();
  Serial.print(request);

  // ask sensors for output and return it
  askSensors(request);
}


/**
 * Write output to the MCUs interface.
 */
void MonSens_ESP8266::write(const char output) {
  Serial.write(output);
  client.print(output);
}

