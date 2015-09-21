from nlp.libnlp cimport NL_document, NL_span, NL_v_memmgr, \
    MemoryManagerWrapper, memmgr, NL_tokenize_buf, NL_deallocate_v_mem, \
    NL_PTBTokConfig, PTBTokenizerConfigWrapper, global_ptb_tok_cfg, \
    NL_free_span, NL_label, BufferDocument

from cpython.buffer cimport PyBUF_SIMPLE, PyObject_CheckBuffer, \
    PyObject_GetBuffer, PyBuffer_Release, Py_buffer

from cpython.mem cimport PyMem_Malloc, PyMem_Free

def tokenize(object str_or_unicode):
    cdef object buf = str_or_unicode 
    cdef Py_buffer view;
    global memmgr
    global global_ptb_tok_cfg
    cdef size_t *num_tokens = <size_t *> PyMem_Malloc(sizeof(size_t));
    cdef NL_span **tokens 
    cdef int i

    if isinstance(str_or_unicode, unicode):
        buf = buf.encode("utf-8")

    doc = BufferDocument(buf);

#    if not PyObject_CheckBuffer(buf):
#        raise TypeError("argument must follow the buffer protocol")
    
#    PyObject_GetBuffer(buf, &view, PyBUF_SIMPLE);

    doc.tokens = NL_tokenize_buf(
        <unsigned char *>doc.view.buf,
        <size_t> doc.view.len, 
        &doc.num_tokens, 
        global_ptb_tok_cfg._cfg, 
        memmgr._mgr)    

#    py_tokens = []
#    for i in range(num_tokens[0]):
#        if tokens[i].label == NULL:
#            py_tokens.append(tokens[i].start[:tokens[i].length])
#        else:
#            py_tokens.append(tokens[i].label[:tokens[i].label_length])
#   
#    for i in range(num_tokens[0]):
#        NL_free_span(&tokens[i], memmgr._mgr)
#    NL_deallocate_v_mem(memmgr._mgr, <void **> &tokens)
#
#    PyMem_Free(num_tokens);
#    PyBuffer_Release(&view)
#    return py_tokens

    return doc;
