
// Inclusão das Bibliotecas
#include<Wire.h>

// Endereco I2C do sensor MPU-6050
const int MPUa = 0x68;
const int MPUb = 0x69;

// Variaveis para armazenar valores do sensor
float AccXa, AccYa, AccZa;
float AccXb, AccYb, AccZb;

void setup() {
  // Inicializa Serial
  Serial.begin(9600);

  // Inicializa o MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPUa);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.begin();
  Wire.beginTransmission(MPUb);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Configura Acelerometro para fundo de escala desejado
  /*
      Wire.write(0b00000000); // fundo de escala em +/-2g
      Wire.write(0b00001000); // fundo de escala em +/-4g
      Wire.write(0b00010000); // fundo de escala em +/-8g
      Wire.write(0b00011000); // fundo de escala em +/-16g
  */
  Wire.beginTransmission(MPUa);
  Wire.write(0x1C);
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPUb);
  Wire.write(0x1C);
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();
}

void loop() {
  // Comandos para iniciar transmissão de dados
  Wire.beginTransmission(MPUa);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPUa, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccXa = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccYa = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZa = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Wire.beginTransmission(MPUb);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPUb, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccXb = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccYb = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZb = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)


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

  Serial.print(AccXa / 2048);
  Serial.print(" ");
  Serial.print(AccYa / 2048);
  Serial.print(" ");
  Serial.println(AccZa / 2048);

  Serial.print(AccXb / 2048);
  Serial.print(" ");
  Serial.print(AccYb / 2048);
  Serial.print(" ");
  Serial.println(AccZb / 2048);

/*
  Serial.print(GyrX / 16.4);
  Serial.print(" ");
  Serial.print(GyrY / 16.4);
  Serial.print(" ");
  Serial.println(GyrZ / 16.4);
*/
  // Atraso de 100ms
  delay(100);
}
