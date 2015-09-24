from nlp.libnlp cimport NL_document, NL_span, NL_v_memmgr, \
    MemoryManagerWrapper, memmgr, NL_tokenize_buf, NL_deallocate_v_mem, \
    NL_PTBTokConfig, PTBTokenizerConfigWrapper, global_ptb_tok_cfg, \
    NL_free_span, NL_label, BufferDocument, BufferToken

from cpython.buffer cimport PyBUF_SIMPLE, PyObject_CheckBuffer, \
    PyObject_GetBuffer, PyBuffer_Release, Py_buffer

from cpython.mem cimport PyMem_Malloc, PyMem_Free

def tokenize(object str_or_unicode):
    cdef object buf = str_or_unicode 
    cdef Py_buffer view;
    global memmgr
    global global_ptb_tok_cfg

    if isinstance(str_or_unicode, unicode):
        buf = buf.encode("utf-8")

    doc = BufferDocument(buf);

    doc.tokens = NL_tokenize_buf(
        <unsigned char *>doc.view.buf,
        <size_t> doc.view.len, 
        &doc.num_tokens, 
        global_ptb_tok_cfg._cfg, 
        memmgr._mgr)    

    return doc
