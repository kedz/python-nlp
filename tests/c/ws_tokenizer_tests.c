#include "ws_tokenizer_tests.h"

#define TOKEN_TEST                                                            \
  NL_annotations *ann = NL_ws_tokenize(&buffer, mgr);                         \
  if (ann == NULL) {                                                          \
      NEW_ERROR(80);                                                          \
      sprintf((char *) this_error->msg, "Tokenizer returned NULL!");          \
  } else {                                                                    \
      for (int i=0; i < ann->size; i++) {                                     \
          if (i < gold_num_tokens) {                                          \
              unsigned char *token = NULL;                                    \
              size_t token_length = 0;                                        \
              NL_bspan *span = NL_get_bspan(ann, i);                          \
              if (span->data == NULL) {                                       \
                  token = span->bytes;                                        \
                  token_length = span->size;                                  \
              } else {                                                        \
                  token = ((NL_string *) span->data)->bytes;                  \
                  token_length = ((NL_string *) span->data)->size;            \
              }                                                               \
              unsigned char *gold_token = gold[i];                            \
              size_t gold_length = strlen((char *) gold_token);               \
              if (token_length != gold_length                                 \
                          || memcmp(token, gold_token, token_length) != 0) {  \
                                                                              \
                *num_errors += 1;                                             \
                errors = realloc(errors, *num_errors * sizeof(error_info *)); \
                errors[*num_errors -1] = malloc(sizeof(error_info));          \
                error_info *this_error = errors[*num_errors -1];              \
                this_error->msg = NULL;                                       \
                                                                              \
                size_t cpy_s1 = strlen("Tokenizer returned \"");              \
                size_t cpy_s2 = strlen("\" but expected \"");                 \
                size_t cpy_s3 = strlen("\".");                                \
                size_t msg_size = cpy_s1 + cpy_s2 + cpy_s3                    \
                    + token_length + gold_length + 1;                         \
                this_error->msg = malloc(sizeof(char) * msg_size);            \
                this_error->msg[msg_size-1] = '\0';                           \
                memcpy(this_error->msg, "Tokenizer returned \"", cpy_s1);     \
                memcpy(&this_error->msg[cpy_s1], token, token_length);        \
                memcpy(&this_error->msg[cpy_s1 + token_length],               \
                       "\" but expected \"", cpy_s2);                         \
                memcpy(&this_error->msg[cpy_s1 + token_length + cpy_s2],      \
                       gold_token, gold_length);                              \
                memcpy(                                                       \
                    &this_error->msg[cpy_s1+token_length+cpy_s2+gold_length], \
                    "\".", cpy_s3);                                           \
              }                                                               \
          }                                                                   \
      }                                                                       \
  }                                                                           \
                                                                              \
                                                                              \
  if (ann->size != gold_num_tokens) {                                         \
      *num_errors += 1;                                                       \
      errors = realloc(errors, *num_errors * sizeof(error_info *));           \
      errors[*num_errors -1] = malloc(sizeof(error_info));                    \
      error_info *this_error = errors[*num_errors -1];                        \
      this_error->msg = malloc(sizeof(char *) *200);                          \
                                                                              \
      sprintf(                                                                \
          (char *) this_error->msg,                                           \
          "Tokenizer returned %lu tokens, should be %lu.",                    \
          ann->size, gold_num_tokens);                                       \
                                                                              \
  }                                                                           \
                                                                              \
  NL_deallocate_bspan_annotations(mgr, &ann);                                 \
                                                                              \
  int pool_size = 2;                                                          \
  for (int i=0; i < mgr->max_pools; i++) {                                    \
      unsigned int allocs = mgr->pools[i]->allocs;                            \
      if (allocs > 0) {                                                       \
          *num_errors += 1;                                                   \
          errors = realloc(errors, *num_errors * sizeof(error_info *));       \
          errors[*num_errors -1] = malloc(sizeof(error_info));                \
          error_info *this_error = errors[*num_errors -1];                    \
          errors[*num_errors-1]->msg = malloc(sizeof(char) * 80);             \
          sprintf(                                                            \
              (char *) this_error->msg,                                       \
              "Memory manager leak %d allocations in pool size %d.",          \
              allocs, pool_size);                                             \
      }                                                                       \
      pool_size = pool_size * 2;                                              \
                                                                              \
  }                                                                           \
  NL_free_v_memmgr(&mgr);  

error_info **ws_tokenizer_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "whitespace tokenizer test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_buffer buffer = {
        (unsigned char *) "This is a test of tokens.",
        strlen("This is a test of tokens.")
    };

    size_t gold_num_tokens = 6;
    unsigned char *gold[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "test",
        (unsigned char *) "of",
        (unsigned char *) "tokens.",
    };
    TOKEN_TEST
    return errors;
} 

error_info **ws_tokenizer_test2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "whitespace tokenizer test2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_buffer buffer = {
        (unsigned char *) "  This is a test of tokens.",
        strlen("  This is a test of tokens.")
    };

    size_t gold_num_tokens = 6;
    unsigned char *gold[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "test",
        (unsigned char *) "of",
        (unsigned char *) "tokens.",
    };
    TOKEN_TEST
    return errors;
}

error_info **ws_tokenizer_test3(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "whitespace tokenizer test3";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_buffer buffer = {
        (unsigned char *) "This is a test of tokens.   ",
        strlen("This is a test of tokens.   ")
    };

    size_t gold_num_tokens = 6;
    unsigned char *gold[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "test",
        (unsigned char *) "of",
        (unsigned char *) "tokens.",
    };
    TOKEN_TEST
    return errors;
}

error_info **ws_tokenizer_test4(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "whitespace tokenizer test4";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_buffer buffer = {
        (unsigned char *) "  This is a test of tokens.   ",
        strlen("  This is a test of tokens.   ")
    };

    size_t gold_num_tokens = 6;
    unsigned char *gold[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "test",
        (unsigned char *) "of",
        (unsigned char *) "tokens.",
    };
    TOKEN_TEST
    return errors;
}

error_info **ws_tokenizer_test5(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "whitespace tokenizer test5";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_buffer buffer = {
        (unsigned char *) "\xE2\x80\xA8This\ris\r\na\ntest of tokens.\xC2\xA0",
        strlen("\xE2\x80\xA8This\ris\r\na\ntest of tokens.\xC2\xA0")
    };

    size_t gold_num_tokens = 6;
    unsigned char *gold[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "test",
        (unsigned char *) "of",
        (unsigned char *) "tokens.",
    };
    TOKEN_TEST
    return errors;
}
