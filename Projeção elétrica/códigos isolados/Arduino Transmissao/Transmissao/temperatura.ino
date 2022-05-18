void temperatura() {

  if((millis()-Temp_millisInicial) > 1000){
    // Get the voltage reading from the LM35
    reading = analogRead(sensorPin);

    // Convert that reading into voltage
    voltage = reading*(5.0/1024.0);

    // Convert the voltage into the temperature in Celsius
    temperatureC = voltage*100;

    // Print the temperature in Celsius]
    
    //Serial.print("Temperatura: ");
    //Serial.println(temperatureC);
    //Serial.println("===================================");
    Temp_millisInicial = millis();
  }
}
