/*
 *SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 *SPDX-License-Identifier: MIT
 */

#include "MultipleSatellite.h"

static const int RXPin = 22, TXPin = 21;

//Be suitable for Unit GPS v1.1  https://docs.m5stack.com/en/unit/Unit-GPS%20v1.1
//Be suitable for Unit GPS SMA   https://docs.m5stack.com/en/unit/Unit-GPS%20SMA
static const uint32_t GPSBaud = 115200;

//Be suitable for Unit GPS  https://docs.m5stack.com/en/unit/gps
//static const uint32_t GPSBaud = 9600;

// Create an instance of MultipleSatellite, assuming we use the Serial1 serial port
MultipleSatellite gps(Serial1, GPSBaud, SERIAL_8N1, RXPin, TXPin);

void displayInfo();

void setup()
{
    Serial.begin(115200);
    gps.begin();
    gps.setSystemBootMode(BOOT_FACTORY_START);
    Serial.println(F("DeviceExample.ino"));
    Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
    Serial.print(F("Testing TinyGPSPlus library v. "));
    Serial.println(TinyGPSPlus::libraryVersion());
    Serial.println(F("by Mikal Hart"));
    Serial.println();
    String version = gps.getGNSSVersion();
    Serial.printf("GNSS SW=%s\r\n", version.c_str());
    delay(1000);
    // Set satellite mode
    gps.setSatelliteMode(SATELLITE_MODE_GPS);
}
void loop()
{
    // Update data
    gps.updateGPS();
    displayInfo();
    delay(10);
}

void displayInfo()
{
    Serial.print(F("Location: "));
    Serial.printf("satellites:%d\n", gps.satellites.value());
    if (gps.location.isUpdated()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        Serial.print(F("\n"));

    } else {
        Serial.print(F("INVALID\n"));
    }

    Serial.print(F("  Date/Time: "));
    if (gps.date.isUpdated()) {
        Serial.print(gps.date.month());
        Serial.print(F("/"));
        Serial.print(gps.date.day());
        Serial.print(F("/"));
        Serial.print(gps.date.year());
    } else {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" "));
    if (gps.time.isUpdated()) {
        if (gps.time.hour() < 10) Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        if (gps.time.second() < 10) Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(F("."));
        if (gps.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(gps.time.centisecond());
    } else {
        Serial.print(F("INVALID"));
    }

    Serial.println();
    delay(1000);
}
