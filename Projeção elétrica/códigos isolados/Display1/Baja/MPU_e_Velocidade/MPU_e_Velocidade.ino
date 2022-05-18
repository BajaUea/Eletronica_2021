#include <SoftwareSerial.h>
#include<Wire.h> //comunicação com MPU
#include <SPI.h>
#include <SD.h>

#define pinRPM 2
#define RAIO_RODA 0.2667 // em metros

const int pinoSD = 8;

unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 
unsigned long int mpu_millisInicial = 0; // tempo inicial para aceleração

const int MPU1 = 0x68;
const int MPU2 = 0x69;

volatile int pulsosRPM = 0; //contador de pulsos para RPM 

unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h

float AccX1, AccY1, AccZ1, Temp1, GyrX1, GyrY1, GyrZ1;
float AccX2, AccY2, AccZ2, Temp2, GyrX2, GyrY2, GyrZ2;

void setup() {
  // Inicializa Serial
  Serial.begin(9600);
  attachInterrupt (digitalPinToInterrupt(pinRPM), tacometro, RISING); //Interrupção para ler pulso do RPM

  // Inicializa o MPU1
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Inicializa o MPU2
  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Configura Giroscópio para fundo de escala desejado
  /*  Giros possiveis
    Wire.write(0b00000000); // fundo de escala em +/-250°/s
    Wire.write(0b00001000); // fundo de escala em +/-500°/s
    Wire.write(0b00010000); // fundo de escala em +/-1000°/s
    Wire.write(0b00011000); // fundo de escala em +/-2000°/s
  */
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);
  Wire.write(0b00000000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1B);
  Wire.write(0b00000000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  // Configura Acelerometro para fundo de escala desejado
  /*  Aceleracoes possiveis
      Wire.write(0b00000000); // fundo de escala em +/-2g
      Wire.write(0b00001000); // fundo de escala em +/-4g
      Wire.write(0b00010000); // fundo de escala em +/-8g
      Wire.write(0b00011000); // fundo de escala em +/-16g
  */
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00010000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00010000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();


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
  String StringVEL_RPM = "";
  String StringACE_MPU1 = "";
  String StringGIRO_MPU1 = "";
  String StringACE_MPU2 = "";
  String StringGIRO_MPU2 = "";
  velocidade();
  MPU();
  StringVEL_RPM += String(VEL);
  StringVEL_RPM += ",";
  StringVEL_RPM += String(RPM);
  StringVEL_RPM += ",";

  StringACE_MPU1 += String(AccX1*9.8/4096);
  StringACE_MPU1 += ",";
  StringACE_MPU1 += String(AccY1*9.8/4096);
  StringACE_MPU1 += ",";
  StringACE_MPU1 += String(AccZ1*9.8/4096);
  StringACE_MPU1 += ",";

  StringGIRO_MPU1 += String(GyrX1/131);
  StringGIRO_MPU1 += ",";
  StringGIRO_MPU1 += String(GyrY1/131);
  StringGIRO_MPU1 += ",";
  StringGIRO_MPU1 += String(GyrZ1/131);
  StringGIRO_MPU1 += ",";

  StringACE_MPU2 += String(AccX2*9.8/4096);
  StringACE_MPU2 += ",";
  StringACE_MPU2 += String(AccY2*9.8/4096);
  StringACE_MPU2 += ",";
  StringACE_MPU2 += String(AccZ2*9.8/4096);
  StringACE_MPU2 += ",";

  StringGIRO_MPU2 += String(GyrX2/131);
  StringGIRO_MPU2 += ",";
  StringGIRO_MPU2 += String(GyrY2/131);
  StringGIRO_MPU2 += ",";
  StringGIRO_MPU2 += String(GyrZ2/131);

  

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // escreve se o arquivo for valido
  if (dataFile) {
    dataFile.print(StringVEL_RPM);
    dataFile.print(StringACE_MPU1);
    dataFile.print(StringGIRO_MPU1);
    dataFile.print(StringACE_MPU2);
    dataFile.println(StringGIRO_MPU2);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
  
}
