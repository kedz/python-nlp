#ifndef H_NL_VOCAB
#define H_NL_VOCAB

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "nlp/types.h"
#include "nlp/mem_manager.h"
#include "nlp/MurmurHash3.h"

static const size_t NL_PRIMES[] = {127997, 255989, 511997, 1023991}; 
static const size_t NL_NUM_PRIMES = 4;

#define NL_VOCAB_MEM_ERROR -1
#define NL_VOCAB_NOT_FOUND 0
#define NL_VOCAB_FOUND 1
#define NL_VOCAB_INSERT 2


NL_vocab *NL_new_vocab(NL_v_memmgr *mgr);
void NL_deallocate_vocab(NL_v_memmgr *mgr, NL_vocab **vocab);

int NL_get_string_id(NL_v_memmgr *mgr, NL_vocab *vocab,
        NL_string* string, size_t *id);

//void NL_add_bspan(NL_v_memmgr *mgr, NL_annotations *ann, 
//        unsigned char *bytes, size_t size, void *data, NL_flags flags);
//
//void NL_add_sspan(NL_v_memmgr *mgr, NL_annotations *ann, 
//        size_t span_id, size_t size, void *data, NL_flags flags);
//
//NL_bspan *NL_get_bspan(NL_annotations *ann, size_t index);
//NL_sspan *NL_get_sspan(NL_annotations *ann, size_t index);
//
//void NL_deallocate_bspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann);
//void NL_deallocate_sspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann);
//
//NL_string *NL_new_string(NL_v_memmgr *mgr, size_t size);
//
#endif
