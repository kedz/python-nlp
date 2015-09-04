#include <stdlib.h>

size_t NL_get_size_unicode_quotes(unsigned char *p, size_t buf_length);

void NL_unicode_quotes_probably_left(unsigned char *p, size_t buf_length,
    unsigned char *transform);

void NL_unicode_quotes_probably_right(unsigned char *p, size_t buf_length,
    unsigned char *transform);


size_t NL_get_size_ascii_quotes(unsigned char *p, size_t buf_length);
