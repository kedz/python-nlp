#include "sent_tok_tests.h"

#define SENT_TEST                                                             \
  NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);                \
  if (tokens == NULL) {                                                       \
      NEW_ERROR(80);                                                          \
      sprintf((char *) this_error->msg, "Tokenizer returned NULL!");          \
  } else {                                                                    \
      for (int i=0; i < tokens->size; i++) {                                  \
          if (i < gold_num_tokens) {                                          \
              unsigned char *token = NULL;                                    \
              size_t token_length = 0;                                        \
              NL_bspan *span = NL_get_bspan(tokens, i);                       \
              if (span->data == NULL) {                                       \
                  token = span->bytes;                                        \
                  token_length = span->size;                                  \
              } else {                                                        \
                  token = ((NL_string *) span->data)->bytes;                  \
                  token_length = ((NL_string *) span->data)->size;            \
              }                                                               \
              unsigned char *gold_token = gold_tokens[i];                     \
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
  if (tokens->size != gold_num_tokens) {                                      \
      *num_errors += 1;                                                       \
      errors = realloc(errors, *num_errors * sizeof(error_info *));           \
      errors[*num_errors -1] = malloc(sizeof(error_info));                    \
      error_info *this_error = errors[*num_errors -1];                        \
      this_error->msg = malloc(sizeof(char *) *200);                          \
                                                                              \
      sprintf(                                                                \
          (char *) this_error->msg,                                           \
          "Tokenizer returned %lu tokens, should be %lu.",                    \
          tokens->size, gold_num_tokens);                                     \
                                                                              \
  }                                                                           \
  NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);              \
  if (sentences == NULL) {                                                    \
      NEW_ERROR(80);                                                          \
      sprintf((char *) this_error->msg, "Sentence tokenizer returned NULL!"); \
  } else {                                                                    \
      for (int i=0; i < sentences->size; i++) {                               \
          if (i < gold_num_sents) {                                           \
              NL_sspan *sent = NL_get_sspan(sentences, i);                    \
              NL_bspan *start = NL_get_bspan(tokens, sent->span_id);          \
              NL_bspan *stop = NL_get_bspan(                                  \
                  tokens, sent->span_id + sent->size - 1);                    \
              unsigned char *sent_str = start->bytes;                         \
              size_t sent_str_size = stop->bytes + stop->size - start->bytes; \
              if (memcmp(sent_str, gold_sents[i], sent_str_size) != 0 ||      \
                          sent_str_size != strlen((char *) gold_sents[i])) {  \
                  NEW_ERROR(80);                                              \
                  sprintf((char *) this_error->msg, "Bad sentence string: "); \
                  size_t pos = strlen("Bad sentence string: ");               \
                  memcpy(this_error->msg + pos, sent_str, sent_str_size);     \
                  *(this_error->msg + pos + sent_str_size) = '\0';            \
              }                                                               \
          }                                                                   \
      }                                                                       \
  }                                                                           \
  NL_deallocate_sspan_annotations(mgr, &sentences);                           \
  NL_deallocate_bspan_annotations(mgr, &tokens);                              \
  NL_deallocate_v_mem(mgr, (void **) &cfg);                                   \
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


error_info **sent_tokenizer_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "sent tok test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This is a sentence. Also this! Whoa?!";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "sentence",
        (unsigned char *) ".",
        (unsigned char *) "Also",
        (unsigned char *) "this",
        (unsigned char *) "!",
        (unsigned char *) "Whoa",
        (unsigned char *) "?!",
    };
    size_t gold_num_tokens = 10;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This is a sentence.",
        (unsigned char *) "Also this!",
        (unsigned char *) "Whoa?!",
    };
    size_t gold_num_sents = 3;

    SENT_TEST

    return errors;
}

error_info **sent_tokenizer_test1_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "sent tok test1.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This is a sentence. Also this! Whoa?!";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 3;

    unsigned char * gold_sent_tokens[][5] = { 
      { (unsigned char *) "This", 
        (unsigned char *) "is", 
        (unsigned char *) "a", 
        (unsigned char *) "sentence", 
        (unsigned char *) "."},
      { (unsigned char *) "Also", 
        (unsigned char *) "this", 
        (unsigned char *) "!", NULL, NULL},
      { (unsigned char *) "Whoa", 
        (unsigned char *) "?!", NULL, NULL, NULL}, 
    };
    size_t gold_sent_tokens_sizes[] = {5, 3, 2};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test1_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test1_1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should only be one sentence.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "only",
        (unsigned char *) "be",
        (unsigned char *) "one",
        (unsigned char *) "sentence",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 7;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should only be one sentence.",
    };
    size_t gold_num_sents = 1;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test1_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test1.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should only be one sentence.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 1;

    unsigned char * gold_sent_tokens[][7] = { 
      { (unsigned char *) "This", 
        (unsigned char *) "should", 
        (unsigned char *) "only", 
        (unsigned char *) "be", 
        (unsigned char *) "one", 
        (unsigned char *) "sentence", 
        (unsigned char *) "."},
    };
    size_t gold_sent_tokens_sizes[] = {7};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test2_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test2_1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences.  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) ".",
        (unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 11;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be two sentences.",
        (unsigned char *) "There is a split.",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test2_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test2.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences.  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][6] = { 
       {(unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) ".",
       },
       {(unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".", NULL,
       },
    };
    size_t gold_sent_tokens_sizes[] = {6, 5};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test3_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test3_1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences!  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "!",
        (unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 11;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be two sentences!",
        (unsigned char *) "There is a split.",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test3_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test3.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences!  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][6] = { 
       {(unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "!",
       },
       {(unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".", NULL,
       },
    };
    size_t gold_sent_tokens_sizes[] = {6, 5};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test4_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test4_1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences?  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "?",
        (unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 11;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be two sentences?",
        (unsigned char *) "There is a split.",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test4_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test4.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences?  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][6] = { 
       {(unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "?",
       },
       {(unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".", NULL,
       },
    };
    size_t gold_sent_tokens_sizes[] = {6, 5};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test5_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test5_1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences!!!?!!  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "!!!?!!",
        (unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 11;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be two sentences!!!?!!",
        (unsigned char *) "There is a split.",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test5_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test5.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences!!!?!!  There is a split.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][6] = { 
       {(unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) "!!!?!!",
       },
       {(unsigned char *) "There",
        (unsigned char *) "is",
        (unsigned char *) "a",
        (unsigned char *) "split",
        (unsigned char *) ".", NULL,
       },
    };
    size_t gold_sent_tokens_sizes[] = {6, 5};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test6_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test6.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences.  Second one incomplete";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) ".",
        (unsigned char *) "Second",
        (unsigned char *) "one",
        (unsigned char *) "incomplete",
    };
    size_t gold_num_tokens = 9;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be two sentences.",
        (unsigned char *) "Second one incomplete",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test6_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test6.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be two sentences.  Second one incomplete";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][6] = { 
       {(unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "two",
        (unsigned char *) "sentences",
        (unsigned char *) ".",
       },
       {(unsigned char *) "Second",
        (unsigned char *) "one",
        (unsigned char *) "incomplete",
        NULL, NULL, NULL
       },
    };
    size_t gold_sent_tokens_sizes[] = {6, 3};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test7_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test7.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "One incomplete sentence";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "One",
        (unsigned char *) "incomplete",
        (unsigned char *) "sentence",
    };
    size_t gold_num_tokens = 3;

    unsigned char *gold_sents[] = {
        (unsigned char *) "One incomplete sentence",
    };
    size_t gold_num_sents = 1;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test7_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test7.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "One incomplete sentence";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 1;

    unsigned char * gold_sent_tokens[][3] = { 
      { (unsigned char *) "One", 
        (unsigned char *) "incomplete", 
        (unsigned char *) "sentence", },
    };
    size_t gold_sent_tokens_sizes[] = {3};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test8_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test8.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "(Break after a parenthesis.)  (Or after \"quoted stuff!\")";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "-LRB-",
        (unsigned char *) "Break",
        (unsigned char *) "after",
        (unsigned char *) "a",
        (unsigned char *) "parenthesis",
        (unsigned char *) ".",
        (unsigned char *) "-RRB-",
        (unsigned char *) "-LRB-",
        (unsigned char *) "Or",
        (unsigned char *) "after",
        (unsigned char *) "``",
        (unsigned char *) "quoted",
        (unsigned char *) "stuff",
        (unsigned char *) "!",
        (unsigned char *) "''",
        (unsigned char *) "-RRB-",
    };
    size_t gold_num_tokens = 16;

    unsigned char *gold_sents[] = {
        (unsigned char *) "(Break after a parenthesis.)",
        (unsigned char *) "(Or after \"quoted stuff!\")",
    };
    size_t gold_num_sents = 2;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test8_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test8.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "(Break after a parenthesis.)  (Or after \"quoted stuff!\")";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 2;

    unsigned char * gold_sent_tokens[][9] = { 
       {(unsigned char *) "(",
        (unsigned char *) "Break",
        (unsigned char *) "after",
        (unsigned char *) "a",
        (unsigned char *) "parenthesis",
        (unsigned char *) ".",
        (unsigned char *) ")",
        NULL, NULL,
       },
       {(unsigned char *) "(",
        (unsigned char *) "Or",
        (unsigned char *) "after",
        (unsigned char *) "\"",
        (unsigned char *) "quoted",
        (unsigned char *) "stuff",
        (unsigned char *) "!",
        (unsigned char *) "\"",
        (unsigned char *) ")",
       },
    };
    size_t gold_sent_tokens_sizes[] = {7, 9};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test9_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test9.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) "  ";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
    };
    size_t gold_num_tokens = 0;

    unsigned char *gold_sents[] = {
    };
    size_t gold_num_sents = 0;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test9_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test9.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) "  ";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 0;

    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    if (sentences->size != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test10_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test10.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "This should be\n one sentence.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "This",
        (unsigned char *) "should",
        (unsigned char *) "be",
        (unsigned char *) "one",
        (unsigned char *) "sentence",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 6;

    unsigned char *gold_sents[] = {
        (unsigned char *) "This should be\n one sentence.",
    };
    size_t gold_num_sents = 1;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test10_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test10.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) 
        "This should be\n one sentence.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 1;

    unsigned char * gold_sent_tokens[][6] = { 
      { (unsigned char *) "This", 
        (unsigned char *) "should", 
        (unsigned char *) "be", 
        (unsigned char *) "one", 
        (unsigned char *) "sentence", 
        (unsigned char *) "."},
    };
    size_t gold_sent_tokens_sizes[] = {6};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test11_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test11.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "'') Funny stuff joined on.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "''",
        (unsigned char *) "-RRB-",
        (unsigned char *) "Funny",
        (unsigned char *) "stuff",
        (unsigned char *) "joined",
        (unsigned char *) "on",
        (unsigned char *) ".",
    };
    size_t gold_num_tokens = 7;

    unsigned char *gold_sents[] = {
        (unsigned char *) "'') Funny stuff joined on.",
    };
    size_t gold_num_sents = 1;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test11_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test11.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) "'') Funny stuff joined on.";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 1;

    unsigned char * gold_sent_tokens[][7] = { 
      { (unsigned char *) "''", 
        (unsigned char *) ")", 
        (unsigned char *) "Funny", 
        (unsigned char *) "stuff", 
        (unsigned char *) "joined", 
        (unsigned char *) "on", 
        (unsigned char *) "."},
    };
    size_t gold_sent_tokens_sizes[] = {7};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **ptb_sent_tokenizer_test12_1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test12.1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    unsigned char *bytes = (unsigned char *) 
        "Mr. White got a loaf of bread";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    unsigned char *gold_tokens[] = {
        (unsigned char *) "Mr.",
        (unsigned char *) "White",
        (unsigned char *) "got",
        (unsigned char *) "a",
        (unsigned char *) "loaf",
        (unsigned char *) "of",
        (unsigned char *) "bread",
    };
    size_t gold_num_tokens = 7;

    unsigned char *gold_sents[] = {
        (unsigned char *) "Mr. White got a loaf of bread",
    };
    size_t gold_num_sents = 1;

    SENT_TEST

    return errors;
}

error_info **ptb_sent_tokenizer_test12_2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb sent tok test12.2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);


    unsigned char *bytes = (unsigned char *) "Mr. White got a loaf of bread";
    NL_buffer buffer = {bytes, strlen((char *) bytes)};

    size_t gold_num_sents = 1;

    unsigned char * gold_sent_tokens[][7] = { 
      { (unsigned char *) "Mr.", 
        (unsigned char *) "White", 
        (unsigned char *) "got", 
        (unsigned char *) "a", 
        (unsigned char *) "loaf", 
        (unsigned char *) "of", 
        (unsigned char *) "bread"},
    };
    size_t gold_sent_tokens_sizes[] = {7};
    
    NL_annotations *tokens = NL_tokenize_buf(&buffer, cfg, mgr);
    NL_annotations *sentences = NL_sentence_tokenize(tokens, mgr);

    for (size_t i=0; i < sentences->size; i++) {
        if (i >= gold_num_sents) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Found %lu sentences, expected %lu", 
                sentences->size, gold_num_sents);
            break;
        } else {
            NL_sspan *sent = NL_get_sspan(sentences, i);
            for (size_t j=0; j < sent->size; j++) {
                if (j >= gold_sent_tokens_sizes[i]) {
                    NEW_ERROR(80);
                    sprintf((char *) this_error->msg,
                            "Found %lu tokens, expected %lu",
                            sent->size, gold_sent_tokens_sizes[i]);
                } else {
                    NL_bspan *tok = NL_get_bspan(tokens, j + sent->span_id);
                    unsigned char *gold_token = gold_sent_tokens[i][j];
                    if (tok->size != strlen((char *)gold_token) ||
                        memcmp(tok->bytes, gold_token, tok->size) != 0) {
                        NEW_ERROR(200);
                        sprintf((char *) this_error->msg,
                                "Expected string \"%s\" but got ",
                                gold_token);
                        
                        memcpy(this_error->msg + 27 
                                    + strlen((char *)gold_token), 
                               tok->bytes, tok->size);
                        *(this_error->msg + 27 + strlen((char *) gold_token)
                                + tok->size) = '\0';


                    }
                }
            }
        } 
    }

    NL_deallocate_sspan_annotations(mgr, &sentences);
    NL_deallocate_bspan_annotations(mgr, &tokens);
    NL_deallocate_v_mem(mgr,(void **) &cfg);
    NL_free_v_memmgr(&mgr);

    return errors;
}

