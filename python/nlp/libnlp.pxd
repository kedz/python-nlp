cdef extern from "mem_manager.h":
    ctypedef struct NL_v_memmgr:
        pass

    cdef NL_v_memmgr *NL_new_v_memmgr(size_t block_size);
    cdef void NL_free_v_memmgr(NL_v_memmgr **);

    cdef void NL_deallocate_v_mem(NL_v_memmgr *mgr, void * data);

cdef extern from "document.h":
    ctypedef unsigned char *NL_label

    ctypedef struct NL_document:
        pass
    ctypedef struct NL_span:
        unsigned char *start
        size_t length
        NL_label label
        size_t label_length

    cdef void NL_free_span(NL_span **span, NL_v_memmgr *manager);


cdef extern from "tokenizer.h":
    ctypedef enum NL_normalize_quotes:
        QUOTES_NONE, QUOTES_LATEX, QUOTES_UNICODE, QUOTES_ASCII

    ctypedef struct NL_PTBTokConfig:
        int split_assimilations
        int normalize_dashes
        int normalize_amp
        NL_normalize_quotes normalize_quotes

    cdef NL_span **NL_tokenize_buf(
        unsigned char *buf, size_t buf_len, size_t *num_tokens, 
        NL_PTBTokConfig *cfg, NL_v_memmgr *mgr);

cdef class MemoryManagerWrapper(object):
    cdef NL_v_memmgr *_mgr

cdef class PTBTokenizerConfigWrapper(object):
    cdef NL_PTBTokConfig *_cfg



cdef MemoryManagerWrapper memmgr
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg
