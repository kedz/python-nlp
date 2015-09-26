#ifndef H_NL_WS_TOKENIZER
#define H_NL_WS_TOKENIZER

#include "nlp/mem_manager.h"
#include "nlp/types.h"
#include "nlp/annotations.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

NL_annotations *NL_ws_tokenize(NL_buffer *buffer, NL_v_memmgr *mgr);
#endif
