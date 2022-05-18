#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h> // Comunicação com MPU

#define pinVEL 2 // Pino de interrupção para rotação da roda
#define RAIO_RODA 0.266 // Em metros

float distancia1, distancia2;

////
// Endereco I2C do sensor MPU-6050
const int MPU1 = 0x68;
const int MPU2 = 0x69;

// Variaveis para armazenar valores dos MPU
float AccX1, AccY1, AccZ1, GyrX1, GyrY1, GyrZ1;
float AccX2, AccY2, AccZ2, GyrX2, GyrY2, GyrZ2;

unsigned long mpu_millisInicial = 0; // Tempo inicial para aceleração
unsigned long Velocidade_millisInicial = 0; // Tempo inicial para velocidade 
unsigned long tempo = 0; // tempo inicial para o gps
unsigned long ultra_millisInicial = 0; // tempo inicial para aceleração

volatile int pulsosVEL = 0; // Contador de pulsos para RPM 

unsigned int RPMvel = 0; // Frequencia de rotacoes da roda
unsigned int VEL = 0; // Velocidade em km/h

const int pinoSD = 8;

String a = "", b = "", c = "";


File dataFile;


void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  SD.begin(pinoSD);

  /////
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
  Wire.write(0b00001000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00001000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  ////

  attachInterrupt (digitalPinToInterrupt(pinVEL), velocimetro, RISING); // Interrupção para ler pulso da roda

}

void loop()
{
  acelerometro();
  velocidade();
  if((millis() - tempo) > 250){
    dataFile = SD.open("datalog.txt", FILE_WRITE);

    // escreve se o arquivo for valido
    if (dataFile) {
      
      dataFile.print(AccX1/8192);
      dataFile.print(",");
      dataFile.print(AccY1/8192);
      dataFile.print(",");
      dataFile.print(AccZ1/8192);
      dataFile.print(",");
      
      dataFile.print(GyrX1/131);
      dataFile.print(",");
      dataFile.print(GyrY1/131);
      dataFile.print(",");
      dataFile.print(GyrZ1/131);
      dataFile.print(",");
      
      dataFile.print(AccX2/8192);
      dataFile.print(",");
      dataFile.print(AccY2/8192);
      dataFile.print(",");
      dataFile.print(AccZ2/8192);
      dataFile.print(",");
      
      dataFile.print(GyrX2/131);
      dataFile.print(",");
      dataFile.print(GyrY2/131);
      dataFile.print(",");
      dataFile.print(GyrZ2/131);

      dataFile.print(",");
      dataFile.print(VEL);

      dataFile.print(",");
      dataFile.print(distancia1);

      dataFile.print(",");
      dataFile.println(distancia2);
      
      dataFile.close();
      
      Serial.print(AccX1);
      Serial.print(",");
      Serial.print(AccY1);
      Serial.print(",");
      Serial.print(AccZ1);
      Serial.print(",");
      
      Serial.print(GyrX1);
      Serial.print(",");
      Serial.print(GyrY1);
      Serial.print(",");
      Serial.print(GyrZ1);
      Serial.print(",");
      
      Serial.print(AccX1);
      Serial.print(",");
      Serial.print(AccY1);
      Serial.print(",");
      Serial.print(AccZ1);
      Serial.print(",");
      
      Serial.print(GyrX1);
      Serial.print(",");
      Serial.print(GyrY1);
      Serial.print(",");
      Serial.print(GyrZ1);

      Serial.print(",");
      Serial.print(VEL);

      Serial.print(",");
      Serial.print(distancia1);

      Serial.print(",");
      Serial.println(distancia2);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
    
    tempo = millis();
  }
  
}
