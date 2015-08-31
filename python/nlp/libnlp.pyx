from cpython.mem cimport PyMem_Malloc, PyMem_Free

cdef class MemoryManagerWrapper(object):
    def __cinit__(self):
        print "MemoryManagerWrapper.__cinit__()"
        self._mgr = NL_new_v_memmgr(256);

    def __str__(self):
        return "MemoryManagerWrapper object (don't mess with me!)"

    def __dealloc__(self):
        print "MemoryManagerWrapper.__dealloc__()"
        NL_free_v_memmgr(&self._mgr);

cdef class PTBTokenizerConfigWrapper(object):
    def __cinit__(self):
        print "PTBTokenizerConfigWrapper.__cinit__()"
        self._cfg = <NL_PTBTokConfig *> PyMem_Malloc(sizeof(NL_PTBTokConfig))
        self._cfg.split_assimilations = 1
        self._cfg.normalize_dashes = 1

    property split_assimilations:
        """When true, tokenizer creates two tokens for assimilated words.
        E.g. "gimme" is tokenized as ["gim", "me"]."""

        def __get__(self):
            if self._cfg.split_assimilations == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.split_assimilations = 1
            else:
                self._cfg.split_assimilations = 0

    property normalize_dashes:
        u"""When true, tokenizer normalizes tokens like "&mdash;" and  
        "\u0096" to "--"."""

        def __get__(self):
            if self._cfg.normalize_dashes == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_dashes = 1
            else:
                self._cfg.normalize_dashes = 0


    def __str__(self):
        return "PTBTokenizerConfigWrapper object (don't mess with me!)"

    def __dealloc__(self):
        print "PTBTokenizerConfigWrapper.__dealloc__()"
        PyMem_Free(self._cfg);

cdef MemoryManagerWrapper memmgr = MemoryManagerWrapper()
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg = PTBTokenizerConfigWrapper()

def get_global_PTB_config():
    global global_ptb_tok_cfg
    return global_ptb_tok_cfg
