#ifndef H_NL_SENT_TOKENIZER
#define H_NL_SENT_TOKENIZER

#include <stdlib.h>
#include "nlp/types.h"
#include "nlp/mem_manager.h"
#include "nlp/annotations.h"

NL_annotations *NL_sentence_tokenize(NL_annotations* tokens, 
        NL_v_memmgr *mgr);

#define NL_SENT_END_FLAG 0x02

#endif
