#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer/whitespace_tokenizer.h"

error_info **ws_tokenizer_test1(char **name, size_t *num_errors);
error_info **ws_tokenizer_test2(char **name, size_t *num_errors);
error_info **ws_tokenizer_test3(char **name, size_t *num_errors);
error_info **ws_tokenizer_test4(char **name, size_t *num_errors);
error_info **ws_tokenizer_test5(char **name, size_t *num_errors);

#define NUM_WS_TOKENIZER_TESTS 5

#define WS_TOKENIZER_TESTS(var_name)                                         \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
    ws_tokenizer_test1,                                                      \
    ws_tokenizer_test2,                                                      \
    ws_tokenizer_test3,                                                      \
    ws_tokenizer_test4,                                                      \
    ws_tokenizer_test5,                                                      \
  };                                                                         \


