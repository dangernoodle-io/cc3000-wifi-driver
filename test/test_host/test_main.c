#include "unity.h"

// Forward declarations from test_pgmspace_compat.c
void test_progmem_is_noop_on_host(void);
void test_pgm_read_byte_reads_ram(void);
void test_pgm_read_word_reads_ram(void);
void test_memcpy_P_is_memcpy_on_host(void);
void test_strcpy_P_is_strcpy_on_host(void);
void test_pstr_is_identity_on_host(void);
void test_prog_char_typedef_exists(void);

// Forward declarations from test_stream_decode.c
void test_stream_to_uint16_zero(void);
void test_stream_to_uint16_low_byte_only(void);
void test_stream_to_uint16_high_byte_only(void);
void test_stream_to_uint16_little_endian_decode(void);
void test_stream_to_uint16_max(void);
void test_stream_to_uint16_with_offset(void);
void test_stream_to_uint16_high_bit_set(void);
void test_stream_to_uint32_zero(void);
void test_stream_to_uint32_little_endian_decode(void);
void test_stream_to_uint32_max(void);
void test_stream_to_uint32_with_offset(void);
void test_stream_to_uint32_high_bit_set(void);
void test_stream_to_uint32_ip_decode(void);

// Forward declarations from test_data_types.c
void test_uint8_size(void);
void test_int8_size(void);
void test_uint16_size(void);
void test_int16_size(void);
void test_uint32_size(void);
void test_int32_size(void);
void test_boolean_size(void);
void test_null_macro(void);
void test_false_macro(void);
void test_true_macro(void);
void test_ok_macro(void);
void test_uint8_value(void);
void test_int8_negative_value(void);
void test_uint16_value(void);
void test_uint32_value(void);
void test_boolean_true(void);
void test_boolean_false(void);

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // pgmspace_compat tests
    RUN_TEST(test_progmem_is_noop_on_host);
    RUN_TEST(test_pgm_read_byte_reads_ram);
    RUN_TEST(test_pgm_read_word_reads_ram);
    RUN_TEST(test_memcpy_P_is_memcpy_on_host);
    RUN_TEST(test_strcpy_P_is_strcpy_on_host);
    RUN_TEST(test_pstr_is_identity_on_host);
    RUN_TEST(test_prog_char_typedef_exists);

    // stream_decode tests (exercises src/utility/cc3000_common.cpp)
    RUN_TEST(test_stream_to_uint16_zero);
    RUN_TEST(test_stream_to_uint16_low_byte_only);
    RUN_TEST(test_stream_to_uint16_high_byte_only);
    RUN_TEST(test_stream_to_uint16_little_endian_decode);
    RUN_TEST(test_stream_to_uint16_max);
    RUN_TEST(test_stream_to_uint16_with_offset);
    RUN_TEST(test_stream_to_uint16_high_bit_set);
    RUN_TEST(test_stream_to_uint32_zero);
    RUN_TEST(test_stream_to_uint32_little_endian_decode);
    RUN_TEST(test_stream_to_uint32_max);
    RUN_TEST(test_stream_to_uint32_with_offset);
    RUN_TEST(test_stream_to_uint32_high_bit_set);
    RUN_TEST(test_stream_to_uint32_ip_decode);

    // data_types tests
    RUN_TEST(test_uint8_size);
    RUN_TEST(test_int8_size);
    RUN_TEST(test_uint16_size);
    RUN_TEST(test_int16_size);
    RUN_TEST(test_uint32_size);
    RUN_TEST(test_int32_size);
    RUN_TEST(test_boolean_size);
    RUN_TEST(test_null_macro);
    RUN_TEST(test_false_macro);
    RUN_TEST(test_true_macro);
    RUN_TEST(test_ok_macro);
    RUN_TEST(test_uint8_value);
    RUN_TEST(test_int8_negative_value);
    RUN_TEST(test_uint16_value);
    RUN_TEST(test_uint32_value);
    RUN_TEST(test_boolean_true);
    RUN_TEST(test_boolean_false);

    return UNITY_END();
}
