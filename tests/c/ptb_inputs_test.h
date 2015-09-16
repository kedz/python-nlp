#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"


error_info **ptb_test1(char **name, size_t *num_errors);
error_info **ptb_test2(char **name, size_t *num_errors);
error_info **ptb_test3(char **name, size_t *num_errors);
error_info **ptb_test4(char **name, size_t *num_errors);
error_info **ptb_test5(char **name, size_t *num_errors);
error_info **ptb_test6(char **name, size_t *num_errors);
error_info **ptb_test7(char **name, size_t *num_errors);
error_info **ptb_test8(char **name, size_t *num_errors);
error_info **ptb_test9(char **name, size_t *num_errors);
error_info **ptb_test10(char **name, size_t *num_errors);
error_info **ptb_test11(char **name, size_t *num_errors);
error_info **ptb_test12(char **name, size_t *num_errors);
error_info **ptb_test13(char **name, size_t *num_errors);
error_info **ptb_test14(char **name, size_t *num_errors);
error_info **ptb_test15(char **name, size_t *num_errors);
error_info **ptb_test16(char **name, size_t *num_errors);
error_info **ptb_test17(char **name, size_t *num_errors);
error_info **ptb_test18(char **name, size_t *num_errors);
error_info **ptb_test19(char **name, size_t *num_errors);
error_info **ptb_test20(char **name, size_t *num_errors);
error_info **ptb_test21(char **name, size_t *num_errors);
error_info **ptb_test22(char **name, size_t *num_errors);
error_info **ptb_test23(char **name, size_t *num_errors);
error_info **ptb_test24(char **name, size_t *num_errors);
error_info **ptb_test25(char **name, size_t *num_errors);
error_info **ptb_test26(char **name, size_t *num_errors);
error_info **corp_test1(char **name, size_t *num_errors);
error_info **corp_test2(char **name, size_t *num_errors);

error_info **jacob_eisenstein_apos_test(char **name, size_t *num_errors);
error_info **sgml_test1(char **name, size_t *num_errors);

#define NUM_PTB_INPUTS_TESTS 30

#define PTB_INPUTS_TESTS(var_name)                                           \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
    ptb_test1,                                                               \
    ptb_test2,                                                               \
    ptb_test3,                                                               \
    ptb_test4,                                                               \
    ptb_test5,                                                               \
    ptb_test6,                                                               \
    ptb_test7,                                                               \
    ptb_test8,                                                               \
    ptb_test9,                                                               \
    ptb_test10,                                                              \
    ptb_test11,                                                              \
    ptb_test12,                                                              \
    ptb_test13,                                                              \
    ptb_test14,                                                              \
    ptb_test15,                                                              \
    ptb_test16,                                                              \
    ptb_test17,                                                              \
    ptb_test18,                                                              \
    ptb_test19,                                                              \
    ptb_test20,                                                              \
    ptb_test21,                                                              \
    ptb_test22,                                                              \
    ptb_test23,                                                              \
    ptb_test24,                                                              \
    ptb_test25,                                                              \
    ptb_test26,                                                              \
    corp_test1,                                                              \
    corp_test2,                                                              \
    jacob_eisenstein_apos_test,                                              \
    sgml_test1,                                                              \
};                                                                           \


