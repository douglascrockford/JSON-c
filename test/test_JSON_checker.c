#include "fff.h"
#include "../JSON_checker.h"
#include "unity.h"
#include <stdbool.h>
#include <stdio.h>

DEFINE_FFF_GLOBALS;

void setUp(void) {
    // Reset all faked functions
}

void tearDown(void) {
    // nothing yet
}

#define MAX_JSON_DEPTH 200

/**
 * @brief Test for correctly detecting both valid and invalid JSON syntax.
 *
 * Check the contents of a JSON file, return true if expect_good is true and the
 * JSON is valid, return true if expect_good is false and the JSON is invalid,
 * return false otherwise.
 *
 * The source data here is derived from the (excellent) JSON parsing test suite
 * at https://github.com/nst/JSONTestSuite/tree/master.
 */
static bool check_format(const char *filename, bool expect_success) {
    JSON_checker jc = new_JSON_checker(MAX_JSON_DEPTH);
    bool succeeded = false;
    char next_char;
    int n_read;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "test error: could not open %s\n", filename);
        return false;
    }

    for (;;) {
        n_read = fread(&next_char, sizeof(char), 1, fp);
        if (n_read != 1) {
            break;
        }
        if (!JSON_checker_char(jc, next_char)) {
            break;
        }
    }
    // At end of file
    if (JSON_checker_done(jc)) {
        succeeded = true;
    }

    return expect_success == succeeded;
}

#define JSON_TEST_SUITE_DIR "./test_parsing/"
#define TEST_JSON_GOOD_FMT(f) TEST_ASSERT_MESSAGE(check_format(f, true), f);
#define TEST_JSON_BAD_FMT(f) TEST_ASSERT_MESSAGE(check_format(f, false), f);

void test_json_check_good_format(void) {
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_arraysWithSpaces.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_empty.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_empty-string.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_ending_with_newline.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_false.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_heterogeneous.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_null.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_with_1_and_newline.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_with_leading_space.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_with_several_null.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_array_with_trailing_space.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_0e+1.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_0e1.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_after_space.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_double_close_to_zero.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_int_with_exp.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_minus_zero.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_negative_int.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_negative_one.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_negative_zero.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_capital_e.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_capital_e_neg_exp.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_capital_e_pos_exp.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_exponent.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_fraction_exponent.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_neg_exp.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_real_pos_exponent.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_simple_int.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_number_simple_real.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_basic.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_duplicated_key.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_duplicated_key_and_value.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_empty.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_empty_key.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_escaped_null_in_key.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_extreme_numbers.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_long_strings.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_simple.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_string_unicode.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_object_with_newlines.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_1_2_3_bytes_UTF-8_sequences.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_accepted_surrogate_pair.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_accepted_surrogate_pairs.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_allowed_escapes.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_backslash_and_u_escaped_zero.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_backslash_doublequotes.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_comments.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_double_escape_a.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_double_escape_n.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_escaped_control_character.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_escaped_noncharacter.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_in_array.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_in_array_with_leading_space.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_last_surrogates_1_and_2.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_nbsp_uescaped.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_nonCharacterInUTF-8_U+10FFFF.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_nonCharacterInUTF-8_U+FFFF.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_null_escape.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_one-byte-utf-8.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_pi.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_reservedCharacterInUTF-8_U+1BFFF.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_simple_ascii.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_space.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_surrogates_U+1D11E_MUSICAL_SYMBOL_G_CLEF.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_three-byte-utf-8.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_two-byte-utf-8.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_u+2028_line_sep.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_u+2029_par_sep.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_uEscape.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_uescaped_newline.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unescaped_char_delete.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_2.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_escaped_double_quote.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+10FFFE_nonchar.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+1FFFE_nonchar.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+200B_ZERO_WIDTH_SPACE.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+2064_invisible_plus.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+FDD0_nonchar.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicode_U+FFFE_nonchar.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_unicodeEscapedBackslash.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_utf8.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_string_with_del_character.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_false.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_int.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_negative_real.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_null.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_string.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_lonely_true.json");
    // TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_string_empty.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_trailing_newline.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_true_in_array.json");
    TEST_JSON_GOOD_FMT(JSON_TEST_SUITE_DIR "y_structure_whitespace_array.json");
}

void test_json_check_bad_format(void) {
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_1_true_without_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_a_invalid_utf8.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_colon_instead_of_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_comma_after_close.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_comma_and_number.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_double_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_double_extra_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_extra_close.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_extra_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_incomplete.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_incomplete_invalid_value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_inner_array_no_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_invalid_utf8.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_items_separated_by_semicolon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_just_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_just_minus.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_missing_value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_newlines_unclosed.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_number_and_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_number_and_several_commas.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_spaces_vertical_tab_formfeed.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_star_inside.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_unclosed.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_unclosed_trailing_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_unclosed_with_new_lines.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_array_unclosed_with_object_inside.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_incomplete_false.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_incomplete_null.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_incomplete_true.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_multidigit_number_then_00.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_.-1.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_.2e-3.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_++.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_+1.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_+Inf.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0.1.2.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0.3e.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0.3e+.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0.e1.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0_capital_E.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0_capital_E+.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_-01.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0e.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_0e+.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_-1.0..json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_1.0e.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_1.0e-.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_1.0e+.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_1_000.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_1eE2.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_-2..json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_2.e+3.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_2.e3.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_2.e-3.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_9.e+.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_expression.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_hex_1_digit.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_hex_2_digits.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_Inf.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_infinity.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_invalid+-.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_invalid-negative-real.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_invalid-utf-8-in-bigger-int.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_invalid-utf-8-in-exponent.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_invalid-utf-8-in-int.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_minus_infinity.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_minus_sign_with_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_minus_space_1.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_NaN.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_-NaN.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_neg_int_starting_with_zero.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_neg_real_without_int_part.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_neg_with_garbage_at_end.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_real_garbage_after_e.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_real_with_invalid_utf8_after_e.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_real_without_fractional_part.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_starting_with_dot.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_U+FF11_fullwidth_digit_one.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_with_alpha.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_with_alpha_char.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_number_with_leading_zero.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_bad_value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_bracket_key.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_comma_instead_of_colon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_double_colon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_emoji.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_garbage_at_end.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_key_with_single_quotes.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_lone_continuation_byte_in_key_and_trailing_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_missing_colon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_missing_key.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_missing_semicolon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_missing_value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_no-colon.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_non_string_key.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_non_string_key_but_huge_number_instead.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_repeated_null_null.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_several_trailing_commas.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_single_quote.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_trailing_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_trailing_comment.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_trailing_comment_open.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_trailing_comment_slash_open.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_trailing_comment_slash_open_incomplete.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_two_commas_in_a_row.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_unquoted_key.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_unterminated-value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_with_single_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_object_with_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_single_space.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_1_surrogate_then_escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_1_surrogate_then_escape_u.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_1_surrogate_then_escape_u1.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_1_surrogate_then_escape_u1x.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_accentuated_char_no_quotes.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_backslash_00.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_escape_x.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_escaped_backslash_bad.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_escaped_ctrl_char_tab.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_escaped_emoji.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_incomplete_escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_incomplete_escaped_character.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_incomplete_surrogate.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_incomplete_surrogate_escape_invalid.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_invalid_backslash_esc.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_invalid_unicode_escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_invalid_utf8_after_escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_invalid-utf-8-in-escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_leading_uescaped_thinspace.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_no_quotes_with_bad_escape.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_single_doublequote.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_single_quote.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_single_string_no_double_quotes.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_start_escape_unclosed.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_unescaped_ctrl_char.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_unescaped_newline.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_unescaped_tab.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_unicode_CapitalU.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_string_with_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_100000_opening_arrays.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_angle_bracket_..json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_angle_bracket_null.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_array_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_array_with_extra_array_close.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_array_with_unclosed_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_ascii-unicode-identifier.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_capitalized_True.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_close_unopened_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_comma_instead_of_closing_brace.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_double_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_end_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_incomplete_UTF8_BOM.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_lone-invalid-utf-8.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_lone-open-bracket.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_no_data.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_null-byte-outside-string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_number_with_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_object_followed_by_closing_object.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_object_unclosed_no_value.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_object_with_comment.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_object_with_trailing_garbage.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_apostrophe.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_object.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_open_object.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_open_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_array_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object_close_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object_comma.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object_open_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object_open_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_object_string_with_apostrophes.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_open_open.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_single_eacute.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_single_star.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_trailing_#.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_U+2060_word_joined.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_uescaped_LF_before_string.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unclosed_array.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unclosed_array_partial_null.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unclosed_array_unfinished_false.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unclosed_array_unfinished_true.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unclosed_object.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_unicode-identifier.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_UTF8_BOM_no_data.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_whitespace_formfeed.json");
    TEST_JSON_BAD_FMT(JSON_TEST_SUITE_DIR "n_structure_whitespace_U+2060_word_joiner.json");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_json_check_good_format);
    RUN_TEST(test_json_check_bad_format);

    return UNITY_END();
}
