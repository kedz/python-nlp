#include "nlp/document.h"
#include <stddef.h>
#include <stdio.h>

int main() {

    printf("unsigned char: %zu\n", sizeof(unsigned char));
    printf("unsigned char*: %zu\n", sizeof(unsigned char*));
    printf("size_t: %zu\n", sizeof(size_t));
    printf("NL_span size: %zu\n", sizeof(NL_span));
    printf("NL_document size: %zu\n", sizeof(NL_document));
    

    return 0;
}
