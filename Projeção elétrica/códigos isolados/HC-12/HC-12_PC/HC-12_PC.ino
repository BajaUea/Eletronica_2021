//Programa: Conexão HC-12 com PC
//Autor: Lukas Wendel

#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //RX, TX

String inputString = "";    //Variável para armazenamento dos dados da Serial

void setup() {
    Serial.begin(9600);     //Inicia comunicação serial do Arduino
    mySerial.begin(9600);   //Inicia comunicação serial do HC-12
}

void loop() {
    if(mySerial.available()){ //Verifica se há dados disponíveis na Serial do HC-12
        while(mySerial.available()){
            char inChar = (char)mySerial.read();
            inputString = mySerial.read();
            if(inChar == '0'){
                Serial.println(inputString);
                inputString = "";
            }
        }
    }
}
