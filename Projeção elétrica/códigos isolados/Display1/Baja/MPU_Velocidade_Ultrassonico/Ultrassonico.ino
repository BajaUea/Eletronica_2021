void velocidade()
{
    if((millis() - Velocidade_millisInicial) > 250){
    
    distancia1 = distanceSensor.measureDistanceCm();
    distancia2 = distanceSensor2.measureDistanceCm();
    Serial.println("===================================");
    Serial.print(distancia1);
    Serial.println(" ");
    Serial.println(distancia2);
    Serial.println("===================================");
  }
}
