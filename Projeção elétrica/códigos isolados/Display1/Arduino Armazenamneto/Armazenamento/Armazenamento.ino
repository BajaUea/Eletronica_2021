#include <Wire.h> // Comunicação com MPU
#include <SoftwareSerial.h> // Comunicação com a serial
#include <SPI.h> // Comunicação com o cartão SD
#include <SD.h> // Biblioteca do cartão SD
#include <TinyGPS++.h> //GPS

#define pinVEL 2 // Pino de interrupção para rotação da roda
#define RAIO_RODA 0.2667 // Em metros

// Endereco I2C do sensor MPU-6050
const int MPU1 = 0x68;
const int MPU2 = 0x69;

// Choose two Arduino pins to use for software serial
int RXPin = 4;
int TXPin = 3;

int GPSBaud = 9600;

const int pinoSD = 8; // Pino CS do cartão SD

String latitude = "";
String longitude = "";

// Variaveis para armazenar valores dos MPU
float AccX1, AccY1, AccZ1, GyrX1, GyrY1, GyrZ1;
float AccX2, AccY2, AccZ2, GyrX2, GyrY2, GyrZ2;


unsigned long mpu_millisInicial = 0; // Tempo inicial para aceleração
unsigned long Velocidade_millisInicial = 0; // Tempo inicial para velocidade  
unsigned long sd_millisInicial = 0; // Tempo inicial para o cartão SD
unsigned long gps_millisInicial = 0; // tempo inicial para o gps

volatile int pulsosVEL = 0; // Contador de pulsos para RPM 

unsigned int RPMvel = 0; // Frequencia de rotacoes da roda
unsigned int VEL = 0; // Velocidade em km/h

File dataFile;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  // Inicializa Serial
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

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

  attachInterrupt (digitalPinToInterrupt(pinVEL), tacometro, RISING); // Interrupção para ler pulso da roda

  SD.begin(pinoSD);
  
}

void loop() {
  acelerometro();
  velocidade();
  gpsi();
  cartao();
}
