#ifndef H_NL_DOCUMENT
#define H_NL_DOCUMENT

#include "mem_manager.h"

typedef struct NL_span {
    unsigned char *start;
    size_t length;
    //NL_label**labels;
    //unsigned int num_labels;
    //NLPC_span **spans;
    //int num_spans; 
} NL_span;

typedef struct NL_document {
    unsigned char *buffer;
    size_t buffer_length;
    NL_span **tokens;
    size_t num_tokens;

} NL_document;

#define NL_SPAN_SIZE 16
#define NL_DOC_SIZE 32

NL_span *NL_new_span(unsigned char *buf_start, size_t length,
        NL_v_memmgr *manager);
NL_span **NL_new_spans(size_t num_spans, NL_v_memmgr *manager);
void NL_free_span(NL_span **span, NL_v_memmgr *manager);

NL_document *NL_doc_from_buffer_length(
    unsigned char *buffer, size_t buffer_length, NL_v_memmgr *manager);


/*typedef struct NLPC_document NLPC_document;
typedef struct NL_span_seq NL_span_seq;
typedef struct NL_label NL_label;

void NLPC_dbg_doc(NLPC_document *d);


NLPC_document *NLPC_new_document(unsigned char *buffer);
void NLPC_free_document(NLPC_document **d, int free_buffer);
unsigned char *NLPC_get_document_buffer(NLPC_document *d);

unsigned int NLPC_get_num_span_sequences(NLPC_document *d);
unsigned int NLPC_get_max_span_sequences(NLPC_document *d);
void NLPC_add_span_annotations(NLPC_document *, NL_span **, 
        unsigned int length);

NL_span *NLPC_new_span(unsigned char *buf_start, unsigned char *buf_end);
void NLPC_free_span(NL_span **span, int recursive);

NL_span *NLPC_get_span(NLPC_document *, unsigned int seq, unsigned int span);
int NL_span_eq(NL_span *, NL_span *);
unsigned int NL_span_seq_size(NLPC_document *d, unsigned int span_seq);

unsigned int NL_num_labels(NL_span *span);
void NL_add_label(NL_span *span, unsigned char * name, void *data);
void* NL_get_label_data(NL_span *span, unsigned char *name);



//NL_span_seq *NLPC_get_span_seq(NLPC_document *d, unsigned int seq);
//NL_span *NLPC_get_span(NL_span_seq *seq, unsigned int span);

unsigned char *NLPC_get_span_buffer(NL_span *span);
unsigned int NLPC_get_span_length(NL_span *span);
void NLPC_print_span(NL_span *span);
*/


#endif
