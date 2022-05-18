#include<Wire.h>//Biblioteca para comunicação I2C

const int MPU1 = 0x68; // Endereço do sensor 1
const int MPU2 = 0x69; // Endereço do sensor 2

float AcX1,AcY1,AcZ1,Tmp1; //Variaveis para pegar os valores medidos
float AcX2,AcY2,AcZ2,Tmp2; //Variaveis para pegar os valores medidos

void setup(){
  Wire.begin(); // Inicia a comunicação I2C
  Wire.beginTransmission(MPU1); //Começa a transmissao de dados para o sensor 1
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 1
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU2); //Começa a transmissao de dados para o sensor 2
  Wire.write(0x6B); // registrador PWR_MGMT_1
  Wire.write(0); // Manda 0 e "acorda" o sensor 2
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
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();

  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00011000);  // Trocar esse comando para fundo de escala desejado conforme acima
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
  Wire.endTransmission(true); // Se der erro tente tirar esta linha

  // Agora escreve os valores no monitor serial
  // Sensor 1
  Serial.print("AcX1 = "); Serial.print((AcX1 / 2048)*9.8);
  Serial.print(" | AcY1 = "); Serial.print((AcY1 / 2048)*9.8);
  Serial.print(" | AcZ1 = "); Serial.print((AcZ1 / 2048)*9.8);
  Serial.print(" | Tmp1 = "); Serial.print(Tmp1/340.00+36.53); // Equação da temperatura em Cº de acordo com o datasheet
  Serial.print("\n==============================================\n");

  // Sensor 2
  Serial.print("AcX2 = "); Serial.print((AcX2 / 2048)*9.8);
  Serial.print(" | AcY2 = "); Serial.print((AcY2 / 2048)*9.8);
  Serial.print(" | AcZ2 = "); Serial.print((AcZ2 / 2048)*9.8);
  Serial.print(" | Tmp2 = "); Serial.print(Tmp2/340.00+36.53); // Equação da temperatura em Cº de acordo com o datasheet
  Serial.print("\n===============================================\n");


  delay(1000);
}
