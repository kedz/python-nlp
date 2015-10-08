#ifndef H_NL_CONLL_READER
#define H_NL_CONLL_READER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nlp/types.h"
#include "nlp/mem_manager.h"
#include "nlp/annotations.h"

NL_doc *NL_read_conll_buffer(NL_buffer *buffer, NL_v_memmgr *mgr);

#endif
