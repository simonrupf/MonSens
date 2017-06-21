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
 * @brief MonSens implementation for the wireless NodeMCU microcontroller board.
 *
 * The NodeMCU offers a large amount of dynamic and persistent memory and plenty
 * of pins to connect multiple sensors on a single unit. There are multiple
 * revisions of it, but all of them should be usable for MonSens applications.
 */

#include <MonSens_NodeMCU.h>

/**
 * Set the SSID of the WiFi network.
 */
void MonSens_NodeMCU::setSsid(const char* ssid) {
  wifiSsid = ssid;
}

/**
 * Set the password of the WiFi network.
 */
void MonSens_NodeMCU::setPassword(const char* password) {
  wifiPassword = password;
}

/**
 * Inject the port the server should listen on.
 */
void MonSens_NodeMCU::setPort(int port) {
  tcpPort = port;
}

/**
 * Initialize the communicator, to be called in the MCUs setup routine.
 */
void MonSens_NodeMCU::init() {
  // Connect to WiFi network
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(wifiSsid);
 
  WiFi.begin(wifiSsid, wifiPassword);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
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
 * Read input from the MCUs interface.
 */
const char* MonSens_NodeMCU::readln() {
  // Check if a client has connected
  client = server->available();
  if (!client) {
    // wait a bit for a client to connect
    delay(1);
    return "";
  }
 
  // Wait until the client sends some data, but not more then MONSENS_NODEMCU_TIMEOUT ms
  Serial.println("new client");
  uint16_t i = 0;
  while (!client.available() && i <= MONSENS_NODEMCU_TIMEOUT) {
    delay(1);
    ++i;
  }
  if (i > MONSENS_NODEMCU_TIMEOUT) {
    return "";
  }

  // Read the first line of the request
  char request[4];
  client.readStringUntil('\r').toCharArray(request, 4);
  Serial.println(request);
  client.flush();
  return request;
}

/**
 * Write output to the MCUs interface, inserting a line break at the end.
 */
void MonSens_NodeMCU::writeln(char* output) {
  Serial.println(output);
  client.println(output);
};

