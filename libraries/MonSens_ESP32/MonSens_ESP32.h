/*
 * Copyright © 2025 Simon Rupf
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
 * @brief MonSens implementation for the wireless ESP32 microcontroller board.
 *
 * The ESP32 offers a large amount of dynamic and persistent memory and plenty
 * of pins to connect multiple sensors on a single unit. There are multiple
 * revisions of it, but all of them should be usable for MonSens applications.
 */

#ifndef MONSENS_ESP32_H
#define MONSENS_ESP32_H

#include <MonSens.h>
#include <WiFi.h>
#include <WiFiManager.h>      // Local AP with configuration portal for credentials

// amount of ms to wait until client sends something, maximum 65535
#ifndef MONSENS_ESP32_TIMEOUT
#  define MONSENS_ESP32_TIMEOUT 5000
#endif

/**
 * MonSens implementation for the wireless ESP32.
 */
class MonSens_ESP32: public IMonSens_Communicator {
  public:
    /**
     * Constructor
     */
    MonSens_ESP32() {}

    /**
     * Set the SSID of the WiFi network.
     */
    void setSsid(const char* ssid);

    /**
     * Set the password of the WiFi network.
     */
    void setPassword(const char* password);

    /**
     * Set the port the server should listen on.
     */
    void setPort(const uint16_t port);

    /**
     * Initialize the communicator, to be called in the MCUs setup routine.
     */
    void init();

    /**
     * Read inputs and respond to them, to be called in the MCUs loop routine.
     */
    void communicate();

  protected:
    /**
     * SSID of the WiFi network.
     */
    const char* wifiSsid = "";

    /**
     * Password of the WiFi network.
     */
    const char* wifiPassword = "";

    /**
     * TCP port the server listens at.
     */
    uint16_t tcpPort;

    /**
     * Client connecting to the server.
     */
    WiFiClient client;

    /**
     * Server listening for TCP connections.
     */
    WiFiServer* server;

    /**
     * Write output to the MCUs interface.
     */
    void write(const char output);
};

#endif
