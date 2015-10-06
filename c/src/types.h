#ifndef H_NL_TYPES
#define H_NL_TYPES

#include <stdint.h>

typedef uint32_t NL_hash[4];
#define NL_SIZEOF_HASH sizeof(uint32_t) * 4

typedef unsigned char NL_flags;

#define NL_OWN_DATA 0x01
#define NL_SENT_END_FLAG 0x02
#define NL_SENT_INC 0x04

// All annotations are built on top of an underlying byte buffer. Usually this
// is the text of a document under analysis. size stores the length of the 
// buffer in bytes.
typedef struct NL_buffer {
    unsigned char *bytes;
    size_t size;
} NL_buffer;


// A list of annotations on an NL_buffer object.
typedef struct NL_annotations {
    void **_lists;
    size_t size;
    size_t _object_size;
    size_t _num_lists;
    size_t _max_lists;
    size_t _current_position;
    NL_flags flags;
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
    size_t span_id;
    size_t size;
    void *data;
    NL_flags flags;
} NL_sspan;

typedef struct NL_doc {
    NL_buffer *buffer;
    NL_annotations *tokens;
    NL_annotations *pos_tags;
    NL_annotations *ner_tags;
    NL_annotations *sentences;
    unsigned char *flags;
} NL_doc;

#endif
