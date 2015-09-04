#include "document.h"
#include "mem_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer_utils.h"


typedef enum NL_normalize_quotes {
    QUOTES_NONE, 
    QUOTES_LATEX, 
    QUOTES_UNICODE, 
    QUOTES_ASCII} NL_normalize_quotes; 

typedef struct NL_PTBTokConfig {
    int split_assimilations; // "cannot" => "can" "not"
    int normalize_dashes; 
    int normalize_amp; 
    NL_normalize_quotes normalize_quotes;
    //    short int tokenizeNLs, americanize, normalizeSpace,
//       normalizeAmpersandEntity, normalizeCurrency, normalizeFractions,
//       normalizeParentheses, normalizeOtherBrackets,
//       quotes_latex, quotes_unicode, quotes_ascii,
//       ellipsis_ptb3, ellipsis_unicode,
//       ptb3Dashes, escapeForwardSlashAsterisk, strictTreebank3,
//       splitAssimilations;
} NL_PTBTokConfig;


typedef struct __token_list {
    struct __token_list *next;
    NL_span **tokens;
} __token_list;



NL_span **NL_tokenize_buf(
    unsigned char *buf, size_t buf_len, size_t *num_tokens, 
    NL_PTBTokConfig *cfg, NL_v_memmgr *mgr);
void uni_right_quote(unsigned char *p, size_t buf_length, unsigned char *cpy);
