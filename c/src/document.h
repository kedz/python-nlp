#include "MurmurHash3.h"
#include <string.h>

typedef struct NLPC_document NLPC_document;
typedef struct NLPC_span NLPC_span;
typedef struct NLPC_span_seq NLPC_span_seq;
typedef struct NL_label NL_label;

void NLPC_dbg_doc(NLPC_document *d);


NLPC_document *NLPC_new_document(unsigned char *buffer);
void NLPC_free_document(NLPC_document **d, int free_buffer);
unsigned char *NLPC_get_document_buffer(NLPC_document *d);

unsigned int NLPC_get_num_span_sequences(NLPC_document *d);
unsigned int NLPC_get_max_span_sequences(NLPC_document *d);
void NLPC_add_span_annotations(NLPC_document *, NLPC_span **, 
        unsigned int length);

NLPC_span *NLPC_new_span(unsigned char *buf_start, unsigned char *buf_end);
void NLPC_free_span(NLPC_span **span, int recursive);

NLPC_span *NLPC_get_span(NLPC_document *, unsigned int seq, unsigned int span);
int NLPC_span_eq(NLPC_span *, NLPC_span *);
unsigned int NLPC_span_seq_size(NLPC_document *d, unsigned int span_seq);

unsigned int NL_num_labels(NLPC_span *span);
void NL_add_label(NLPC_span *span, unsigned char * name, void *data);
void* NL_get_label_data(NLPC_span *span, unsigned char *name);



//NLPC_span_seq *NLPC_get_span_seq(NLPC_document *d, unsigned int seq);
//NLPC_span *NLPC_get_span(NLPC_span_seq *seq, unsigned int span);

unsigned char *NLPC_get_span_buffer(NLPC_span *span);
unsigned int NLPC_get_span_length(NLPC_span *span);
void NLPC_print_span(NLPC_span *span);
