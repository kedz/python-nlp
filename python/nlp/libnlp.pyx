from __future__ import (absolute_import, division, print_function, 
        unicode_literals)

from cpython.version cimport PY_MAJOR_VERSION
from cpython.mem cimport PyMem_Malloc, PyMem_Free

cdef class MemoryManagerWrapper(object):
    def __cinit__(self):
        self._mgr = NL_new_v_memmgr(512);

    def __str__(self):
        return "MemoryManagerWrapper object (don't mess with me!)"

    def __dealloc__(self):
        NL_free_v_memmgr(&self._mgr);

cdef class PTBTokenizerConfigWrapper(object):
    def __cinit__(self):
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
        """When true, tokenizer normalizes tokens like "&mdash;" and  
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
        """When true, tokenizer normalizes tokens like "&amp;" to "&"."""

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
        """String or None. Accepts ["unicode"|"ascii"|"latex"|None]."""

        def __get__(self):
            
            if self._cfg.normalize_quotes == QUOTES_UNICODE:
                return "unicode"
            elif self._cfg.normalize_quotes == QUOTES_ASCII:
                return "ascii"
            elif self._cfg.normalize_quotes == QUOTES_LATEX:
                return "latex"
            elif self._cfg.normalize_quotes == QUOTES_NONE:
                return None

        def __set__(self, value):
            if value == None:
                self._cfg.normalize_quotes = QUOTES_NONE
            elif value == "unicode":
                self._cfg.normalize_quotes = QUOTES_UNICODE
            elif value == "ascii":
                self._cfg.normalize_quotes = QUOTES_ASCII
            elif value == "latex":
                self._cfg.normalize_quotes = QUOTES_LATEX
            else:
                raise ValueError(
                    "Property 'normalize_quotes' takes 1 of 4 values: " \
                    + "'unicode', 'ascii', 'latex', or None.")

    property tokenize_newlines:
        """When true, tokenizer tokenizes things like \\n and \\r\\n."""

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
        """When true, tokenizer converts things like '\u00A2' to 'cents'."""

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
        """When true, tokenizer transforms '*' and '/' to '\\*' and '\\/'.
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
        """String or None. Accepts ["unicode"|"ptb3"|None]."""

        def __get__(self):
            
            if self._cfg.normalize_ellipsis == ELLIPSIS_UNICODE:
                return "unicode"
            elif self._cfg.normalize_ellipsis == ELLIPSIS_PTB3:
                return "ptb3"
            elif self._cfg.normalize_ellipsis == ELLIPSIS_NONE:
                return None

        def __set__(self, value):
            if value == None:
                self._cfg.normalize_ellipsis = ELLIPSIS_NONE
            elif value == "unicode":
                self._cfg.normalize_ellipsis = ELLIPSIS_UNICODE
            elif value == "ptb3":
                self._cfg.normalize_ellipsis = ELLIPSIS_PTB3
            else:
                raise ValueError(
                    "Property 'normalize_ellipsis' takes 1 of 3 values: " \
                    + "'unicode', 'ptb3', or None.")

    property normalize_parentheses:
        """When true, tokenizer converts "(" and ")" to "-LRB-" and "-RRB-",
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
        """When true, tokenizer converts "[", "]", "{", and "}" to "-LSB-",
        "-RSB-", "-LCB-", and "-RCB-" respectively."""

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
        """When true, tokenizer tokenizes "U.K. About ", as ["U.K", ".", 
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
        """When true, tokenizer converts whitespace in phone numbers and 
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

    property normalize_fractions:
        """When true, tokenizer converts unicode fractions to text.
        E.g. "\u215E" becomes "7/8"."""

        def __get__(self):
            if self._cfg.normalize_fractions == 1:
                return True
            else:
                return False

        def __set__(self, value):
            if bool(value):
                self._cfg.normalize_fractions = 1
            else:
                self._cfg.normalize_fractions = 0



    def default(self):
        self.split_assimilations = True
        self.normalize_dashes = True
        self.normalize_amp = True
        self.normalize_quotes = "latex"
        self.tokenize_newlines = False
        self.normalize_currency = False
        self.escape_forward_slash_asterisk = False
        self.normalize_ellipsis = "ptb3"
        self.normalize_parentheses = True
        self.normalize_brackets = True
        self.strict_ptb3 = False
        self.normalize_spaces = True
        self.normalize_fractions = False


    def __str__(self):
        msg = "PTBTokenizerConfigWrapper\n" \
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
            + " ::             normalize spaces : {}\n".format(
                    self.normalize_spaces) \
            + " ::          normalize fractions : {}".format(
                    self.normalize_fractions)
        if PY_MAJOR_VERSION < 3:
            return msg.encode("utf-8")
        else: 
            return msg


    def __dealloc__(self):
        PyMem_Free(self._cfg);

cdef MemoryManagerWrapper memmgr = MemoryManagerWrapper()
cdef PTBTokenizerConfigWrapper global_ptb_tok_cfg = PTBTokenizerConfigWrapper()

def get_global_PTB_config():
    global global_ptb_tok_cfg
    return global_ptb_tok_cfg

cdef class BufferDocument(object):
    def __cinit__(self, bytes pystr):
       
        self.num_tokens = 0;
        self.tokens = NULL;
        if not PyObject_CheckBuffer(pystr):
            raise TypeError("argument must follow the buffer protocol")

        PyObject_GetBuffer(pystr, &self.view, PyBUF_SIMPLE);

    def __str__(self):
        if PY_MAJOR_VERSION < 3:
            return (<unsigned char *>self.view.buf)[:self.view.len]
        else:
            return (<unsigned char *>self.view.buf)[:self.view.len].decode(
                "utf-8")

    def __bytes__(self):
        return (<unsigned char *>self.view.buf)[:self.view.len]

    def __unicode__(self):
        return (<unsigned char *>self.view.buf)[:self.view.len].decode("utf-8")

    def __len__(self):
        return self.num_tokens

    def __iter__(self):
        cdef size_t i 
        for i in range(self.num_tokens):
            yield BufferToken(self, i)

    def __getitem__(self, i):
        return BufferToken(self, i)

    def __dealloc__(self):
        
        for i in range(self.num_tokens):
            NL_free_span(&self.tokens[i], memmgr._mgr)
        NL_deallocate_v_mem(memmgr._mgr, <void **> &self.tokens)
        PyBuffer_Release(&self.view)

cdef class BufferToken(object):
    def __cinit__(self, BufferDocument doc, size_t index):
        self.doc = doc
        self.index = index

    def __str__(self):
        cdef NL_span *tok = self.doc.tokens[self.index]
        if PY_MAJOR_VERSION < 3:
            if tok.label_length == 0:
                return (<unsigned char *>tok.start)[:tok.length]
            else: 
                return (<unsigned char *>tok.label)[:tok.label_length]
        else:
            if tok.label_length == 0:
                return (<unsigned char *>tok.start)[:tok.length].decode(
                    "utf-8")
            else: 
                return (<unsigned char *>tok.label)[:tok.label_length].decode(
                    "utf-8")

    def __bytes__(self):
        cdef NL_span *tok = self.doc.tokens[self.index]
        if tok.label_length == 0:
            return (<unsigned char *>tok.start)[:tok.length]
        else: 
            return (<unsigned char *>tok.label)[:tok.label_length]

    def __unicode__(self):
        cdef NL_span *tok = self.doc.tokens[self.index]
        if tok.label_length == 0:
            return (<unsigned char *>tok.start)[:tok.length].decode("utf-8")
        else: 
            return (<unsigned char *>tok.label)[:tok.label_length].decode(
                "utf-8")


