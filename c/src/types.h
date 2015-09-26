#ifndef H_NL_TYPES
#define H_NL_TYPES

typedef unsigned char NL_flags;

#define NL_OWN_DATA 0x01

// All annotations are built on top of an underlying byte buffer. Usually this
// is the text of a document under analysis. size stores the length of the 
// buffer in bytes.
typedef struct NL_buffer {
    unsigned char *bytes;
    size_t size;
} NL_buffer;


// A list of annotations on an NL_buffer object.
typedef struct NL_annotations {
    void *list;
    size_t size;
    size_t _object_size;
    size_t _list_size;
} NL_annotations;

// A string type. One additional byte for storing meta data.
typedef struct NL_string {
    unsigned char *bytes;
    size_t size;
    NL_flags flags; 
} NL_string;

// Span of bytes annotation.
typedef struct NL_bspan {
    unsigned char *bytes;
    size_t size;
    void *data;
    NL_flags flags;
    
} NL_bspan;

// Span of spans.
typedef struct NL_sspan {
    NL_bspan *spans;
    size_t size;
    void *data;
    NL_flags flags;
} NL_sspan;

typedef struct NL_doc {
    NL_buffer *buffer;
    NL_annotations *tokens;
    NL_annotations *pos_tags;
    NL_annotations *ner_tags;
    unsigned char *flags;
} NL_doc;

#endif
