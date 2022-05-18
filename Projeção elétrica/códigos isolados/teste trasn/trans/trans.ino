#include <NMEAGPS.h>
#include <AltSoftSerial.h>
#include <NeoHWSerial.h>
#include <GPSport.h>

#define gpsPort NeoSerial  // Hook GPS TX to pin 0, GPS RX to pin 1
#define GPS_PORT_NAME "NeoSerial"
#define DEBUG_PORT NeoSerial


AltSoftSerial HC12; // RX pin 8, TX pin 9 on an UNO
NMEAGPS gps; // the NMEA parser
gps_fix fix; // the parsed fields, all in one struct
char HC12buffer[ 80 ];
const size_t HC12_MAX = sizeof(HC12buffer);
size_t HC12count = 0;
volatile uint32_t newlines = 0UL;


static void handleRxChar( uint8_t c )
{
  if (c == '\n')
    newlines++;
}


// Parse GPS characters in the background (even during delay)
static void GPSisr( uint8_t c )
{
  gps.handle( c );

} // GPSisr


void setup() {
  
  //pinMode(setPin, OUTPUT);                // Output High for Transparent / Low for Command
  //digitalWrite(setPin, HIGH);            // Enter Transparent mode
  //delay(80);                               // 80 ms delay before operation per datasheet
  HC12.begin(9600);
  NeoSerial.attachInterrupt( handleRxChar );
  NeoSerial.begin(9600);
  //DEBUG_PORT.begin(9600);
  gpsPort.attachInterrupt( GPSisr );
  gpsPort.begin(9600);
}

void loop() {

  while (gps.available()) {
    fix = gps.read();  

    HC12.print( F("FIX=") );             // A "start marker" that the receiver can watch for...
    HC12.write( (uint8_t *) &fix, sizeof(fix) );     // Transmit binary structure to remote
  }
  
}
