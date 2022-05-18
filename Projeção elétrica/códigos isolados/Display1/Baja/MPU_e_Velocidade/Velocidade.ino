void velocidade()
{
    unsigned long int deltaT = millis() - Velocidade_millisInicial;
    if((deltaT) > 250){
      noInterrupts();
      RPM = (pulsosRPM*(deltaT)/1000);
      VEL = (RPM*2*3.14*RAIO_RODA*3.6)/60;
      Serial.print ("RPM = ");
      Serial.print (RPM);
      Serial.print ("  VEL = ");
      Serial.println (VEL);
      pulsosRPM = 0;
      Serial.println("===================================");
      Velocidade_millisInicial = millis();
      interrupts();
  }
}

void tacometro () 
{
  pulsosRPM++;
}
