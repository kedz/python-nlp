
cdef extern from "document.h":
    ctypedef struct NL_span:
        pass

def tokenize(object str_or_unicode):
    cdef object buffer = str_or_unicode 
    if isinstance(str_or_unicode, unicode):
        buffer = buffer.encode("utf-8")
    cdef object tokens = buffer.split(" ")
    
    return tokens
