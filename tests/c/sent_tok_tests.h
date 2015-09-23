#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"

error_info **sent_tokenizer_test1(char **name, size_t *num_errors);

#define NUM_SENT_TOKENIZER_TESTS 1

#define SENT_TOKENIZER_TESTS(var_name)                                       \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
   sent_tokenizer_test1,                                                         \
  };                                                                         \

