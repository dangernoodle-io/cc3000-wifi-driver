#include "unity.h"
#include <string.h>
#include "pgmspace_compat.h"

// Test that on non-AVR host, PROGMEM is a no-op
void test_progmem_is_noop_on_host(void) {
    // PROGMEM should expand to nothing on non-AVR; this just verifies it compiles
    int PROGMEM test_var = 42;
    TEST_ASSERT_EQUAL(42, test_var);
}

// Test that pgm_read_byte reads from RAM directly on host
void test_pgm_read_byte_reads_ram(void) {
    const uint8_t data[4] = {0x12, 0x34, 0x56, 0x78};
    uint8_t val = pgm_read_byte(&data[1]);
    TEST_ASSERT_EQUAL(0x34, val);
}

// Test that pgm_read_word reads from RAM directly on host
void test_pgm_read_word_reads_ram(void) {
    const uint16_t data[2] = {0x1234, 0x5678};
    uint16_t val = pgm_read_word(&data[0]);
    TEST_ASSERT_EQUAL(0x1234, val);
}

// Test that memcpy_P is memcpy on host
void test_memcpy_P_is_memcpy_on_host(void) {
    const uint8_t src[4] = {1, 2, 3, 4};
    uint8_t dst[4] = {0, 0, 0, 0};
    memcpy_P(dst, src, 4);
    TEST_ASSERT_EQUAL(1, dst[0]);
    TEST_ASSERT_EQUAL(2, dst[1]);
    TEST_ASSERT_EQUAL(3, dst[2]);
    TEST_ASSERT_EQUAL(4, dst[3]);
}

// Test that strcpy_P is strcpy on host
void test_strcpy_P_is_strcpy_on_host(void) {
    const char src[] = "hello";
    char dst[10] = {0};
    strcpy_P(dst, src);
    TEST_ASSERT_EQUAL_STRING("hello", dst);
}

// Test that PSTR is identity on non-AVR host
void test_pstr_is_identity_on_host(void) {
    const char *str = PSTR("test string");
    TEST_ASSERT_EQUAL_STRING("test string", str);
}

// Test prog_char typedef exists
void test_prog_char_typedef_exists(void) {
    prog_char c = 'A';
    TEST_ASSERT_EQUAL('A', c);
}
