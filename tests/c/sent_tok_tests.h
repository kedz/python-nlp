#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#include "testdefs.h"

#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"
#include "nlp/tokenizer/sentence_tokenizer.h"

error_info **sent_tokenizer_test1(char **name, size_t *num_errors);
error_info **sent_tokenizer_test1_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test1_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test1_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test2_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test2_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test3_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test3_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test4_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test4_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test5_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test5_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test6_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test6_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test7_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test7_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test8_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test8_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test9_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test9_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test10_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test10_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test11_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test11_2(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test12_1(char **name, size_t *num_errors);
error_info **ptb_sent_tokenizer_test12_2(char **name, size_t *num_errors);

#define NUM_SENT_TOKENIZER_TESTS 26

#define SENT_TOKENIZER_TESTS(var_name)                                       \
  error_info** (*var_name[]) (char **, size_t*) = {                          \
   sent_tokenizer_test1,                                                     \
   sent_tokenizer_test1_2,                                                    \
   ptb_sent_tokenizer_test1_1,                                                \
   ptb_sent_tokenizer_test1_2,                                                \
   ptb_sent_tokenizer_test2_1,                                                \
   ptb_sent_tokenizer_test2_2,                                                \
   ptb_sent_tokenizer_test3_1,                                                \
   ptb_sent_tokenizer_test3_2,                                                \
   ptb_sent_tokenizer_test4_1,                                                \
   ptb_sent_tokenizer_test4_2,                                                \
   ptb_sent_tokenizer_test5_1,                                                \
   ptb_sent_tokenizer_test5_2,                                                \
   ptb_sent_tokenizer_test6_1,                                                \
   ptb_sent_tokenizer_test6_2,                                                \
   ptb_sent_tokenizer_test7_1,                                                \
   ptb_sent_tokenizer_test7_2,                                                \
   ptb_sent_tokenizer_test8_1,                                                \
   ptb_sent_tokenizer_test8_2,                                                \
   ptb_sent_tokenizer_test9_1,                                                \
   ptb_sent_tokenizer_test9_2,                                                \
   ptb_sent_tokenizer_test10_1,                                               \
   ptb_sent_tokenizer_test10_2,                                               \
   ptb_sent_tokenizer_test11_1,                                               \
   ptb_sent_tokenizer_test11_2,                                               \
   ptb_sent_tokenizer_test12_1,                                               \
   ptb_sent_tokenizer_test12_2,                                               \
  };                                                                         \

