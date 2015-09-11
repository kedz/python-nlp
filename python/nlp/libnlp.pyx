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
        self.default()

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

    property normalize_ellipsis:
        u"""String or None. Accepts ["unicode"|"ptb3"|None]."""

        def __get__(self):
            
            if self._cfg.normalize_ellipsis == ELLIPSIS_UNICODE:
                return u"unicode"
            elif self._cfg.normalize_ellipsis == ELLIPSIS_PTB3:
                return u"ptb3"
            elif self._cfg.normalize_ellipsis == ELLIPSIS_NONE:
                return None

        def __set__(self, value):
            if value == None:
                self._cfg.normalize_ellipsis = ELLIPSIS_NONE
            elif value == u"unicode":
                self._cfg.normalize_ellipsis = ELLIPSIS_UNICODE
            elif value == u"ptb3":
                self._cfg.normalize_ellipsis = ELLIPSIS_PTB3
            else:
                raise ValueError(
                    u"Property 'normalize_ellipsis' takes 1 of 3 values: " \
                    + u"'unicode', 'ptb3', or None.")

    property normalize_parentheses:
        u"""When true, tokenizer converts "(" and ")" to "-LRB-" and "-RRB-",
        respectively."""

        def __get__(self):
            if self._cfg.normalize_parentheses == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_parentheses = 1
            else:
                self._cfg.normalize_parentheses = 0

    property normalize_brackets:
        u"""When true, tokenizer converts "[", "]", "{", and "}" to "-LSB-",
        "-RSB-", "-LCB-", and "-RCB-".
        respectively."""

        def __get__(self):
            if self._cfg.normalize_brackets == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_brackets = 1
            else:
                self._cfg.normalize_brackets = 0

    property strict_ptb3:
        u"""When true, tokenizer tokenizes "U.K. About ", as ["U.K", ".", 
        "About"]."""

        def __get__(self):
            if self._cfg.strict_ptb3 == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.strict_ptb3 = 1
            else:
                self._cfg.strict_ptb3 = 0

    property normalize_spaces:
        u"""When true, tokenizer converts whitespace in phone numbers and 
        sgml to non-breaking unicode space U+00A0."""

        def __get__(self):
            if self._cfg.normalize_spaces == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_spaces = 1
            else:
                self._cfg.normalize_spaces = 0



    def default(self):
        self.split_assimilations = True
        self.normalize_dashes = True
        self.normalize_amp = True
        self.normalize_quotes = u"latex"
        self.tokenize_newlines = False
        self.normalize_currency = False
        self.escape_forward_slash_asterisk = False
        self.normalize_ellipsis = u"ptb3"
        self.normalize_parentheses = True
        self.normalize_brackets = True
        self.strict_ptb3 = False
        self.normalize_spaces = True


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
            + " :: escape forward slash asterisk: {}\n".format(
                    self.escape_forward_slash_asterisk) \
            + " ::            normalize ellipsis: {}\n".format(
                    self.normalize_ellipsis) \
            + " ::         normalize parentheses: {}\n".format(
                    self.normalize_parentheses) \
            + " ::            normalize brackets: {}\n".format(
                    self.normalize_brackets) \
            + " ::                   strict ptb3: {}\n".format(
                    self.strict_ptb3) \
            + " ::             normalize spaces : {}".format(
                    self.normalize_spaces)

    def __dealloc__(self):
        print "PTBTokenizerConfigWrapper.__dealloc__()"
        PyMem_Free(self._cfg);

cdef MemoryManagerWrapper memmgr = MemoryManagerWrapper()
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg = PTBTokenizerConfigWrapper()

def get_global_PTB_config():
    global global_ptb_tok_cfg
    return global_ptb_tok_cfg
