void gpsi()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
}

void displayInfo()
{
  if((millis() - gps_millisInicial) > 1000){
    if (gps.location.isValid())
    {
      a = String(gps.location.lat(), 6);
      b = String(gps.location.lng(), 6);
      c = String(gps.altitude.meters());
    }
    else
    {
      Serial.println("Location: Not Available");
    }
  gps_millisInicial = millis();
  }
}
