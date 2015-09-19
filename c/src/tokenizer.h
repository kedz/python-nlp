#ifndef H_NL_PTB_TOKENIZER
#define H_NL_PTB_TOKENIZER

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
//       strictTreebank3,
    //    //americanize, normalizeSpace,
//       normalizeFractions,
    //    short int tokenizeNLs, 
    //
//       normalizeAmpersandEntity, normalizeCurrency, 
//       normalizeParentheses, normalizeOtherBrackets,
//       quotes_latex, quotes_unicode, quotes_ascii,
//       ellipsis_ptb3, ellipsis_unicode,
//       ptb3Dashes, escapeForwardSlashAsterisk,
//       splitAssimilations;
} NL_PTBTokConfig;


typedef struct __token_list {
    struct __token_list *next;
    NL_span **tokens;
} __token_list;

NL_PTBTokConfig *NL_new_PTB_tokenizer_config(NL_v_memmgr* mgr);

NL_span **NL_tokenize_buf(
    unsigned char *buf, size_t buf_len, size_t *num_tokens, 
    NL_PTBTokConfig *cfg, NL_v_memmgr *mgr);
void uni_right_quote(unsigned char *p, size_t buf_length, unsigned char *cpy);

#define BUFSIZE 64
#define NL_PTB_TOK_BUFSIZE 64

#endif
