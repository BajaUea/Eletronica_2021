#include "U8glib.h"
#include<Wire.h>
#include <util/atomic.h>

const int MPU1 = 0x68;
const int MPU2 = 0x69;

U8GLIB_ST7920_128X64_1X Display(8, 7, 6 , 9);

char vel[10];

float AccX1, AccY1, AccZ1, Temp1, GyrX1, GyrY1, GyrZ1, a;
float AccX2, AccY2, AccZ2, Temp2, GyrX2, GyrY2, GyrZ2;

char aAccX1[10], aAccY1[10], aAccZ1[10], aTemp1[10], aGyrX1[10], aGyrY1[10], aGyrZ1[10], a2[10];
char aAccX2[10], aAccY2[10], aAccZ2[10], aTemp2[10], aGyrX2[10], aGyrY2[10], aGyrZ2[10];

#define pinVEL 3

unsigned long millisInicial = 0; //tempo inicial 

volatile int pulsosVEL = 0; //contador de pulsos para velocidade

unsigned int VEL = 0; //velocidade em km/h

void setup() {
  Serial.begin(9600);
  Display.begin();
  Display.setColorIndex(1);
  Display.setFont(u8g_font_unifont);
  attachInterrupt (digitalPinToInterrupt(pinVEL), veloc, RISING); //Interrupção para ler pulso da velocidade

  //CONFIGURAÇÕES DO ACELEROMETRO

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
  /*
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
  /*
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
}


void loop() {
  Display.firstPage();
  do {
    draw();

  }while (Display.nextPage());

}
void draw(){
  
  velocidade();
  acelerometro();
  
  Display.drawFrame(0, 0, 128, 31);
  Display.drawFrame(0, 33, 128, 31);

  Display.drawStr(15, 13, "Velocidade");
  Display.drawStr(35, 28, vel);
  Display.drawStr(76, 28, " Km/h");

  Display.drawStr(15, 46, "Aceleracao");
  delay(400);
  Display.drawStr(35, 61, a2);
  Display.drawStr(76, 61, " m/s*s");
}

void velocidade() 
{
  if((millis() - millisInicial) > 100)
  {
    noInterrupts();
    VEL = (pulsosVEL*2*3.14*0.5*3.6)/2;
    Serial.print ("  VEL = ");
    Serial.println (VEL);
    dtostrf(VEL, 3, 1, vel);
    pulsosVEL = 0;
    millisInicial = millis();
    interrupts();
  }

}


void veloc () 
{
  pulsosVEL++;
}

//void b(){
//  float v2 = 100;
//  dtostrf(v2, 3, 1, d);
//}

void acelerometro() {
  // Comandos para iniciar transmissão de dados
  // MPU 1
  noInterrupts();
  Wire.beginTransmission(MPU1);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU1, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccX1 = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY1 = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ1 = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp1 = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyrX1 = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyrY1 = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyrZ1 = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Wire.endTransmission(true);

  // MPU 2
  Wire.beginTransmission(MPU2);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU2, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccX2 = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY2 = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ2 = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp2 = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyrX2 = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyrY2 = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyrZ2 = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Wire.endTransmission(true);
  interrupts();


  // Imprime na Serial os valores obtidos
  /* Alterar divisão conforme fundo de escala escolhido:
      Acelerômetro
      +/-2g = 16384
      +/-4g = 8192
      +/-8g = 4096
      +/-16g = 2048

      Giroscópio
      +/-250°/s = 131
      +/-500°/s = 65.6
      +/-1000°/s = 32.8
      +/-2000°/s = 16.4
  */

  Serial.print(AccX1*9.8 / 2048);
  Serial.print(" ");
  Serial.print(AccY1*9.8 / 2048);
  Serial.print(" ");
  Serial.println(AccZ1*9.8 / 2048);

  Serial.print(AccX2*9.8 / 2048);
  Serial.print(" ");
  Serial.print(AccY2*9.8 / 2048);
  Serial.print(" ");
  Serial.println(AccZ2*9.8 / 2048);

  a = (AccZ1*9.8)/(2048);
  dtostrf(a, 3, 1, a2);

  dtostrf(AccX1, 3, 1, aAccX1);
  dtostrf(AccY1, 3, 1, aAccY1);
  dtostrf(AccZ1, 3, 1, aAccZ1);
  
  dtostrf(AccX2, 3, 1, aAccX2);
  dtostrf(AccY2, 3, 1, aAccY2);
  dtostrf(AccZ2, 3, 1, aAccZ2);

  //Serial.print(GyrX / 16.4);
 // Serial.print(" ");
  //Serial.print(GyrY / 16.4);
  //Serial.print(" ");
 // Serial.println(GyrZ / 16.4);

  // Atraso de 100ms
  delay(100);
}
