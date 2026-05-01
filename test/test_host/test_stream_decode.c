// Tests for STREAM_TO_UINT16_f / STREAM_TO_UINT32_f in src/utility/cc3000_common.cpp.
// These functions decode little-endian byte streams from CC3000 HCI responses
// into native integers — pure data manipulation, no hardware dependency.

#include "unity.h"
#include "data_types.h"
#include "cc3000_common.h"

void test_stream_to_uint16_zero(void) {
    CHAR buf[2] = { 0x00, 0x00 };
    TEST_ASSERT_EQUAL_UINT16(0x0000, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint16_low_byte_only(void) {
    CHAR buf[2] = { (CHAR)0x42, (CHAR)0x00 };
    TEST_ASSERT_EQUAL_UINT16(0x0042, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint16_high_byte_only(void) {
    CHAR buf[2] = { (CHAR)0x00, (CHAR)0x42 };
    TEST_ASSERT_EQUAL_UINT16(0x4200, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint16_little_endian_decode(void) {
    // Bytes 0x34, 0x12 should decode to 0x1234 (LE).
    CHAR buf[2] = { (CHAR)0x34, (CHAR)0x12 };
    TEST_ASSERT_EQUAL_UINT16(0x1234, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint16_max(void) {
    CHAR buf[2] = { (CHAR)0xFF, (CHAR)0xFF };
    TEST_ASSERT_EQUAL_UINT16(0xFFFF, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint16_with_offset(void) {
    // Decode at offset 2: bytes are { 0x78, 0x56 } -> 0x5678.
    CHAR buf[4] = { (CHAR)0xAA, (CHAR)0xBB, (CHAR)0x78, (CHAR)0x56 };
    TEST_ASSERT_EQUAL_UINT16(0x5678, STREAM_TO_UINT16_f(buf, 2));
}

void test_stream_to_uint16_high_bit_set(void) {
    // Catches a regression where the high byte was sign-extended.
    CHAR buf[2] = { (CHAR)0x00, (CHAR)0x80 };
    TEST_ASSERT_EQUAL_UINT16(0x8000, STREAM_TO_UINT16_f(buf, 0));
}

void test_stream_to_uint32_zero(void) {
    CHAR buf[4] = { 0x00, 0x00, 0x00, 0x00 };
    TEST_ASSERT_EQUAL_UINT32(0x00000000UL, STREAM_TO_UINT32_f(buf, 0));
}

void test_stream_to_uint32_little_endian_decode(void) {
    // Bytes 0x78, 0x56, 0x34, 0x12 -> 0x12345678.
    CHAR buf[4] = { (CHAR)0x78, (CHAR)0x56, (CHAR)0x34, (CHAR)0x12 };
    TEST_ASSERT_EQUAL_UINT32(0x12345678UL, STREAM_TO_UINT32_f(buf, 0));
}

void test_stream_to_uint32_max(void) {
    CHAR buf[4] = { (CHAR)0xFF, (CHAR)0xFF, (CHAR)0xFF, (CHAR)0xFF };
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFUL, STREAM_TO_UINT32_f(buf, 0));
}

void test_stream_to_uint32_with_offset(void) {
    CHAR buf[6] = { (CHAR)0xAA, (CHAR)0xBB,
                    (CHAR)0xEF, (CHAR)0xCD, (CHAR)0xAB, (CHAR)0x89 };
    TEST_ASSERT_EQUAL_UINT32(0x89ABCDEFUL, STREAM_TO_UINT32_f(buf, 2));
}

void test_stream_to_uint32_high_bit_set(void) {
    // Catches sign-extension issues on the top byte.
    CHAR buf[4] = { (CHAR)0x00, (CHAR)0x00, (CHAR)0x00, (CHAR)0x80 };
    TEST_ASSERT_EQUAL_UINT32(0x80000000UL, STREAM_TO_UINT32_f(buf, 0));
}

void test_stream_to_uint32_ip_decode(void) {
    // Realistic case: IP 172.16.1.120 stored as { 120, 1, 16, 172 } little-endian.
    CHAR buf[4] = { (CHAR)120, (CHAR)1, (CHAR)16, (CHAR)172 };
    UINT32 ip = STREAM_TO_UINT32_f(buf, 0);
    TEST_ASSERT_EQUAL_UINT32(0xAC100178UL, ip);
}
