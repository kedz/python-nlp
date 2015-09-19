#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h" 

error_info **memmgr_test1(char **name, size_t *num_errors);
error_info **memmgr_test2(char **name, size_t *num_errors);
error_info **memmgr_test3(char **name, size_t *num_errors);
error_info **vmemmgr_test1(char **name, size_t *num_errors);
error_info **vmemmgr_test2(char **name, size_t *num_errors);
error_info **vmemmgr_test3(char **name, size_t *num_errors);
error_info **vmemmgr_test4(char **name, size_t *num_errors);
error_info **vmemmgr_test5(char **name, size_t *num_errors);
error_info **vmemmgr_test6(char **name, size_t *num_errors);

#define MEMMGR_TESTS(var_name)                                               \
    error_info** (*var_name[]) (char **, size_t *) = {                       \
        memmgr_test1,                                                        \
        memmgr_test2,                                                        \
        memmgr_test3,                                                        \
        vmemmgr_test1,                                                       \
        vmemmgr_test2,                                                       \
        vmemmgr_test3,                                                       \
        vmemmgr_test4,                                                       \
        vmemmgr_test5,                                                       \
        vmemmgr_test6,                                                       \
    };                                                                       \

#define NUM_MEMMGR_TESTS 9

