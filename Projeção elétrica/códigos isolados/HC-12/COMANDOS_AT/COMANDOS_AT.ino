//Programa: Configurar Comandos AT
//Autor: IoTools
//Lembrando que é necessário deixar o  pino Set em nível baixo para ativar os comandos AT

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX, TX
String command = "";

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
    Serial.println("Digite os comandos AT: ");
}

void loop() {
    while(mySerial.available()){
        Serial.write(mySerial.read());
        command = "";
    }
    while(Serial.available()){
        mySerial.write(Serial.read());
        // mySerial.flush();
    }

}
