#include "document.h"
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

void NLPC_tokenize_document(NLPC_document *d, NL_PTBTokConfig *config);
