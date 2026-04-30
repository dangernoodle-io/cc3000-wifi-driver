#pragma once

// Portability shim for Adafruit_CC3000 vendored source.
// On AVR, defers to <avr/pgmspace.h>. Elsewhere (Cortex-M, etc.) provides
// no-op fallbacks so the same code paths build unchanged.

#ifdef __AVR__
  #include <avr/pgmspace.h>
#else
  #ifndef PROGMEM
    #define PROGMEM
  #endif
  #ifndef PSTR
    #define PSTR(s) (s)
  #endif
  #ifndef pgm_read_byte
    #define pgm_read_byte(addr) (*(const uint8_t *)(addr))
  #endif
  #ifndef pgm_read_word
    #define pgm_read_word(addr) (*(const uint16_t *)(addr))
  #endif
  #ifndef memcpy_P
    #define memcpy_P(dst, src, n) memcpy((dst), (src), (n))
  #endif
  #ifndef strcpy_P
    #define strcpy_P(dst, src)    strcpy((dst), (src))
  #endif
  typedef char prog_char;
#endif
