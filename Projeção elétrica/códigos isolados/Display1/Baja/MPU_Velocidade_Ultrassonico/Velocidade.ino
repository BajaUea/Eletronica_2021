void ultrassonico()
{
    if((millis() - Velocidade_millisInicial) > 250){
    
    noInterrupts();
    RPM = (pulsosRPM*13.333);//240/18
    VEL = (RPM*2*3.14*0.266*3.6)/60;
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
