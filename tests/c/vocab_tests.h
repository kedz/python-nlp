#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/vocab.h"
#include "nlp/annotations.h"

error_info **vocab_test1(char **name, size_t *num_errors);
error_info **vocab_test2(char **name, size_t *num_errors);
error_info **vocab_test3(char **name, size_t *num_errors);

#define NUM_VOCAB_TESTS 3

#define VOCAB_TESTS(var_name)                                             \
  error_info** (*var_name[]) (char **, size_t*) = {                           \
    vocab_test1,                                                              \
    vocab_test2,                                                              \
    vocab_test3,                                                              \
  };                                                                     \

