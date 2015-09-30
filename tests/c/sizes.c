#include "nlp/document.h"
#include "nlp/tokenizer.h"
#include <stddef.h>
#include <stdio.h>

int main() {

    printf("unsigned char: %zu\n", sizeof(unsigned char));
    printf("unsigned char*: %zu\n", sizeof(unsigned char*));
    printf("size_t: %zu\n", sizeof(size_t));

    return 0;
}
