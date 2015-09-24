from __future__ import absolute_import, division, print_function, \
        unicode_literals
from cpython.version cimport PY_MAJOR_VERSION

from nlp.libnlp cimport BufferDocument

cdef class Pipeline(object):
    cdef list processors 
    cdef bint verbose

    def __cinit__(self):
        self.processors = []
        self.verbose = True

    def register(self, processor):
        if type(processor) == Processor:
            self.processors.append(processor)
        else:
            raise Exception(
                "Pipeline object can only register Processor objects")

    def process(self, input, input_type="strings"):
        if input_type == "strings":
            self.process_strings(input)
        elif input_type == "string":
            self.process_strings([input])
        elif input_type == "paths":
            self.process_paths(input)
        elif input_type == "path":
            self.process_paths([input])
        elif input_type == "files":
            self.process_files(input)
        elif input_type == "file":
            self.process_files([input])
        else:
            raise TypeError("Bad input!")
        
    def process_strings(self, list input):
        if self.verbose is True:
            print("process_strings not implemented.")
        ret = list()
        for pyobj in input:
            if type(pyobj) is unicode:
                pyobj = pyobj.encode("utf-8")
            elif PY_MAJOR_VERSION < 3 and isinstance(pyobj, bytes):
            # only accept byte strings in Python 2.x, not in Py3
                pyobj = pyobj
                #return (<bytes>s).decode('ascii')
            elif isinstance(pyobj, unicode):
        # an evil cast to <unicode> might work here in some(!) cases,
        # depending on what the further processing does.  to be safe,
        # we can always create a copy instead
                pyobj = unicode(pyobj).encode("utf-8")
            else:
                raise TypeError("Bad input!")
            doc = BufferDocument(pyobj)        

            ret.append(doc)
                   
        return ret


    def process_paths(self, input):
        if self.verbose is True:
            print("process_paths not implemented.")

    def process_files(self, input):
        if self.verbose is True:
            print("process_files not implemented.")


cdef class Processor(object):
    cdef str lang

    def __cinit__(self, lang="en"):
        self.lang = lang

cdef class ObjectProcessor(Processor):
    def __cinit__(self, lang="*"):
        self.lang = lang

    def processor(self, object obj):
        pass


