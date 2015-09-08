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

    property normalize_amp:
        u"""When true, tokenizer normalizes tokens like "&amp;" to "&"."""

        def __get__(self):
            if self._cfg.normalize_amp == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_amp = 1
            else:
                self._cfg.normalize_amp = 0

    property normalize_quotes:
        u"""String or None. Accepts ["unicode"|"ascii"|"latex"|None]."""

        def __get__(self):
            
            if self._cfg.normalize_quotes == QUOTES_UNICODE:
                return u"unicode"
            elif self._cfg.normalize_quotes == QUOTES_ASCII:
                return u"ascii"
            elif self._cfg.normalize_quotes == QUOTES_LATEX:
                return u"latex"
            elif self._cfg.normalize_quotes == QUOTES_NONE:
                return None

        def __set__(self, value):
            if value == None:
                self._cfg.normalize_quotes = QUOTES_NONE
            elif value == u"unicode":
                self._cfg.normalize_quotes = QUOTES_UNICODE
            elif value == u"ascii":
                self._cfg.normalize_quotes = QUOTES_ASCII
            elif value == u"latex":
                self._cfg.normalize_quotes = QUOTES_LATEX
            else:
                raise ValueError(
                    u"Property 'normalize_quotes' takes 1 of 4 values: " \
                    + u"'unicode', 'ascii', 'latex', or None.")

    property tokenize_newlines:
        u"""When true, tokenizer tokenizes things like \\n and \\r\\n."""

        def __get__(self):
            if self._cfg.tokenize_newlines == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.tokenize_newlines = 1
            else:
                self._cfg.tokenize_newlines = 0

    property normalize_currency:
        u"""When true, tokenizer converts things like '\u00A2' to 'cents'."""

        def __get__(self):
            if self._cfg.normalize_currency == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_currency = 1
            else:
                self._cfg.normalize_currency = 0

    property escape_forward_slash_asterisk:
        u"""When true, tokenizer transforms '*' and '/' to '\\*' and '\\/'.
        If either character is already escaped, no change is made."""

        def __get__(self):
            if self._cfg.escape_forward_slash_asterisk == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.escape_forward_slash_asterisk = 1
            else:
                self._cfg.escape_forward_slash_asterisk = 0

    def default(self):
        self.split_assimilations = True
        self.normalize_dashes = True
        self.normalize_amp = True
        self.normalize_quotes = None
        self.tokenize_newlines = False
        self.normalize_currency = False
        self.escape_forward_slash_asterisk = False

    def __str__(self):
        return "PTBTokenizerConfigWrapper\n" \
            + " ::              normalize dashes: {}\n".format(
                    self.normalize_dashes) \
            + " ::                 normalize amp: {}\n".format(
                    self.normalize_amp) \
            + " ::           split assimilations: {}\n".format(
                    self.split_assimilations) \
            + " ::              normalize quotes: {}\n".format(
                    self.normalize_quotes) \
            + " ::             tokenize newlines: {}\n".format(
                    self.tokenize_newlines) \
            + " ::            normalize currency: {}\n".format(
                    self.normalize_currency) \
            + " :: escape forward slash asterisk: {}".format(
                    self.escape_forward_slash_asterisk)

    def __dealloc__(self):
        print "PTBTokenizerConfigWrapper.__dealloc__()"
        PyMem_Free(self._cfg);

cdef MemoryManagerWrapper memmgr = MemoryManagerWrapper()
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg = PTBTokenizerConfigWrapper()

def get_global_PTB_config():
    global global_ptb_tok_cfg
    return global_ptb_tok_cfg
