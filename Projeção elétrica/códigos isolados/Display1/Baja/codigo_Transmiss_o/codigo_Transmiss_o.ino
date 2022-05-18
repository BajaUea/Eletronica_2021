/*
   Project: NEO-6M GY-GPS6MV2 GPS module
   Function:This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   
The module GND pin is connected to Arduino GND pin
The module RX pin is connected to Arduino pin 3
The module TX pin is connected to Arduino pin 4
The module VCC pin is connected to Arduino 5V pin
*/
//*************************************************************
#include <TinyGPS++.h>//include the library code
#include <SoftwareSerial.h>//include the library code
//*******************************************************
TinyGPSPlus gps;// The TinyGPS++ object
SoftwareSerial ss(4, 3);// The serial connection to the GPS device
void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  Serial.println();
  Serial.println(F("Sats HDOP Latitude   Longitude   Fix  Date        Time   Date   Alt    Course Speed"));
  Serial.println(F("---------------------------------------------------------------------------------------------------------------------------------------"));
}

void loop() {

  gps1();
}
