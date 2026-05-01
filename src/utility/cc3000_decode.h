#pragma once

// Pure-data byte-stream decoders, extracted from cc3000_common.cpp so they can
// be compiled and tested off-target without dragging in Arduino, SPI, or POSIX
// headers. Vendored algorithms unchanged.

#include "data_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Decode a little-endian UINT16 from byte stream `cp` at byte offset.
UINT16 STREAM_TO_UINT16_f(CHAR* cp, UINT16 offset);

// Decode a little-endian UINT32 from byte stream `cp` at byte offset.
UINT32 STREAM_TO_UINT32_f(CHAR* cp, UINT16 offset);

#ifdef __cplusplus
}
#endif
