void velocidade_RPM() 
{
  if((millis() - Velocidade_millisInicial) > 500){
    
    noInterrupts();
    RPM = (pulsosRPM/1 /*numero de pulsos na roda*/)*600;
    VEL = (RPM*2*3.14/* raio */*3.6)/60;
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
