#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"

//error_info **tokenizer_test1(char **name, size_t *num_errors);
//error_info **tokenizer_test2(char **name, size_t *num_errors);
//error_info **tokenizer_test3(char **name, size_t *num_errors);
error_info **plangs_test(char **name, size_t *num_errors);
error_info **assims_no_split_test(char **name, size_t *num_errors);
error_info **assims_split_test(char **name, size_t *num_errors);
error_info **assims2_no_split_test(char **name, size_t *num_errors);
error_info **assims2_split_test(char **name, size_t *num_errors);

#define NUM_TOKENIZER_TESTS 5

#define TOKENIZER_TESTS(var_name)                                            \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
    plangs_test,                                                             \
    assims_no_split_test,                                                    \
    assims_split_test,                                                       \
    assims2_no_split_test,                                                   \
    assims2_split_test,                                                      \
  };                                                                         \


