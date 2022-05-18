#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(2400);               // Serial port to HC12

}

void loop() {
  while (Serial.available()) {  // If HC-12 has data
    HC12.write(Serial.read());      // Send the data to Serial monitor
  }
}
