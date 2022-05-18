#include <SoftwareSerial.h>
#include <Adafruit_MLX90614.h> //Sensor de temperatura

SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); 

unsigned long Temp_millisInicial = 0; //tempo inicial para temperatura 
unsigned long Velocidade_millisInicial = 0; //tempo inicial para velocidade 
unsigned long int telemetria_millisInicial = 0; // tempo inicial para telemetria

volatile int pulsosRPM = 0; //contador de pulsos para RPM 

unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h

double temp_amb; 
double temp_obj; 

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  mlx.begin(); //inicializa o sensor de temperatura

}

void loop() {
 
  temperatura();
  velocidade_RPM();

  if((millis()-telemetria_millisInicial) > 1000){
    noInterrupts();
    String enviar = "";
    enviar += (String(temp_obj) + "," + String(temp_amb) + "," + String(RPM) + "," + String(VEL));
    HC12.println(enviar);
    telemetria_millisInicial = millis();
    interrupts();
  }
}
