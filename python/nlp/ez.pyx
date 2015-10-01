from nlp.libnlp cimport NL_v_memmgr, \
    MemoryManagerWrapper, memmgr, NL_tokenize_buf, NL_deallocate_v_mem, \
    NL_allocate_mem_size, \
    NL_PTBTokConfig, PTBTokenizerConfigWrapper, global_ptb_tok_cfg, \
    BufferDocument, BufferToken, NL_annotations, \
    NL_doc, NL_buffer, NL_sentence_tokenize

from cpython.buffer cimport PyBUF_SIMPLE, PyObject_CheckBuffer, \
    PyObject_GetBuffer, PyBuffer_Release, Py_buffer

from cpython.mem cimport PyMem_Malloc, PyMem_Free

from libc.stdint cimport uintptr_t

def tokenize(object str_or_unicode):
    cdef object buf = str_or_unicode 
    global memmgr
    global global_ptb_tok_cfg

    if isinstance(str_or_unicode, unicode):
        buf = buf.encode("utf-8")
    
    if not PyObject_CheckBuffer(buf):
        raise TypeError("argument must follow the buffer protocol")
    doc = BufferDocument();
    cdef Py_buffer _view
    PyObject_GetBuffer(buf, &_view, PyBUF_SIMPLE);
    doc._view = _view

    #cdef void *mem = NL_allocate_mem_size(
    #        memmgr._mgr, sizeof(NL_doc) + sizeof(NL_buffer))
    #doc._doc = <NL_doc *> mem;
    doc._doc = <NL_doc *> NL_allocate_mem_size(memmgr._mgr, sizeof(NL_doc))
    doc._doc.tokens = NULL
    doc._doc.pos_tags = NULL
    doc._doc.ner_tags = NULL
    doc._doc.sentences = NULL
    doc._doc.flags = NULL
    #doc._doc.buffer = <NL_buffer *> mem + sizeof(NL_doc)
    doc._doc.buffer = <NL_buffer *> NL_allocate_mem_size(
            memmgr._mgr, sizeof(NL_buffer))
    doc._doc.buffer.bytes = <unsigned char *> doc._view.buf
    doc._doc.buffer.size = doc._view.len
    doc._doc.tokens = NL_tokenize_buf(doc._doc.buffer,
        global_ptb_tok_cfg._cfg, memmgr._mgr)

    return doc

def sent_tokenize(object str_or_unicode):
    cdef object buf = str_or_unicode 
    global memmgr
    global global_ptb_tok_cfg

    if isinstance(str_or_unicode, unicode):
        buf = buf.encode("utf-8")
    
    if not PyObject_CheckBuffer(buf):
        raise TypeError("argument must follow the buffer protocol")
    cdef BufferDocument doc = BufferDocument();
    cdef Py_buffer _view
    PyObject_GetBuffer(buf, &_view, PyBUF_SIMPLE);
    doc._view = _view
    print _view.len
    #cdef void *mem = NL_allocate_mem_size(
    #        memmgr._mgr, sizeof(NL_doc) + sizeof(NL_buffer))
    #doc._doc = <NL_doc *> mem;
    doc._doc = <NL_doc *> NL_allocate_mem_size(memmgr._mgr, sizeof(NL_doc))
    doc._doc.tokens = NULL
    doc._doc.pos_tags = NULL
    doc._doc.ner_tags = NULL
    doc._doc.flags = NULL

    #doc._doc.buffer = <NL_buffer *> mem + sizeof(NL_doc)
    doc._doc.buffer = <NL_buffer *> NL_allocate_mem_size(
            memmgr._mgr, sizeof(NL_buffer))
    doc._doc.buffer.bytes = <unsigned char *> doc._view.buf
    doc._doc.buffer.size = <size_t> doc._view.len
    doc._doc.tokens = NL_tokenize_buf(doc._doc.buffer,
        global_ptb_tok_cfg._cfg, memmgr._mgr)
    print (doc._doc.buffer.size)
    doc._doc.sentences = NL_sentence_tokenize(doc._doc.tokens, memmgr._mgr)
    return doc
