void velocidade()
{
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();
    RPM = (pulsosRPM/2 /*numero de pulsos da curva de onda do motor*/)*60; // Calculo do RPM do motor
    //RPMvel = (pulsosVEL*0.04625 /*numero de pulsos na roda = 18*/); // Calculo do RPM da roda
    VEL = (pulsosVEL*0.04625*2*3.14*RAIO_RODA*3.6); // Calculo da velocidade

    //Serial.print ("RPM motor = ");
    //Serial.print (RPM);
    
    //Serial.print ("  RPM = ");
    //Serial.print (RPMvel);
    //Serial.print ("  VEL = ");
    //Serial.println (VEL);
    pulsosVEL = 0;
    pulsosRPM = 0;
    //Serial.println("===================================");
    Velocidade_millisInicial = millis();
    
    interrupts();
  }
}

void tacometro() 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}

void RPMmotor() 
{
  pulsosRPM++; // Função chamada no pino de interrupção
}
