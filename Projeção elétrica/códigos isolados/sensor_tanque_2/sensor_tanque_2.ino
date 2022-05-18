/*
 * Programador Edmundo Alves
 * Projeto: BAJA_UEA 2021
 */
#define  pin_Sensor_2 7   //Define o pino de entrada do sinal do sensor
#define  LED 12        //Define led(pino 13) da placa do arduino 

bool status_Sensor_2   =  false ;  //variável que armazena o estado do sensor 

void setup(){
    Serial .begin (9600 ); //Inicialização da porta de comunicação Serial

    pinMode (pin_Sensor_2 , INPUT ); //Define o sensor como entrada de informações
    pinMode (LED, OUTPUT );      //Define o led como saída
}

void loop() {

  //Faz a leitura digital do estado do sensor
  //acionado - 0(0V)  desacionado - 1(+Vcc) 
    status_Sensor_2 = digitalRead   (pin_Sensor_2); 

  //se o valor da variável for 0(false) entra no if
    if (status_Sensor_2 == false ) {
        Serial .println ("RESERVA"  ); //exibe na serial a string dentro das aspas
        digitalWrite  (LED , LOW );  //apaga o led
  }

  
}
