#include <stdlib.h>

size_t NL_get_size_unicode_quotes(unsigned char *p, size_t buf_length);

void NL_unicode_quotes_probably_left(unsigned char *p, size_t buf_length,
    unsigned char *transform);

void NL_unicode_quotes_probably_right(unsigned char *p, size_t buf_length,
    unsigned char *transform);

size_t NL_get_size_ascii_quotes(unsigned char *p, size_t buf_length);

void NL_ascii_quotes(unsigned char *p, size_t buf_length,
        unsigned char *transform);

size_t NL_get_size_latex_quotes(unsigned char *p, size_t buf_length);

void NL_latex_quotes_probably_left(unsigned char *p, size_t buf_length,
    unsigned char *transform);

void NL_latex_quotes_probably_right(unsigned char *p, size_t buf_length,
    unsigned char *transform);

void NL_copy_no_softhyphen(unsigned char *p, size_t buf_length,
    unsigned char *transform);

void NL_normalize_ampersand(unsigned char *p, size_t buf_length,
    unsigned char *transform);

size_t NL_get_size_escaped_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length);

void NL_escape_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length, unsigned char *transform);

size_t NL_get_size_normalized_spaces(unsigned char *p, 
    size_t buf_length);

void NL_normalize_spaces(unsigned char *p, 
    size_t buf_length, unsigned char *transform);
