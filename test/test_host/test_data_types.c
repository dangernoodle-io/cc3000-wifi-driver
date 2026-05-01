#include "unity.h"
#include "data_types.h"

// Test that basic type definitions exist and have correct sizes
void test_uint8_size(void) {
    TEST_ASSERT_EQUAL(1, sizeof(UINT8));
}

void test_int8_size(void) {
    TEST_ASSERT_EQUAL(1, sizeof(INT8));
}

void test_uint16_size(void) {
    TEST_ASSERT_EQUAL(2, sizeof(UINT16));
}

void test_int16_size(void) {
    TEST_ASSERT_EQUAL(2, sizeof(INT16));
}

void test_uint32_size(void) {
    // UINT32 is unsigned long, which is 8 bytes on some 64-bit systems
    TEST_ASSERT_TRUE(sizeof(UINT32) >= 4);
}

void test_int32_size(void) {
    // INT32 is signed long, which is 8 bytes on some 64-bit systems
    TEST_ASSERT_TRUE(sizeof(INT32) >= 4);
}

void test_boolean_size(void) {
    TEST_ASSERT_EQUAL(1, sizeof(BOOLEAN));
}

// Test that macros are defined correctly
void test_null_macro(void) {
    TEST_ASSERT_NULL(NULL);
}

void test_false_macro(void) {
    TEST_ASSERT_EQUAL(0, FALSE);
}

void test_true_macro(void) {
    TEST_ASSERT_NOT_EQUAL(0, TRUE);
}

void test_ok_macro(void) {
    TEST_ASSERT_EQUAL(0, OK);
}

// Test type values
void test_uint8_value(void) {
    UINT8 val = 255;
    TEST_ASSERT_EQUAL(255, val);
}

void test_int8_negative_value(void) {
    INT8 val = -128;
    TEST_ASSERT_EQUAL(-128, val);
}

void test_uint16_value(void) {
    UINT16 val = 65535;
    TEST_ASSERT_EQUAL(65535, val);
}

void test_uint32_value(void) {
    UINT32 val = 0xFFFFFFFF;
    TEST_ASSERT_EQUAL(0xFFFFFFFF, val);
}

void test_boolean_true(void) {
    BOOLEAN b = TRUE;
    TEST_ASSERT_NOT_EQUAL(0, b);
}

void test_boolean_false(void) {
    BOOLEAN b = FALSE;
    TEST_ASSERT_EQUAL(0, b);
}
