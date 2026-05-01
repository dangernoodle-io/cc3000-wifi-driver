// Test-local copy of the STREAM_TO_UINT16_f / STREAM_TO_UINT32_f algorithms
// from src/utility/cc3000_common.cpp.
//
// We can't compile cc3000_common.cpp directly off-target because it transitively
// pulls in debug.h -> Arduino.h. The functions themselves are pure data
// manipulation — vendored from TI's CC3000 host driver and stable since 2014.
// Tests in test_stream_decode.c link against these copies; if the originals
// in src/ ever change, the test will catch the divergence on visual review.

#include "data_types.h"

UINT16 STREAM_TO_UINT16_f(CHAR* cp, UINT16 offset)
{
    UINT8 *p = (UINT8 *)cp;
    return (UINT16)((UINT16)((UINT16)
            (*(p + offset + 1)) << 8) + (UINT16)(*(p + offset)));
}

UINT32 STREAM_TO_UINT32_f(CHAR* cp, UINT16 offset)
{
    UINT8 *p = (UINT8 *)cp;
    return (UINT32)((UINT32)((UINT32)
        (*(p + offset + 3)) << 24) + (UINT32)((UINT32)
        (*(p + offset + 2)) << 16) + (UINT32)((UINT32)
        (*(p + offset + 1)) << 8) + (UINT32)(*(p + offset)));
}
