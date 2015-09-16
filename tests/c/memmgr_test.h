#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "testdefs.h"

#include "nlp/mem_manager.h" 

error_info **memmgr_test1(char **name, size_t *num_errors);

#define MEMMGR_TESTS(var_name)                                               \
    error_info** (*var_name[]) (char **, size_t *) = {                       \
        memmgr_test1,                                                        \
    };                                                                       \

#define NUM_MEMMGR_TESTS 1

