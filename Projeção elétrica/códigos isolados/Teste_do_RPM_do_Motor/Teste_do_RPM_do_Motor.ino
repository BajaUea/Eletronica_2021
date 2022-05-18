#include <SoftwareSerial.h>

#define pinRPM 3

volatile int pulsosRPM = 0; // Contador de pulsos para RPM

unsigned long int tacometro_millisInicial = 0; // tempo inicial para tacometro


float RPM = 0; // Frequencia de rotação do motor

void setup() {
  Serial.begin(9600);

}

void loop(){
   attachInterrupt(digitalPinToInterrupt(pinRPM), tacometro, RISING); //Interrupção para ler pulso do RPM
    
    if((millis() - tacometro_millisInicial) > 1000){
        noInterrupts();
    
        // Calculo RPM

        RPM = (pulsosRPM/2)*60; // Calculo do RPM
        pulsosRPM = 0;
        Serial.println(RPM);
        
        tacometro_millisInicial = millis();
        
        interrupts();
    }
}

void tacometro (){
    pulsosRPM++;
}
