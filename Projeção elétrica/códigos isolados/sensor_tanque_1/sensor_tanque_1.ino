/*
 * Programador Edmundo Alves
 * Projeto: BAJA_UEA 2021
 */
//Arduino e Sensor Capacitivo
#define pinSensor 8   //Define o pino de entrada do sinal do sensor
#define LED 13        //Define led(pino 13) da placa do arduino 

bool statusSensor = false;  //variável que armazena o estado do sensor 

void setup() {
    Serial.begin(9600); //Inicialização da porta de comunicação Serial

    pinMode(pinSensor, INPUT); //Define o sensor como entrada de informações
    pinMode(LED, OUTPUT);      //Define o led como saída
}

void loop() {

  //Faz a leitura digital do estado do sensor
  //acionado - 0(0V)  desacionado - 1(+Vcc) 
    statusSensor = digitalRead(pinSensor); 

  //se o valor da variável for 1(true) entra no if
    if (statusSensor == true) {
        Serial.println("tanque cheio");  //exibe na serial a string dentro das aspas
        digitalWrite(LED, HIGH); //acende o led
  }

  //se o valor da variável for 0(false) entra no else if
    if (statusSensor == false) {
        Serial.println("meio tanque"); //exibe na serial a string dentro das aspas
        digitalWrite(LED, LOW);  //apaga o led
  }

  
}
