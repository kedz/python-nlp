#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/util/conll_reader.h"

error_info **conll_reader_test1(char **name, size_t *num_errors);
error_info **conll_reader_test2(char **name, size_t *num_errors);
error_info **conll_reader_test3(char **name, size_t *num_errors);

#define NUM_CONLL_READER_TESTS 3

#define CONLL_READER_TESTS(var_name)                                          \
  error_info** (*var_name[]) (char **, size_t*) = {                           \
    conll_reader_test1,                                                       \
    conll_reader_test2,                                                       \
    conll_reader_test3,                                                       \
  };                                                                          \


