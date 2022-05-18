//Programa: Configuração do HC-12 do carro
//Autor: Lukas Wendel

#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX, TX

int combustivel;    //Quantidade de combustível
int RPM;            //RPM do motor.
float velocidade;   //Velocidade do carro.
float temp_obj;     //Temperatura do motor.
float latitude;     //Coordenadas
float longitude;    //do
float altitude;     //GPS.
float AC_1;         //Acelerômetro 1 (aceleração).
float AC_2;         //Acelerômetro 2 (aceleração).
float AC_3;         //Acelerômetro 3 (desaceleração).

unsigned long tempo = 0; //variável para auxiliar na frequência de envio de dados

void setup() {
    mySerial.begin(9600);
}

void loop() {
    if((millis() - tempo ) > 100){
        mySerial.println("Valor do RPM: "); //'print' deve ser mudado pra 'write'?  Fica aí a questão
        mySerial.print(RPM);
        mySerial.println("01_Quantidade de combustível: ");
        mySerial.print(combustivel);
        mySerial.println("02_Velocidade do carro: ");
        mySerial.print(velocidade);
        mySerial.println("03_Temperatura do motor: ");
        mySerial.print(temp_obj);
        mySerial.println("04_Latitude: ");
        mySerial.print(latitude);
        mySerial.println("05_Longitude: ");
        mySerial.print(longitude);
        mySerial.println("06_Altitude: ");
        mySerial.print(altitude);
        mySerial.println("07_Acelerômetro 1: ");
        mySerial.print(AC_1);
        mySerial.println("08_Acelerômetro 1: ");
        mySerial.print(AC_1);
        mySerial.println("09_Acelerômetro 2: ");
        mySerial.print(AC_2);
        mySerial.println("00_Acelerômetro 3: ");
        mySerial.print(AC_3);

        tempo = millis();
    }
}
