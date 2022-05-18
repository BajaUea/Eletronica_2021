#include <NMEAGPS.h>
#include <AltSoftSerial.h>
#include <NeoTee.h>
#include <NeoTeeStream.h>
#include <NMEAprint.h>
#include <GPSport.h>


AltSoftSerial HC12;     // RX pin 8, TX pin 9 on an UNO
#define GPS_PORT_NAME "AltSoftSerial"
#define DEBUG_PORT Serial
NMEAGPS gps;        // the NMEA parser
gps_fix fix;        // the parsed fields, all in one struct
size_t fixCount;      // the count of received bytes


// ----------- Global Declarations ----------- 
const char   startMarker[] = "FIX=";
size_t startCount    = 0;
enum receiverState_t { WAITING_FOR_FIX, RECEIVING_FIX };
receiverState_t receiverState = WAITING_FOR_FIX;
// ----------- Global Declarations ----------- \\

void setup() {

  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() {

  if (HC12.available()>0) {
  char c = HC12.read();
  
  switch (receiverState) {
    
    case WAITING_FOR_FIX:
      // Did we receive the next character of the start marker?
      if (startMarker[ startCount ] == c) {
        startCount++;

        // Yes, is this the whole start marker?
        if (startCount == sizeof(startMarker)-1) {

        // Yes, the next bytes are the binary fix structure
        receiverState = RECEIVING_FIX;
        fixCount      = 0;
        }

      } else {
        // The character didn't match, start over...
        startCount = 0;
      }
      break;
    
    case RECEIVING_FIX:
      // Save the next received byte into the local fix structure
      uint8_t *fixBytes = (uint8_t *) &fix;  // an "alias" for the fix structure's memory bytes
      fixBytes[ fixCount++ ] = c; // increments the counter, too

      if (fixCount >= sizeof(fix)) {
        // Complete fix received!  Print reconstructed NMEA sentences from the fix.
        NMEAprintRMC( &Serial, fix );
        NMEAprintGGA( &Serial, fix );

        // Restart the process
        receiverState = WAITING_FOR_FIX;
        startCount    = 0;
      }
      break;
  }
  }
}
