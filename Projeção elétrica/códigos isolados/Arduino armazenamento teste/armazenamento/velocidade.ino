void velocidade() 
{
  if((millis() - Velocidade_millisInicial) > 250){
    
    noInterrupts();
    RPMvel = (pulsosVEL*13.333 /*numero de pulsos na roda*/)*60*4; // 60*4/18
    VEL = (RPMvel*2*3.14*RAIO_RODA*3.6)/60; // Calculo da velocidade
    //Serial.print ("RPM = ");
    //Serial.print (RPMvel);
    //Serial.print ("  VEL = ");
    //Serial.println (VEL);
    pulsosVEL = 0;
    //Serial.println("===================================");
    Velocidade_millisInicial = millis();
    interrupts();
  }
}

void velocimetro () 
{
  pulsosVEL++; // Função chamada no pino de interrupção
}
