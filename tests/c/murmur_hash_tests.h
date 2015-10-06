#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"
#include "nlp/types.h"
#include "nlp/mem_manager.h"
#include "nlp/MurmurHash3.h"

error_info **murmur_hash_test1(char **name, size_t *num_errors);
error_info **murmur_hash_test2(char **name, size_t *num_errors);
error_info **murmur_hash_test3(char **name, size_t *num_errors);
error_info **murmur_hash_test4(char **name, size_t *num_errors);
error_info **murmur_hash_test5(char **name, size_t *num_errors);

#define NUM_MURMUR_HASH_TESTS 5

#define MURMUR_HASH_TESTS(var_name)                                           \
  error_info** (*var_name[]) (char **, size_t*) = {                           \
    murmur_hash_test1,                                                        \
    murmur_hash_test2,                                                        \
    murmur_hash_test3,                                                        \
    murmur_hash_test4,                                                        \
    murmur_hash_test5,                                                        \
  };                                                                          \


