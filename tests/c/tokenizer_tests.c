#include "tokenizer_tests.h"

//error_info **tokenizer_test1(char **name, size_t *num_errors) {
//
//    error_info **errors = NULL;
//    *num_errors = 0;
//    *name = "tokenizer test1";
//
//
//    unsigned char *buf = (unsigned char *) "This is a test of tokens.";
//    size_t num_tokens;
//    size_t gold_num_tokens = 7;
//    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
//    NL_tokenize_buf(
//            buf, strlen((char *)buf), &num_tokens, NULL, mgr);
//    if (num_tokens != gold_num_tokens) {
//        NEW_ERROR(80)
//        sprintf((char *) this_error->msg,
//                "Number of tokens incorrect, expected %lu but got %lu",
//                gold_num_tokens, num_tokens);
//    }
//
//    int gold_allocs[] = {0, 0, 0, 0, 7, 1, 0, 0, 0};
//    for (int i=0; i < 9; i++) {
//        if (gold_allocs[i] != mgr->pools[i]->allocs) {
//            NEW_ERROR(80)
//            sprintf((char *) this_error->msg,
//                "pool size %lu -- %d allocated, expected %d", 
//                mgr->pools[i]->object_size, 
//                mgr->pools[i]->allocs, 
//                gold_allocs[i]);
//
//        }
//    }
//
//    NL_free_v_memmgr(&mgr); 
//
//    return errors;
//}
//
//error_info **tokenizer_test2(char **name, size_t *num_errors) {
//
//    error_info **errors = NULL;
//    *num_errors = 0;
//    *name = "tokenizer test2";
//
//    size_t gold_num_tokens = NL_PTB_TOK_BUFSIZE + 45;
//
//    size_t buf_size = 0;
//    for (int i = 1; i <= gold_num_tokens; i++) {
//        int d = 1;
//        size_t word_size = 2;
//        while (i / d > 0) {
//            word_size++;
//            d = d * 10;
//        } 
//        buf_size = buf_size + word_size;
//    }
//    printf("Allocating %lu\n", buf_size);
//    unsigned char *buf = malloc(sizeof(unsigned char) * buf_size);
//    buf_size = 0;
//    unsigned char **gold = malloc(sizeof(unsigned char *) * gold_num_tokens);
//
//    for (int i = 1; i <= gold_num_tokens; i++) {
//            int d = 1;
//            size_t word_size = 2;
//            while (i / d > 0) {
//                word_size++;
//                d = d * 10;
//            } 
//            if (i < gold_num_tokens) {
//                sprintf((char *)&buf[buf_size], "w%d ", i);
//                buf_size = buf_size + word_size;
//            } else {
//               // printf("HERE\n");
//                sprintf((char *)&buf[buf_size], "w%d", i);
//                buf_size = buf_size + word_size -1;
//            }
//           // printf("%s\n", buf);
//            gold[i-1] = malloc(sizeof(unsigned char) * word_size);
//            gold[i-1][word_size-1] = '\0';
//            sprintf((char *)gold[i-1], "w%d", i);
//           // printf("%s\n", gold[i-1]);
//    }
//    printf("buf-size = %lu\n", buf_size);
//    buf[buf_size] = '\0';
//    //printf("%s\n", buf);
//    
//    size_t num_tokens;
//    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
//    NL_span **spans = NL_tokenize_buf(
//            buf, strlen((char *)buf), &num_tokens, NULL, mgr);
//    if (num_tokens != gold_num_tokens) {
//        NEW_ERROR(80)
//        sprintf((char *) this_error->msg,
//                "Number of tokens incorrect, expected %lu but got %lu",
//                gold_num_tokens, num_tokens);
//    }
//
//    size_t tokens_bsize = sizeof(NL_span *) * num_tokens;
//    size_t tokens_bin = (int) log2((float) tokens_bsize);
//    if (1 << (tokens_bin) == tokens_bsize)
//        tokens_bin = tokens_bin - 1;
//
//    //printf("bsize = %lu, bin = %lu\n", tokens_bsize, tokens_bin);
//    int *gold_allocs = calloc(sizeof(int), mgr->max_pools);
//    gold_allocs[5] = gold_num_tokens;
//    gold_allocs[tokens_bin]++;
//
//    for (int i=0; i < mgr->max_pools; i++) {
//        if (gold_allocs[i] != mgr->pools[i]->allocs) {
//            NEW_ERROR(80)
//            sprintf((char *) this_error->msg,
//                "pool size %lu -- %d allocated, expected %d", 
//                mgr->pools[i]->object_size, 
//                mgr->pools[i]->allocs, 
//                gold_allocs[i]);
//        }
//    }
//    free(gold_allocs);
//
//    for (int i=0; i < num_tokens; i++) {
//        NL_free_span(&spans[i], mgr);
//    }
//    NL_deallocate_v_mem(mgr, (void **)&spans);
//
//
//    for (int i=0; i < mgr->max_pools; i++) {
//        if (0 != mgr->pools[i]->allocs) {
//            NEW_ERROR(80)
//            sprintf((char *) this_error->msg,
//                "pool size %lu -- %d allocated, expected %d", 
//                mgr->pools[i]->object_size, 
//                mgr->pools[i]->allocs, 
//                0);
//
//        }
//    }
//
//
//
//    NL_free_v_memmgr(&mgr); 
//    free(buf);
//    for (int i=0; i < gold_num_tokens; i++) {
//        free(gold[i]);
//    } 
//    free(gold);
//
//    return errors;
//}
//
//error_info **tokenizer_test3(char **name, size_t *num_errors) {
//
//    error_info **errors = NULL;
//    *num_errors = 0;
//    *name = "tokenizer test3";
//
//    size_t gold_num_tokens = NL_PTB_TOK_BUFSIZE + 1;
//
//    size_t buf_size = 0;
//    for (int i = 1; i < gold_num_tokens; i++) {
//        int d = 1;
//        size_t word_size = 2;
//        while (i / d > 0) {
//            word_size++;
//            d = d * 10;
//        } 
//        buf_size = buf_size + word_size;
//    }
//    buf_size += 2;
//    printf("Allocating %lu\n", buf_size);
//    unsigned char *buf = malloc(sizeof(unsigned char) * buf_size);
//    buf_size = 0;
//    unsigned char **gold = malloc(sizeof(unsigned char *) * gold_num_tokens);
//
//    for (int i = 1; i < gold_num_tokens; i++) {
//            int d = 1;
//            size_t word_size = 2;
//            while (i / d > 0) {
//                word_size++;
//                d = d * 10;
//            } 
//                sprintf((char *)&buf[buf_size], "w%d ", i);
//                buf_size = buf_size + word_size;
//            //printf("%s\n", buf);
//            gold[i-1] = malloc(sizeof(unsigned char) * word_size);
//            gold[i-1][word_size-1] = '\0';
//            sprintf((char *)gold[i-1], "w%d", i);
//            //printf("%s\n", gold[i-1]);
//    }
//    sprintf((char *)&buf[buf_size], "(");
//    buf_size = buf_size + 2;
//    gold[gold_num_tokens-1] = malloc(sizeof(unsigned char) * 2);
//    gold[gold_num_tokens-1][0] = '(';
//    gold[gold_num_tokens-1][1] = '\0';
//    
//    printf("buf-size = %lu\n", buf_size);
//    //buf[buf_size] = '\0';
//    //printf("%s\n", buf);
//    
//    size_t num_tokens;
//    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
//    NL_span **spans = NL_tokenize_buf(
//            buf, strlen((char *)buf), &num_tokens, NULL, mgr);
//    if (num_tokens != gold_num_tokens) {
//        NEW_ERROR(80)
//        sprintf((char *) this_error->msg,
//                "Number of tokens incorrect, expected %lu but got %lu",
//                gold_num_tokens, num_tokens);
//    }
////
//    size_t tokens_bsize = sizeof(NL_span *) * num_tokens;
//    size_t tokens_bin = (int) log2((float) tokens_bsize);
//    if (1 << (tokens_bin) == tokens_bsize)
//        tokens_bin = tokens_bin - 1;
//
//    printf("bsize = %lu, bin = %lu\n", tokens_bsize, tokens_bin);
//    int *gold_allocs = calloc(sizeof(int), mgr->max_pools);
//    gold_allocs[5] = gold_num_tokens;
//    gold_allocs[tokens_bin]++;
//
//    for (int i=0; i < mgr->max_pools; i++) {
//        if (gold_allocs[i] != mgr->pools[i]->allocs) {
//            NEW_ERROR(80)
//            sprintf((char *) this_error->msg,
//                "pool size %lu -- %d allocated, expected %d", 
//                mgr->pools[i]->object_size, 
//                mgr->pools[i]->allocs, 
//                gold_allocs[i]);
//        }
//    }
//    free(gold_allocs);
//
//    for (int i=0; i < num_tokens; i++) {
//        NL_free_span(&spans[i], mgr);
//    }
//    NL_deallocate_v_mem(mgr, (void **)&spans);
//
//
//
//    for (int i=0; i < mgr->max_pools; i++) {
//        if (0 != mgr->pools[i]->allocs) {
//            NEW_ERROR(80)
//            sprintf((char *) this_error->msg,
//                "pool size %lu -- %d allocated, expected %d", 
//                mgr->pools[i]->object_size, 
//                mgr->pools[i]->allocs, 
//                0);
//
//        }
//    }
//
//
//
//    NL_free_v_memmgr(&mgr); 
//    free(buf);
//    for (int i=0; i < gold_num_tokens; i++) {
//        free(gold[i]);
//    } 
//    free(gold);
//
//    return errors;
//}

#define TOKEN_TEST                                                            \
  NL_annotations *ann = NL_tokenize_buf(&buffer, cfg, mgr);                   \
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

error_info **plangs_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "plangs test";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 6;
    NL_buffer buffer = {
        (unsigned char *)"C++ c++ C# c# F# f#",
        strlen("C++ c++ C# c# F# f#")
    };
    unsigned char *gold[] = {
        (unsigned char *) "C++",
        (unsigned char *) "c++",
        (unsigned char *) "C#",
        (unsigned char *) "c#",
        (unsigned char *) "F#",
        (unsigned char *) "f#"
    }; 

    TOKEN_TEST

    return errors;
}

error_info **assims_no_split_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "assims_no_split_test";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);
    cfg->split_assimilations = 0;

    size_t gold_num_tokens = 6;
    NL_buffer buffer = {
        (unsigned char *) "cannot gonna gotta lemme gimme wanna",
        strlen("cannot gonna gotta lemme gimme wanna")
    };
    unsigned char *gold[] = {
        (unsigned char *) "cannot",
        (unsigned char *) "gonna",
        (unsigned char *) "gotta",
        (unsigned char *) "lemme",
        (unsigned char *) "gimme",
        (unsigned char *) "wanna"
    }; 

    TOKEN_TEST

    return errors;
}

error_info **assims_split_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "assims_split_test";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);
    cfg->split_assimilations = 1;

    size_t gold_num_tokens = 12;
    NL_buffer buffer = {
        (unsigned char *) "cannot gonna gotta lemme gimme wanna",
        strlen("cannot gonna gotta lemme gimme wanna")
    };
    unsigned char *gold[] = {
        (unsigned char *) "can",
        (unsigned char *) "not",
        (unsigned char *) "gon",
        (unsigned char *) "na",
        (unsigned char *) "got",
        (unsigned char *) "ta",
        (unsigned char *) "lem",
        (unsigned char *) "me",
        (unsigned char *) "gim",
        (unsigned char *) "me",
        (unsigned char *) "wan",
        (unsigned char *) "na"
    }; 

    TOKEN_TEST

    return errors;
}

error_info **assims2_no_split_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "assims2_no_split_test";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);
    cfg->split_assimilations = 0;

    size_t gold_num_tokens = 2;
    NL_buffer buffer = {
        (unsigned char *) "'twas 'tis",
        strlen("'twas 'tis")
    };
    unsigned char *gold[] = {
        (unsigned char *) "'twas",
        (unsigned char *) "'tis",
    }; 

    TOKEN_TEST

    return errors;
}

error_info **assims2_split_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "assims2_split_test";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);
    cfg->split_assimilations = 1;

    size_t gold_num_tokens = 4;
    NL_buffer buffer = {
        (unsigned char *) "'twas 'tis",
        strlen("'twas 'tis")
    };
    unsigned char *gold[] = {
        (unsigned char *) "'t",
        (unsigned char *) "was",
        (unsigned char *) "'t",
        (unsigned char *) "is",
    }; 

    TOKEN_TEST

    return errors;
}





