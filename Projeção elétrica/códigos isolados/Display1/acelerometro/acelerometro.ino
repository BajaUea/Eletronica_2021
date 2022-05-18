#include<Wire.h>//Biblioteca para comunicação I2C

const int MPU1 = 0x68; // Endereço do sensor 1
const int MPU2 = 0x69; // Endereço do sensor 2

int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1; //Variaveis para pegar os valores medidos
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2; //Variaveis para pegar os valores medidos

void setup(){

  //Primeiro MPU
  
  Wire.begin(); // Inicia a comunicação I2C
  Wire.beginTransmission(MPU1); //Começa a transmissao de dados para o sensor 1
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 1
  Wire.endTransmission(true);

// Configura Giroscópio para fundo de escala desejado
  /*
    Wire.write(0b00000000); // fundo de escala em +/-250°/s
    Wire.write(0b00001000); // fundo de escala em +/-500°/s
    Wire.write(0b00010000); // fundo de escala em +/-1000°/s
    Wire.write(0b00011000); // fundo de escala em +/-2000°/s
  */

  Wire.beginTransmission(MPU1); //Começa a transmissao de dados para o sensor 1
  Wire.write(0x1B); // registrador PWR_MGMT_1
  Wire.write(0x00011000);
  Wire.endTransmission(true);

  // Configura Acelerometro para fundo de escala desejado
  /*
      Wire.write(0b00000000); // fundo de escala em +/-2g
      Wire.write(0b00001000); // fundo de escala em +/-4g
      Wire.write(0b00010000); // fundo de escala em +/-8g
      Wire.write(0b00011000); // fundo de escala em +/-16g
  */

  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00011000);  
  Wire.endTransmission();

  //Segundo MPU

  Wire.beginTransmission(MPU2); //Começa a transmissao de dados para o sensor 2
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 2
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU2); //Começa a transmissao de dados para o sensor 1
  Wire.write(0x1B); // registrador PWR_MGMT_1
  Wire.write(0x00011000);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00011000);  
  Wire.endTransmission();

  Serial.begin(9600); //Inicia a comunicaçao serial (para exibir os valores lidos)
}
void loop(){
  // Sensor 1
  Wire.beginTransmission(MPU1); //Começa a transmissao de dados do sensor 1
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU1,14,true); // Faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcX1 = Wire.read()<<8|Wire.read();
  AcY1 = Wire.read()<<8|Wire.read();
  AcZ1 = Wire.read()<<8|Wire.read();
  Tmp1 = Wire.read()<<8|Wire.read();
  GyX1 = Wire.read()<<8|Wire.read();
  GyY1 = Wire.read()<<8|Wire.read();
  GyZ1 = Wire.read()<<8|Wire.read();
  Wire.endTransmission(true); // Se der erro tente tirar esta linha

  // Sensor 2
  Wire.beginTransmission(MPU2); // Começa a transmissao de dados do sensor 2
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU2,14,true); // Faz um "pedido" para ler 14 registradores, que serão os registrados com os dados medidos
  AcX2 = Wire.read()<<8|Wire.read();
  AcY2 = Wire.read()<<8|Wire.read();
  AcZ2 = Wire.read()<<8|Wire.read();
  Tmp2 = Wire.read()<<8|Wire.read();
  GyX2 = Wire.read()<<8|Wire.read();
  GyY2 = Wire.read()<<8|Wire.read();
  GyZ2 = Wire.read()<<8|Wire.read();
  Wire.endTransmission(true); // Se der erro tente tirar esta linha

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

  // Agora escreve os valores no monitor serial
  // Sensor 1
  Serial.print(AcX1 / 2048);
  Serial.print(" ");
  Serial.print(AcY1 / 2048);
  Serial.print(" ");
  Serial.println(AcZ1 / 2048);

  //Serial.print(GyX1 / 16.4);
  //Serial.print(" ");
  //Serial.print(GyY1 / 16.4);
  //Serial.print(" ");
  //Serial.println(GyZ1 / 16.4);

   // Sensor 2

  /*Serial.print(AccX / 2048);
  Serial.print(" ");
  Serial.print(AccY / 2048);
  Serial.print(" ");
  Serial.println(AccZ / 2048);

  Serial.print(GyrX / 16.4);
  Serial.print(" ");
  Serial.print(GyrY / 16.4);
  Serial.print(" ");
  Serial.println(GyrZ / 16.4);

  */

  delay(500);
}
