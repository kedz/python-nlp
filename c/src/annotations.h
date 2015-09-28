#ifndef H_NL_ANNOTATIONS
#define H_NL_ANNOTATIONS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "nlp/types.h"
#include "nlp/mem_manager.h"

#define NL_BASE_ANN_LIST_SIZE 16

NL_annotations *NL_new_bspan_annotations(NL_v_memmgr *mgr);
NL_annotations *NL_new_sspan_annotations(NL_v_memmgr *mgr);

void NL_add_bspan(NL_v_memmgr *mgr, NL_annotations *ann, 
        unsigned char *bytes, size_t size, void *data, NL_flags flags);

void NL_add_sspan(NL_v_memmgr *mgr, NL_annotations *ann, 
        size_t span_id, size_t size, void *data, NL_flags flags);


NL_bspan *NL_get_bspan(NL_annotations *ann, size_t index);
NL_sspan *NL_get_sspan(NL_annotations *ann, size_t index);

void NL_deallocate_bspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann);
void NL_deallocate_sspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann);

NL_string *NL_new_string(NL_v_memmgr *mgr, size_t size);

#endif
