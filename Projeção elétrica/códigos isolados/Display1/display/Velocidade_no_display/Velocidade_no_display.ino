#include "U8glib.h"


U8GLIB_ST7920_128X64_1X Display(8, 7, 6 , 9);

char vel[10];

#define pinVEL 3

unsigned long millisInicial = 0; //tempo inicial 

volatile int pulsosVEL = 0; //contador de pulsos para velocidade

unsigned int VEL = 0; //velocidade em km/h

void setup() {
  Serial.begin(9600);
  Display.begin();
  Display.setColorIndex(1);
  Display.setFont(u8g_font_unifont);
  attachInterrupt (digitalPinToInterrupt(pinVEL), veloc, RISING); //Interrupção para ler pulso da velocidade

  
}


void loop() {
  Display.firstPage();
  do {
    draw();

  }while (Display.nextPage());

}
void draw(){
  
  velocidade();
  
  Display.drawFrame(0, 0, 128, 31);
  Display.drawFrame(0, 33, 128, 31);

  Display.drawStr(15, 13, "Velocidade");
  Display.drawStr(35, 28, vel);
  Display.drawStr(76, 28, " Km/h");

  Display.drawStr(15, 46, "Aceleracao");
  Display.drawStr(35, 61, vel);
  Display.drawStr(76, 61, " m/s*s");
}

void velocidade() 
{
  if((millis() - millisInicial) > 500)
  {
    noInterrupts();
    VEL = (pulsosVEL*2*3.14*0.5*3.6)/2;
    Serial.print ("  VEL = ");
    Serial.println (VEL);
    dtostrf(VEL, 3, 1, vel);
    pulsosVEL = 0;
    millisInicial = millis();
    interrupts();
  }

}


void veloc () 
{
  pulsosVEL++;
}

//void b(){
//  float v2 = 100;
//  dtostrf(v2, 3, 1, d);
//}
