#include "conll_reader_tests.h"

error_info **conll_reader_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "conll reader test1";

    unsigned char * bytes = (unsigned char *)
"Xinhua  NNP\n\
News    NNP\n\
Agency  NNP\n\
,   ,\n\
Beijing NNP\n\
,   ,\n\
January NNP\n\
3   CD\n\
,   ,\n\
by  IN\n\
wire    NN\n\
\n\
Recently    RB\n\
,   ,\n\
China   NNP\n\
advocated   VBD\n\
using   VBG\n\
the DT\n\
textile JJ\n\
industry    NN\n\
as  IN\n\
a   DT\n\
point   NN\n\
of  IN\n\
breakthrough    NN\n\
in  IN\n\
state   NN\n\
-   HYPH\n\
owned   VBN\n\
enterprise  NN\n\
reform  NN\n\
and CC\n\
problem NN\n\
resolution  NN\n\
.   .\n\
\n";

    size_t num_gold_sents = 2;
    size_t num_gold = 34;
    size_t gold_sizes[] = {11, 23};
    size_t gold_ids[] = {0, 11};
    char *gold_tokens[] = { 
        "Xinhua", "News", "Agency", ",", "Beijing", ",", "January", "3", ",",
        "by", "wire", "Recently", ",", "China", "advocated", "using", "the",
        "textile", "industry", "as", "a", "point", "of", "breakthrough", "in",
        "state", "-", "owned", "enterprise", "reform", "and", "problem",
        "resolution", ".",
    };

    char *gold_pos[] = { 
        "NNP", "NNP", "NNP", ",", "NNP", ",", "NNP", "CD", ",", "IN", "NN", 
        "RB", ",", "NNP",
        "VBD", "VBG", "DT", "JJ", "NN", "IN", "DT", "NN", "IN", "NN", "IN", 
        "NN", "HYPH", "VBN", "NN", "NN","CC", "NN", "NN", "."
    };

    NL_buffer buffer = {bytes, strlen((char *) bytes)};
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_doc *doc = NL_read_conll_buffer(&buffer, mgr);

    if (doc == NULL) {
        NEW_ERROR(80)
        sprintf(
            (char *) this_error->msg, "NL_read_conll_buffer returned NULL!");
    } else {
        if (doc->tokens == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->tokens is NULL!");
        } else {
            if (doc->tokens->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->tokens->size is %lu, expected %lu",
                    doc->tokens->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->tokens, i);
                    if (span->size != strlen((char *) gold_tokens[i]) ||
                        memcmp(span->bytes, gold_tokens[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "Tokenizer error!");
                        
                    } 

                }
            }
        }
        if (doc->pos_tags == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->pos_tags is NULL!");
        } else {
            if (doc->pos_tags->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->pos_tags->size is %lu, expected %lu",
                    doc->pos_tags->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->pos_tags, i);
                    if (span->size != strlen((char *) gold_pos[i]) ||
                        memcmp(span->bytes, gold_pos[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "POS tag error!");
                    } 
                }
            }
        }

        if (doc->sentences == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->sentences is NULL!");
        } else {
            if (doc->sentences->size != num_gold_sents) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->sentences->size is %lu, expected %lu",
                    doc->sentences->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold_sents; i++) {
                    NL_sspan *span = NL_get_sspan(doc->sentences, i);
                    if (span->span_id != gold_ids[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence starts at token %lu, expected %lu",
                            span->span_id, gold_ids[i]);
                    }
                    if (span->size != gold_sizes[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence has size %lu, expected %lu",
                            span->size, gold_sizes[i]);
                    }
                }
            }
        }
    }

    NL_free_v_memmgr(&mgr);

    return errors;

}

error_info **conll_reader_test2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "conll reader test2";

    unsigned char * bytes = (unsigned char *)
"Xinhua  NNP\n\
News    NNP\n\
Agency  NNP\n\
,   ,\n\
Beijing NNP\n\
,   ,\n\
January NNP\n\
3   CD\n\
,   ,\n\
by  IN\n\
wire    NN\n\
\n\
Recently    RB\n\
,   ,\n\
China   NNP\n\
advocated   VBD\n\
using   VBG\n\
the DT\n\
textile JJ\n\
industry    NN\n\
as  IN\n\
a   DT\n\
point   NN\n\
of  IN\n\
breakthrough    NN\n\
in  IN\n\
state   NN\n\
-   HYPH\n\
owned   VBN\n\
enterprise  NN\n\
reform  NN\n\
and CC\n\
problem NN\n\
resolution  NN\n\
.   .\n";

    size_t num_gold_sents = 2;
    size_t num_gold = 34;
    size_t gold_sizes[] = {11, 23};
    size_t gold_ids[] = {0, 11};
    char *gold_tokens[] = { 
        "Xinhua", "News", "Agency", ",", "Beijing", ",", "January", "3", ",",
        "by", "wire", "Recently", ",", "China", "advocated", "using", "the",
        "textile", "industry", "as", "a", "point", "of", "breakthrough", "in",
        "state", "-", "owned", "enterprise", "reform", "and", "problem",
        "resolution", ".",
    };

    char *gold_pos[] = { 
        "NNP", "NNP", "NNP", ",", "NNP", ",", "NNP", "CD", ",", "IN", "NN", 
        "RB", ",", "NNP",
        "VBD", "VBG", "DT", "JJ", "NN", "IN", "DT", "NN", "IN", "NN", "IN", 
        "NN", "HYPH", "VBN", "NN", "NN","CC", "NN", "NN", "."
    };

    NL_buffer buffer = {bytes, strlen((char *) bytes)};
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_doc *doc = NL_read_conll_buffer(&buffer, mgr);

    if (doc == NULL) {
        NEW_ERROR(80)
        sprintf(
            (char *) this_error->msg, "NL_read_conll_buffer returned NULL!");
    } else {
        if (doc->tokens == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->tokens is NULL!");
        } else {
            if (doc->tokens->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->tokens->size is %lu, expected %lu",
                    doc->tokens->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->tokens, i);
                    if (span->size != strlen((char *) gold_tokens[i]) ||
                        memcmp(span->bytes, gold_tokens[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "Tokenizer error!");
                        
                    } 

                }
            }
        }
        if (doc->pos_tags == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->pos_tags is NULL!");
        } else {
            if (doc->pos_tags->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->pos_tags->size is %lu, expected %lu",
                    doc->pos_tags->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->pos_tags, i);
                    if (span->size != strlen((char *) gold_pos[i]) ||
                        memcmp(span->bytes, gold_pos[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "POS tag error!");
                    } 
                }
            }
        }

        if (doc->sentences == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->sentences is NULL!");
        } else {
            if (doc->sentences->size != num_gold_sents) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->sentences->size is %lu, expected %lu",
                    doc->sentences->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold_sents; i++) {
                    NL_sspan *span = NL_get_sspan(doc->sentences, i);
                    if (span->span_id != gold_ids[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence starts at token %lu, expected %lu",
                            span->span_id, gold_ids[i]);
                    }
                    if (span->size != gold_sizes[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence has size %lu, expected %lu",
                            span->size, gold_sizes[i]);
                    }
                }
            }
        }
    }

    NL_free_v_memmgr(&mgr);

    return errors;

}

error_info **conll_reader_test3(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "conll reader test3";

    unsigned char * bytes = (unsigned char *)
"Xinhua  NNP\n\
News    NNP\n\
Agency  NNP\n\
,   ,\n\
Beijing NNP\n\
,   ,\n\
January NNP\n\
3   CD\n\
,   ,\n\
by  IN\n\
wire    NN\n\
\n\
Recently    RB\n\
,   ,\n\
China   NNP\n\
advocated   VBD\n\
using   VBG\n\
the DT\n\
textile JJ\n\
industry    NN\n\
as  IN\n\
a   DT\n\
point   NN\n\
of  IN\n\
breakthrough    NN\n\
in  IN\n\
state   NN\n\
-   HYPH\n\
owned   VBN\n\
enterprise  NN\n\
reform  NN\n\
and CC\n\
problem NN\n\
resolution  NN\n\
.   .";

    size_t num_gold_sents = 2;
    size_t num_gold = 34;
    size_t gold_sizes[] = {11, 23};
    size_t gold_ids[] = {0, 11};
    char *gold_tokens[] = { 
        "Xinhua", "News", "Agency", ",", "Beijing", ",", "January", "3", ",",
        "by", "wire", "Recently", ",", "China", "advocated", "using", "the",
        "textile", "industry", "as", "a", "point", "of", "breakthrough", "in",
        "state", "-", "owned", "enterprise", "reform", "and", "problem",
        "resolution", ".",
    };

    char *gold_pos[] = { 
        "NNP", "NNP", "NNP", ",", "NNP", ",", "NNP", "CD", ",", "IN", "NN", 
        "RB", ",", "NNP",
        "VBD", "VBG", "DT", "JJ", "NN", "IN", "DT", "NN", "IN", "NN", "IN", 
        "NN", "HYPH", "VBN", "NN", "NN","CC", "NN", "NN", "."
    };

    NL_buffer buffer = {bytes, strlen((char *) bytes)};
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_doc *doc = NL_read_conll_buffer(&buffer, mgr);

    if (doc == NULL) {
        NEW_ERROR(80)
        sprintf(
            (char *) this_error->msg, "NL_read_conll_buffer returned NULL!");
    } else {
        if (doc->tokens == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->tokens is NULL!");
        } else {
            if (doc->tokens->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->tokens->size is %lu, expected %lu",
                    doc->tokens->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->tokens, i);
                    if (span->size != strlen((char *) gold_tokens[i]) ||
                        memcmp(span->bytes, gold_tokens[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "Tokenizer error!");
                        
                    } 

                }
            }
        }
        if (doc->pos_tags == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->pos_tags is NULL!");
        } else {
            if (doc->pos_tags->size != num_gold) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->pos_tags->size is %lu, expected %lu",
                    doc->pos_tags->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold; i++) {
                    NL_bspan *span = NL_get_bspan(doc->pos_tags, i);
                    if (span->size != strlen((char *) gold_pos[i]) ||
                        memcmp(span->bytes, gold_pos[i], span->size)!= 0) {

                        NEW_ERROR(80)
                        sprintf(
                            (char *) this_error->msg, 
                            "POS tag error!");
                    } 
                }
            }
        }

        if (doc->sentences == NULL) {
            NEW_ERROR(80)
            sprintf(
                (char *) this_error->msg, 
                "doc->sentences is NULL!");
        } else {
            if (doc->sentences->size != num_gold_sents) {
                NEW_ERROR(80)
                sprintf(
                    (char *) this_error->msg, 
                    "doc->sentences->size is %lu, expected %lu",
                    doc->sentences->size, num_gold);
            } else {
                for (size_t i=0; i < num_gold_sents; i++) {
                    NL_sspan *span = NL_get_sspan(doc->sentences, i);
                    if (span->span_id != gold_ids[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence starts at token %lu, expected %lu",
                            span->span_id, gold_ids[i]);
                    }
                    if (span->size != gold_sizes[i]) {
                        NEW_ERROR(80)
                        sprintf((char *) this_error->msg,
                            "sentence has size %lu, expected %lu",
                            span->size, gold_sizes[i]);
                    }
                }
            }
        }
    }

    NL_free_v_memmgr(&mgr);

    return errors;

}
