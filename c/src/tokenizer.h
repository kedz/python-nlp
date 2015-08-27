#include "document.h"
#include "mem_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NL_PTBTokConfig {
    short int tokenizeNLs, americanize, normalizeSpace,
       normalizeAmpersandEntity, normalizeCurrency, normalizeFractions,
       normalizeParentheses, normalizeOtherBrackets,
       quotes_latex, quotes_unicode, quotes_ascii,
       ellipsis_ptb3, ellipsis_unicode,
       ptb3Dashes, escapeForwardSlashAsterisk, strictTreebank3,
       splitAssimilations;
} NL_PTBTokConfig;


typedef struct __token_list {
    struct __token_list *next;
    NL_span **tokens;
} __token_list;



NL_span **NL_tokenize_buf(
    unsigned char *buf, size_t buf_len, size_t *num_tokens, 
    NL_PTBTokConfig *cfg, NL_v_memmgr *mgr);
