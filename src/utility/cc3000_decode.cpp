// Pure-data byte-stream decoders. See cc3000_decode.h.
// Algorithms vendored verbatim from TI's CC3000 host driver via
// Adafruit_CC3000_Library; preserved to maintain bit-exact behavior.

#include "cc3000_decode.h"

UINT16 STREAM_TO_UINT16_f(CHAR* cp, UINT16 offset)
{
  // Adafruit CC3k Host Driver Difference
  // Explicit cast to UINT8 pointer is required or decoding parameters breaks on Arduino.
  // Noted 12-12-2014 by tdicola
  UINT8 *p = (UINT8 *)cp;
  /*
  DEBUGPRINT_F("Stream2u16: ");
  DEBUGPRINT_HEX(cp[offset+1]);
  DEBUGPRINT_F(" + ");
  DEBUGPRINT_HEX(cp[offset]);
  DEBUGPRINT_F("\n\r");
  */

  return (UINT16)((UINT16)((UINT16)
          (*(p + offset + 1)) << 8) + (UINT16)(*(p + offset)));
}

UINT32 STREAM_TO_UINT32_f(CHAR* cp, UINT16 offset)
{
  // Adafruit CC3k Host Driver Difference
  // Explicit cast to UINT8 pointer is required or decoding parameters breaks on Arduino.
  // Noted 12-12-2014 by tdicola
  UINT8 *p = (UINT8 *)cp;

  /*
  DEBUGPRINT_F("\tStream2u32: ");
  DEBUGPRINT_HEX(cp[offset+3]);  DEBUGPRINT_F(" + ");
  DEBUGPRINT_HEX(cp[offset+2]);  DEBUGPRINT_F(" + ");
  DEBUGPRINT_HEX(cp[offset+1]);  DEBUGPRINT_F(" + ");
  DEBUGPRINT_HEX(cp[offset]);
  DEBUGPRINT_F("\n\r");
  */

  return (UINT32)((UINT32)((UINT32)
    (*(p + offset + 3)) << 24) + (UINT32)((UINT32)
    (*(p + offset + 2)) << 16) + (UINT32)((UINT32)
    (*(p + offset + 1)) << 8) + (UINT32)(*(p + offset)));
}
