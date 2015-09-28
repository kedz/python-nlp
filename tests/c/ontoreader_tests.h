#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"

error_info **ontonotes_test(char **name, size_t *num_errors);

#define NUM_ONTONOTES_TESTS 1

#define ONTONOTES_TESTS(var_name)                                            \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
    ontonotes_test,                                                          \
  };                                                                         \


