#ifndef H_NL_PTB_TOKENIZER
#define H_NL_PTB_TOKENIZER

#include "document.h"
#include "mem_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer_utils.h"

#include "nlp/types.h"
#include "nlp/annotations.h"


typedef enum NL_normalize_quotes {
    QUOTES_NONE, 
    QUOTES_LATEX, 
    QUOTES_UNICODE, 
    QUOTES_ASCII} NL_normalize_quotes; 

typedef enum NL_normalize_ellipsis {
    ELLIPSIS_NONE,
    ELLIPSIS_PTB3,
    ELLIPSIS_UNICODE } NL_normalize_ellipsis; 

typedef struct NL_PTBTokConfig {
    int split_assimilations; // "cannot" => "can" "not"
    int normalize_dashes; 
    int normalize_amp; 
    NL_normalize_quotes normalize_quotes;
    int tokenize_newlines;
    int normalize_currency;
    int escape_forward_slash_asterisk;
    NL_normalize_ellipsis normalize_ellipsis;
    int normalize_parentheses;
    int normalize_brackets;
    int strict_ptb3;
    int normalize_spaces;
    int normalize_fractions;
} NL_PTBTokConfig;

NL_PTBTokConfig *NL_new_PTB_tokenizer_config(NL_v_memmgr* mgr);

NL_annotations *NL_tokenize_buf(NL_buffer *buffer, NL_PTBTokConfig *cfg, 
        NL_v_memmgr *mgr);

#endif
