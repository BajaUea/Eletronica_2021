#include "U8glib.h"
U8GLIB_ST7920_128X64_1X Display(8, 7, 6 , 9);

#define pinVEL 3
unsigned long millisInicial = 0; //tempo inicial 
volatile int pulsosVEL = 0; //contador de pulsos para velocidade
unsigned int VEL = 0; //velocidade em km/h


void Display_config() {
  Display.setFont(u8g_font_10x20);
  Display.setFontRefHeightExtendedText();
  Display.setDefaultForegroundColor();
  Display.setFontPosTop();
}

void setup() {
  Serial.begin(9600);
  attachInterrupt (digitalPinToInterrupt(pinVEL), veloc, RISING); //Interrupção para ler pulso da velocidade
}


void loop() {
  Display.firstPage();
  do {
    Display_config();
    Display.drawCircle(64, 64, 55);
    Display.drawCircle(64, 64, 45);
    Display.setPrintPos(55, 35);
    if((millis() - millisInicial) > 500)
    {
    noInterrupts();
    VEL = (pulsosVEL*2*3.14*0.5*3.6)/20;
    Serial.print ("  VEL = ");
    Serial.println (VEL);
    Display.print(VEL);
    delay(1000);
    pulsosVEL = 0;
    millisInicial = millis();
    interrupts();
    }

  }
  while (Display.nextPage());

}
void veloc () 
{
  pulsosVEL++;
}
