#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define pinRPM 2

const int pinoSD = 4;

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 

volatile int pulsosRPM = 0; //contador de pulsos para RPM 

float RPM = 0; //frequencia de rotacoes em RPM
float VEL = 0; //velocidade em km/h

void setup() {
  // Inicializa Serial
  Serial.begin(9600);
  attachInterrupt (digitalPinToInterrupt(pinRPM), tacometro, RISING); //Interrupção para ler pulso do RPM
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(pinoSD)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  String dataString = "";
  
  if((millis() - Velocidade_millisInicial) > 1000){
    
    noInterrupts();
    RPM = (pulsosRPM/3 /*numero de pulsos na roda*/)*60;
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

  dataString += String(VEL);
  dataString += ",";
  dataString += String(RPM);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // escreve no arquivo se ele arquivo for valido
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

}

void tacometro () 
{
  pulsosRPM++;
}
