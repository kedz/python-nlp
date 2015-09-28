from cpython.buffer cimport PyBUF_SIMPLE, PyObject_CheckBuffer, \
    PyObject_GetBuffer, PyBuffer_Release, Py_buffer


cdef extern from "nlp/types.h":

    ctypedef unsigned char NL_flags;

    ctypedef struct NL_buffer:
        unsigned char *bytes;
        size_t size;

    ctypedef struct NL_annotations:
        void *list;
        size_t size;
        size_t _object_size;
        size_t _list_size;
        NL_flags flags;

    ctypedef struct NL_string:
        unsigned char *bytes;
        size_t size;
        NL_flags flags; 

    ctypedef struct NL_bspan:
        unsigned char *bytes;
        size_t size;
        void *data;
        NL_flags flags;

    ctypedef struct NL_sspan:
        size_t span_id;
        size_t size;
        void *data;
        NL_flags flags;

    ctypedef struct NL_doc:
        NL_buffer *buffer;
        NL_annotations *tokens;
        NL_annotations *pos_tags;
        NL_annotations *ner_tags;
        NL_annotations *sentences;
        unsigned char *flags;

cdef extern from "nlp/mem_manager.h":
    ctypedef struct NL_v_memmgr:
        pass

    cdef NL_v_memmgr *NL_new_v_memmgr(size_t block_size);
    cdef void NL_free_v_memmgr(NL_v_memmgr **);

    cdef void *NL_allocate_mem_size(NL_v_memmgr *mgr, size_t size);
    cdef void NL_deallocate_v_mem(NL_v_memmgr *mgr, void * data);


cdef extern from "nlp/annotations.h":
    cdef NL_bspan *NL_get_bspan(NL_annotations *ann, size_t index);
    cdef NL_sspan *NL_get_sspan(NL_annotations *ann, size_t index);
    cdef void NL_deallocate_bspan_annotations(NL_v_memmgr *mgr, 
            NL_annotations **ann);


cdef extern from "nlp/tokenizer.h":
    ctypedef enum NL_normalize_quotes:
        QUOTES_NONE, QUOTES_LATEX, QUOTES_UNICODE, QUOTES_ASCII

    ctypedef enum NL_normalize_ellipsis:
        ELLIPSIS_NONE, ELLIPSIS_PTB3, ELLIPSIS_UNICODE

    ctypedef struct NL_PTBTokConfig:
        int split_assimilations
        int normalize_dashes
        int normalize_amp
        NL_normalize_quotes normalize_quotes
        int tokenize_newlines;
        int normalize_currency;
        int escape_forward_slash_asterisk;
        NL_normalize_ellipsis normalize_ellipsis
        int normalize_parentheses;
        int normalize_brackets;
        int strict_ptb3;
        int normalize_spaces;
        int normalize_fractions;

    cdef NL_annotations *NL_tokenize_buf(
        NL_buffer *buffer,
        NL_PTBTokConfig *cfg, NL_v_memmgr *mgr);

cdef extern from "nlp/tokenizer/sentence_tokenizer.h":
    cdef NL_annotations *NL_sentence_tokenize(NL_annotations* tokens,
                NL_v_memmgr *mgr);

cdef class MemoryManagerWrapper(object):
    cdef NL_v_memmgr *_mgr

cdef class PTBTokenizerConfigWrapper(object):
    cdef NL_PTBTokConfig *_cfg

cdef MemoryManagerWrapper memmgr
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg

cdef class BufferDocument(object):
    cdef NL_doc *_doc;
    cdef Py_buffer _view;

cdef class BufferToken(object):
    cdef BufferDocument doc
    cdef size_t index

cdef class SentenceView(object):
    cdef BufferDocument doc
    cdef size_t index

