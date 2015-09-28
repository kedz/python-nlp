#include "nlp/tokenizer/sentence_tokenizer.h"

NL_annotations *NL_sentence_tokenize(NL_annotations *tokens, 
        NL_v_memmgr *mgr) {

    NL_annotations *sents = NL_new_sspan_annotations(mgr);
    size_t start = 0;
    NL_bspan *tok;
    size_t size;
    size_t j;
    for (size_t i=0; i < tokens->size; i++) {
        tok = NL_get_bspan(tokens, i);
        if (tok->flags & NL_SENT_END_FLAG) {
    
            j = i + 1;
            while (j < tokens->size && NL_get_bspan(tokens, j)->flags & NL_SENT_INC)
                j++;

            size = j - start;
            NL_add_sspan(mgr, sents, start, size, NULL, 0);
            start = j;
            i = j - 1;

        }
    }
    if (start < tokens->size) {
        NL_add_sspan(mgr, sents, start, tokens->size - start, NULL, 0);
    } 
    
    return sents;
}


