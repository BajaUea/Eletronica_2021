#include <SoftwareSerial.h>//include the library code
#define pinRPM 3

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade
volatile float pulsosRPM = 0;
float RPM = 0;

void setup() {

  Serial.begin(4800);

  attachInterrupt (digitalPinToInterrupt(pinRPM), RPMmotor, RISING); //Interrupção para ler pulso do RPM


}

void loop() {

  if((millis() - Velocidade_millisInicial) > 1000){
    noInterrupts();
    RPM = (pulsosRPM /*numero de pulsos da curva de onda do motor*/)*60; // Calculo do RPM do motor
    Serial.print ("RPM motor = ");
    Serial.println (RPM/2);
    Velocidade_millisInicial = millis();
    pulsosRPM = 0;
    interrupts();
  }
}

void RPMmotor() 
{
  pulsosRPM++; // Função chamada no pino de interrupção
}
