#include "U8glib.h"
//Configuração de Pinagem, Enable, RW, RS, RESET
U8GLIB_ST7920_128X64_1X Display(8, 7, 6 , 9);
// Rotina de Configuração da Escrita no Display
void Display_config() {
  Display.setFont(u8g_font_6x10);
  Display.setFontRefHeightExtendedText();
  Display.setDefaultForegroundColor();
  Display.setFontPosTop();
}
void Tela1() {
  Display.setFont(u8g_font_unifont);
  Display.drawStr(45, 15, "Vida");
  Display.drawStr(53, 40, "de");
  Display.drawStr(35, 60, "Silicio");
}
void Tela2() {
  Display.setFont(u8g_font_unifont);
  Display.drawBox(0, 0, 128, 64);
  Display.setColorIndex(0);
  Display.drawStr(4, 35, "Vida de Silicio");
  Display.drawStr(5, 35, "Vida de Silicio");
  Display.drawFrame(1, 1, 126, 62);
}
void Tela3() {
  Display.setFont(u8g_font_helvB08);
  Display.drawStr(45, 31, "Arduino");
  Display.drawStr90(105, 15, "Display");
  Display.drawStr270(20, 55, "Eletronica");
}
void Tela4() {
  Display.setFont(u8g_font_robot_de_niro);
  Display.drawStr(0, 13, "Vida de Silicio");
  Display.setFont(u8g_font_helvB08);
  Display.drawStr(0, 25, "Display Grafico");
  Display.setFont(u8g_font_8x13);
  Display.drawBox(0, 31, 96, 13);
  Display.setColorIndex(0);
  Display.drawStr(0, 41, "Arduino Mega");
  Display.setFont(u8g_font_ncenB10);
  Display.setColorIndex(1);
  Display.drawStr(0, 60, "0123456789");
}
void Tela5() {
  char ASCII[2] = " ";
  int dec = 32;
  Display.setFont(u8g_font_robot_de_niro);
  for (int linha = 10; linha < 70; linha += 10) {
    for (int coluna = 2; coluna < 128; coluna += 8) {
      ASCII[0] = dec;
      Display.drawStr(coluna, linha, ASCII);
      dec ++;
    }
  }
  
}
void Tela6() {
  Display.setFont(u8g_font_8x13);
  Display.drawLine(10, 2, 110, 2);
  Display.drawBox(20, 10, 15, 15);
  Display.drawCircle(85, 20, 15);
  Display.drawEllipse(30, 50, 10, 10);
  Display.drawDisc(90, 50, 10);
}
void setup() {
  Serial.begin(9600);
  if ( Display.getMode() == U8G_MODE_R3G3B2 )
    Display.setColorIndex(20);
  else if ( Display.getMode() == U8G_MODE_GRAY2BIT )
    Display.setColorIndex(1);
  else if ( Display.getMode() == U8G_MODE_BW )
    Display.setColorIndex(1);
}
void loop() {
  //Tela 1
  Display.firstPage();
  do {
    Display_config();
    Tela1();
  }
  while (Display.nextPage());
  delay(1000);
  //Tela 2
  Display.firstPage();
  do {
    Display_config();
    Tela2();
  }
  while (Display.nextPage());
  delay(1000);
  //Tela 3
  Display.firstPage();
  do {
    Display_config();
    Tela3();
  }
  while (Display.nextPage());
  delay(1000);
  //Tela 4
  Display.firstPage();
  do {
    Display_config();
    Tela4();
  }
  while (Display.nextPage());
  delay(1000);
  //Tela 5
  Display.firstPage();
  do {
    Display_config();
    Tela5();
  }
  while (Display.nextPage());
  delay(1000);
  //Tela 6
  Display.firstPage();
  do {
    Display_config();
    Tela6();
  }
  while (Display.nextPage());
  delay(1000);
}
