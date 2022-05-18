//Programa: Scanner I2C
//Esse programa tem como objetivo mostrar o endereço dos dispositivos conectados no protocolo I2C
//Esse programa testa os endereços de 7 bits padrão

#include <Wire.h>

void setup(){
    
    Wire.begin();
    Serial.begin(9600);
    Serial.println("\nI2C Scanner");
    
}
void loop(){
    
    byte error, address;
    int nDevices;
    Serial.println("Scaneando...");
    nDevices = 0;
    for(address = 1; address < 127; address++ ){
        // O Scanner I2C usa o valor de retorno da
        // the Write.endTransmisstion para verificar se
        // se o endereço de um dispositivo foi reconhecido
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0){
        Serial.print("Dispositivo I2C encontrado no endereço 0x");
        if (address<16) 
            Serial.print("0");
            Serial.print(address,HEX);
            Serial.println("  !");
            nDevices++;
        }
        else if (error==4) {
            Serial.print("Erro desconheido no endereço 0x");
            if (address<16) 
                Serial.print("0");
                Serial.println(address,HEX);
        }    
    }
    if (nDevices == 0)
        Serial.println("Nenhum dispositivo I2C encontrado\n");
    else
        Serial.println("Feito\n");
    delay(5000);           // wait 5 seconds for next scan
    
}
