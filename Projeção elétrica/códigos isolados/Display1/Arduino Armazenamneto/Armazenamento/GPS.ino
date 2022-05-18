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
      //Serial.print("Latitude: ");
      //Serial.println(String(gps.location.lat(), 6));
      latitude = String(gps.location.lat(), 6);
    
      //Serial.print("Longitude: ");
      //Serial.println(String(gps.location.lng(), 6));
      longitude = String(gps.location.lng(), 6);
      //Serial.println("===================================");
    }
    else
    {
      Serial.println("Location: Not Available");
    }
  gps_millisInicial = millis();
  }
}
