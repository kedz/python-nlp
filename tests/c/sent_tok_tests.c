#include "sent_tok_tests.h"

error_info **sent_tokenizer_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "sent tok test1";


    unsigned char *buf = (unsigned char *) 
        "This is a sentence. Also this! Whoa?!";
    size_t num_tokens;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_span **tokens = NL_tokenize_buf(
            buf, strlen((char *)buf), &num_tokens, NULL, mgr);
    NL_sentence **sentences = NL_sentence_tokenize(tokens, num_tokens);

    if (sentences == NULL) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Sentence tokenizer returned NULL.");

    }

    return errors;
}
