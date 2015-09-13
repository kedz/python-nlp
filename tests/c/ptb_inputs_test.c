#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "nlp/mem_manager.h"
#include "nlp/tokenizer.h"

typedef struct error_info {
    unsigned char *test_name;
    unsigned char *msg;
} error_info;


#define NEW_ERROR                                                   \
    *num_errors += 1;                                               \
    errors = realloc(errors, *num_errors * sizeof(error_info *));   \
    errors[*num_errors -1] = malloc(sizeof(error_info));            \
    errors[*num_errors-1]->msg = malloc(sizeof(char) * 80);         \
    error_info *this_error = errors[*num_errors -1];                \

#define TOKEN_TEST                                                            \
  NL_v_memmgr *mgr = NL_new_v_memmgr(256);                                    \
  size_t *num_tokens = NL_allocate_mem_size(mgr, sizeof(size_t));             \
  *num_tokens = 0;                                                            \
  NL_span **tokens = NL_tokenize_buf(buf, buf_len, num_tokens, NULL, mgr);    \
  for (int i=0; i < *num_tokens; i++) {                                       \
      if (i < gold_num_tokens) {                                              \
          unsigned char *token = NULL;                                        \
          size_t token_length = 0; \
        if (tokens[i]->label_length > 0) { \
            token = tokens[i]->label; \
            token_length = tokens[i]->label_length; \
        } else { \
            token = tokens[i]->start; \
            token_length = tokens[i]->length; \
        } \
        unsigned char *gold_token = gold[i]; \
        size_t gold_length = strlen((char *) gold_token); \
        if (token_length != gold_length  \
                    || memcmp(token, gold_token, token_length) != 0) { \
 \
            *num_errors += 1;              \
            errors = realloc(errors, *num_errors * sizeof(error_info *)); \
            errors[*num_errors -1] = malloc(sizeof(error_info));    \
            error_info *this_error = errors[*num_errors -1];  \
            this_error->msg = NULL; \
 \
            size_t cpy_s1 = strlen("Tokenizer returned \""); \
            size_t cpy_s2 = strlen("\" but expected \""); \
            size_t cpy_s3 = strlen("\"."); \
            size_t msg_size = cpy_s1 + cpy_s2 + cpy_s3  \
                + token_length + gold_length + 1; \
            this_error->msg = malloc(sizeof(char) * msg_size); \
            this_error->msg[msg_size-1] = '\0'; \
            memcpy( \
                    this_error->msg,  \
                    "Tokenizer returned \"", \
                    cpy_s1); \
            memcpy( \
                    &this_error->msg[cpy_s1], \
                    token, \
                    token_length); \
 \
            memcpy( \
                    &this_error->msg[cpy_s1 + token_length], \
                    "\" but expected \"", \
                    cpy_s2); \
 \
            memcpy( \
                    &this_error->msg[cpy_s1+token_length+cpy_s2], \
                    gold_token, \
                    gold_length); \
            memcpy( \
                    &this_error->msg[ \
                        cpy_s1+token_length+cpy_s2+gold_length], \
                    "\".", \
                    cpy_s3); \
        } \
    } \
    NL_free_span(&tokens[i], mgr); \
} \
NL_deallocate_v_mem(mgr, tokens); \
 \
if (*num_tokens != gold_num_tokens) { \
    *num_errors += 1;              \
    errors = realloc(errors, *num_errors * sizeof(error_info *)); \
    errors[*num_errors -1] = malloc(sizeof(error_info));    \
    error_info *this_error = errors[*num_errors -1];  \
    this_error->msg = malloc(sizeof(char *) *200); \
 \
    sprintf( \
        (char *) this_error->msg,  \
        "Tokenizer returned %lu tokens, should be %lu.", \
        *num_tokens, gold_num_tokens); \
 \
} \
 \
    NL_deallocate_v_mem(mgr, num_tokens); \
 \
    int pool_size = 2; \
    for (int i=0; i < mgr->max_pools; i++) { \
        unsigned int allocs = mgr->pools[i]->allocs; \
        if (allocs > 0) { \
            NEW_ERROR \
            sprintf( \
                (char *) this_error->msg,  \
                "Memory manager leak %d allocations in pool size %d.", \
                allocs, pool_size); \
        } \
        pool_size = pool_size * 2; \
 \
    } \
    NL_free_v_memmgr(&mgr); \



error_info **ptb_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test1";

    size_t gold_num_tokens = 5;
    unsigned char *buf = (unsigned char *)"This is a sentence.";
    unsigned char *gold[] = {
        (unsigned char *)"This", 
        (unsigned char *)"is", 
        (unsigned char *)"a", 
        (unsigned char *)"sentence", 
        (unsigned char *)".",
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test2";

    size_t gold_num_tokens = 12;
    unsigned char *buf = (unsigned char *)
        "U.S. insurance: Conseco acquires Kemper Corp. \n"
        "</HEADLINE>\n<P>\nU.S insurance";
    unsigned char *gold[] = {
        (unsigned char*)"U.S.",
        (unsigned char*)"insurance",
        (unsigned char*)":",
        (unsigned char*)"Conseco",
        (unsigned char*)"acquires",
        (unsigned char*)"Kemper",
        (unsigned char*)"Corp.",
        (unsigned char*)".",
        (unsigned char*)"</HEADLINE>",
        (unsigned char*)"<P>",
        (unsigned char*)"U.S",
        (unsigned char*)"insurance"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test3(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test3";

    size_t gold_num_tokens = 22;
    unsigned char *buf = (unsigned char *)
        "Based in Eugene,Ore., PakTech needs a new distributor after "
        "Sydney-based Creative Pack Pty. Ltd. went into voluntary "
        "administration.";
    unsigned char *gold[] = {
        (unsigned char*)"Based",
        (unsigned char*)"in",
        (unsigned char*)"Eugene",
        (unsigned char*)",",
        (unsigned char*)"Ore.",
        (unsigned char*)",",
        (unsigned char*)"PakTech",
        (unsigned char*)"needs",
        (unsigned char*)"a",
        (unsigned char*)"new",
        (unsigned char*)"distributor",
        (unsigned char*)"after",
        (unsigned char*)"Sydney-based",
        (unsigned char*)"Creative",
        (unsigned char*)"Pack",
        (unsigned char*)"Pty.",
        (unsigned char*)"Ltd.",
        (unsigned char*)"went",
        (unsigned char*)"into",
        (unsigned char*)"voluntary",
        (unsigned char*)"administration",
        (unsigned char*)"." 
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test4(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test4";

    size_t gold_num_tokens = 12;
    unsigned char *buf = (unsigned char *)
        "The Iron Age (ca. 1300 – ca. 300 BC).";
    unsigned char *gold[] = {
        (unsigned char*)"The",
        (unsigned char*)"Iron",
        (unsigned char*)"Age",
        (unsigned char*)"-LRB-",
        (unsigned char*)"ca.",
        (unsigned char*)"1300",
        (unsigned char*)"--",
        (unsigned char*)"ca.",
        (unsigned char*)"300",
        (unsigned char*)"BC",
        (unsigned char*)"-RRB-",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test5(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test5";

    size_t gold_num_tokens = 3;
    unsigned char *buf = (unsigned char *)
        "Indo\xC2\xADnesian ship\xC2\xADping \xC2\xAD";
    unsigned char *gold[] = {
        (unsigned char*)"Indonesian",
        (unsigned char*)"shipping",
        (unsigned char*)"-"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

#define num_tests 5
error_info** (*tests[num_tests]) (char **, size_t*) = {
    ptb_test1, 
    ptb_test2,
    ptb_test3,
    ptb_test4,
    ptb_test5,
    
};

int main(int argc, char *argv[]) {

    char *usage = "ptb_inputs_test [-v] [-h]\n"
        "\t-v\tverbose, print error messages\n"
        "\t-h\tdisplay this message\n";

    int verbose = 0;

    for (int i=0; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("%s", usage);
            exit(0);
        }

    }

    for (int i=0; i < num_tests; i++) {
        char **name = malloc(sizeof(char *));
        error_info **errors = NULL;
        size_t num_errors = 0;
        errors = (*tests[i]) (name, &num_errors);
        char *status;
        if (num_errors == 0) {
            status = "OK";
        } else {
            status = "FAIL";
        }
        printf("%s ... %s\n", *name, status);
        for (int e=0; e<num_errors; e++) {
            if (verbose == 1) {
                printf("Error %d: %s\n", e, errors[e]->msg);
            }
            free(errors[e]->msg);
            free(errors[e]);
        }
        free(errors);
        free(name);
    }
}
