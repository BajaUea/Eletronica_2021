void temperatura() {

  if((millis()-Temp_millisInicial) > 1000){
    // Get the voltage reading from the LM35

    // subtrai do total a ultima leitura
    totalC = totalC - readings[readIndex];

    //le o sensor e coloca dado no vetor
    reading = analogRead(sensorPin);

    // Convert that reading into voltage
    voltage = reading*(5.0/1024.0);

    // Convert the voltage into the temperature in Celsius
    temperatureC = voltage*100;

     //le o sensor e coloca dado no vetor
    readings[readIndex] = temperatureC;

    totalC = totalC + readings[readIndex];

    //avanca para nova posicao do arrayu
    readIndex = readIndex + 1;

    //se estivermos no final do array
     if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
    }

     // calculate the average:
    averageC = totalC / numReadings;
    

    // Print the temperature in Celsius]
    
    //Serial.print("Temperatura: ");
    //Serial.println(temperatureC);
    //Serial.println("===================================");
    Temp_millisInicial = millis();
  }
}
