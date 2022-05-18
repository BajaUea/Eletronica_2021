#include <Wire.h> //comunicação com MPU
#include <Adafruit_MLX90614.h> //Sensor de temperatura
#include <TinyGPS++.h>//include the library code
#include <SoftwareSerial.h>//include the library code
#include <LiquidCrystal_I2C.h>;

// Endereco I2C do sensor MPU-6050
const int MPU1 = 0x68;
const int MPU2 = 0x69;

#define pinRPM 2

TinyGPSPlus gps;// The TinyGPS++ object
SoftwareSerial ss(4, 5);// The serial connection to the GPS device

// Define o endereço utilizado pelo Adaptador I2C
LiquidCrystal_I2C lcd(0x27,20,4);

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 

// Variaveis para armazenar valores do sensor
float AccX1, AccY1, AccZ1, Temp1, GyrX1, GyrY1, GyrZ1;
float AccX2, AccY2, AccZ2, Temp2, GyrX2, GyrY2, GyrZ2;

double temp_amb; 
double temp_obj; 

unsigned long int mpu_millisInicial = 0; // tempo inicial para aceleração
unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 
unsigned long Temp_millisInicial = 0; //tempo inicial para temperatura 
unsigned long Tanq_millisInicial = 0;

volatile int pulsosRPM = 0; //contador de pulsos para RPM 

unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h



void setup() {
  // Inicializa Serial
  Serial.begin(9600);

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
  Wire.write(0x00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1B);
  Wire.write(0x00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
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
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  attachInterrupt (digitalPinToInterrupt(pinRPM), tacometro, RISING); //Interrupção para ler pulso do RPM

  mlx.begin(); //inicializa o sensor de temperatura

  ss.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {  // tempo controlado -> sem problemas

  acelerometro();
  delay(1);
  velocidade_RPM();
  temperatura();
  gpsi();
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print(AccX1*9.8 / 2048);
  lcd.setCursor(6, 0);
  lcd.print(AccY1*9.8 / 2048);
  lcd.setCursor(12, 0);
  lcd.print(AccZ1*9.8 / 2048);
  lcd.setCursor(0, 1);
  lcd.print(VEL);
  lcd.setCursor(2, 1);
  lcd.print("Km/h");
  lcd.setCursor(10, 1);
  lcd.print(temp_obj);
  delay(10);

}
