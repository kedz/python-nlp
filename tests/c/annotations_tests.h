#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/annotations.h"

error_info **annotations_test1(char **name, size_t *num_errors);
error_info **annotations_test2(char **name, size_t *num_errors);
error_info **annotations_test3(char **name, size_t *num_errors);
#define NUM_ANNOTATIONS_TESTS 3

#define ANNOTATIONS_TESTS(var_name)                                           \
  error_info** (*var_name[]) (char **, size_t*) = {                           \
   annotations_test1,                                                         \
   annotations_test2,                                                         \
   annotations_test3,                                                         \
  };                                                                          \

