#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "nlp/tokenizer_utils.h"
#include "testdefs.h"

error_info **tutils_test1(char **name, size_t *num_errors);
error_info **tutils_test2(char **name, size_t *num_errors);
error_info **tutils_test3(char **name, size_t *num_errors);
error_info **tutils_test4(char **name, size_t *num_errors);
error_info **tutils_test5(char **name, size_t *num_errors);
error_info **tutils_test6(char **name, size_t *num_errors);
error_info **tutils_test7(char **name, size_t *num_errors);
error_info **tutils_test8(char **name, size_t *num_errors);
error_info **tutils_test9(char **name, size_t *num_errors);
error_info **tutils_test10(char **name, size_t *num_errors);
error_info **tutils_test11(char **name, size_t *num_errors);
error_info **tutils_test12(char **name, size_t *num_errors);
error_info **tutils_test13(char **name, size_t *num_errors);
error_info **tutils_test14(char **name, size_t *num_errors);
error_info **tutils_test15(char **name, size_t *num_errors);
error_info **tutils_test16(char **name, size_t *num_errors);
error_info **tutils_test17(char **name, size_t *num_errors);
error_info **tutils_test18(char **name, size_t *num_errors);
error_info **tutils_test19(char **name, size_t *num_errors);
error_info **tutils_test20(char **name, size_t *num_errors);

#define TOK_UTILS_TESTS(var_name)                                            \
    error_info** (*var_name[]) (char **, size_t *) = {                       \
        tutils_test1,                                                        \
        tutils_test2,                                                        \
        tutils_test3,                                                        \
        tutils_test4,                                                        \
        tutils_test5,                                                        \
        tutils_test6,                                                        \
        tutils_test7,                                                        \
        tutils_test8,                                                        \
        tutils_test9,                                                        \
        tutils_test10,                                                       \
        tutils_test11,                                                       \
        tutils_test12,                                                       \
        tutils_test13,                                                       \
        tutils_test14,                                                       \
        tutils_test15,                                                       \
        tutils_test16,                                                       \
        tutils_test17,                                                       \
        tutils_test18,                                                       \
        tutils_test19,                                                       \
        tutils_test20,                                                       \
    };                                                                       \

#define NUM_TOK_UTILS_TESTS 20

