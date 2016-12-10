/* main.c */

/*
    This program demonstrates a simple application of JSON_checker. It reads
    a JSON text from STDIN, producing an error message if the text is rejected.

        % JSON_checker <test/pass1.json
*/

#include <stdlib.h>
#include <stdio.h>
#include "JSON_checker.h"

int main(int argc, char* argv[]) {
/*
    Read STDIN. Exit with a message if the input is not well-formed JSON text.

    jc will contain a JSON_checker with a maximum depth of 20.
*/
    int line_number = 1;
    int character_position = 0;
    int at_token_start = 1;
    int show_tokens = 0; /* Set to non-zero to write tokens separated by */
    
    JSON_checker jc = new_JSON_checker(20);

    if (argc > 1 && !strcmp(argv[1],"--show")) {
        show_tokens = 1;
    }

    for (;;) {
        int next_char = getchar();
        if (next_char <= 0) {
            break;
        }
        character_position += 1;
        if (next_char == '\n') {
            line_number++;
            character_position = 0;
        }
        if (!JSON_checker_char(jc, next_char)) {
            /* Got syntax error. Report it. */
            if (next_char >= 0x20 
                && next_char < 0x7f 
                && next_char != '\'') {
                fprintf(stderr,
                    "JSON_checker_char:%d:%d syntax error at ('%c')",
                    line_number, character_position, next_char);
            } else {
                fprintf(stderr,
                    "JSON_checker_char:%d:%d syntax error at ('\\x%02x')",
                    line_number, character_position, next_char);
            }
            exit(1);
        }
        /* 
            Handle the flags for token start 
         */
        if (show_tokens) {
            if (at_token_start || (jc->start_token & 1)) {
                /* token starts before this character */
                putchar('|');
            }
            putchar(next_char);
        }
        if (jc->start_token & 2) {
            /* Token starts on next character */
            at_token_start = 1;
        } else {
            at_token_start = 0;
        }
    }
    if (!JSON_checker_done(jc)) {
        fprintf(stderr, "JSON_checker_end: syntax error\n");
        exit(1);
    }
}