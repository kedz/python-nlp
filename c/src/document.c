#include "document.h"
#include <stdlib.h>
#include <stdio.h>

#define BASE_ANNOTATION_SIZE 8

// TODO add buffer length
struct NLPC_document {
    unsigned char *buffer;
    NLPC_span_seq **span_seqs;
    unsigned int num_span_seqs;
    //unsigned int *span_seq_lengths;
    unsigned int max_span_seqs;
};

struct NL_label {
    unsigned char *name;
    void *data; 
    unsigned int is_owner;
};



struct NLPC_span {
    unsigned char *start;
    unsigned char *stop;
    unsigned int length;
    NL_label**labels;
    unsigned int num_labels;
    //NLPC_span **spans;
    //int num_spans; 
};

struct NLPC_span_seq {
    NLPC_span **spans;
    unsigned int length;
};


//struct NLPC_span_iter {
//    unsigned int pos;
//    NLPC_span *span_seq;
//    unsigned int length;
//};


//NLPC_span *NLPC_init_span_iter(
//    NLPC_document *d, 
//    NLPC_span_iter *iter, 
//    unsigned int span_seq) 
//{

//    iter->span_seq = d->span_seqs[span_seq];
//    iter->pos = 0;
//    iter->length = d->span_seq_lengths[span_seq];

//    if (iter->pos < iter->length) {
//        return iter->span_seq;
//    } else {
//        return NULL;
//    }
//}


//NLPC_span *NLPC_next_span(NLPC_span_iter *iter) {
//    iter->span_seq += sizeof(NLPC_span *);
//    if (iter->pos++ < iter->length) {
//        return iter->span_seq;
//    } else {
//        return NULL;
//    }
//}

void NLPC_dbg_doc(NLPC_document *d) {
    printf("THIS IS THE BUFFER:   ");
    fwrite((char *) d->buffer, 1, 4, stdout);
    printf("\n");

}

NLPC_span *NLPC_new_span(unsigned char *buf_start, unsigned char *buf_end) {
    NLPC_span *span;
    if ((span = malloc(sizeof *span)) != NULL) {
        span->start = buf_start;
        span->stop = buf_end;
        span->length = buf_end - buf_start;
        span->num_labels = 0;
        
    }
    
    return span;
}

void NLPC_free_span(NLPC_span **s, int recursive) {
    if ((*s) != NULL) {
        
        free(*s);
        *s = NULL;
    }
}

void NLPC_add_span_annotations(
    NLPC_document *d, 
    NLPC_span **s, 
    unsigned int length) 
{

    if (d->num_span_seqs == 0) {
        d->span_seqs = malloc(sizeof(NLPC_span_seq *) * BASE_ANNOTATION_SIZE);
        d->max_span_seqs = BASE_ANNOTATION_SIZE;
        //d->span_seq_lengths = calloc(sizeof(unsigned int),
         //                            BASE_ANNOTATION_SIZE);       
    } else if (d->num_span_seqs >= d->max_span_seqs) {
        printf("I need to implement this\n");
        d->max_span_seqs = d->max_span_seqs * 2;
        realloc(d->span_seqs, sizeof(NLPC_span_seq *) * d->max_span_seqs);
    }

    
    d->span_seqs[d->num_span_seqs] = malloc(sizeof(NLPC_span_seq));
    d->span_seqs[d->num_span_seqs]->spans = s;
    d->span_seqs[d->num_span_seqs]->length = length;
    //d->span_seq_lengths[d->num_span_seqs] = length;
    d->num_span_seqs++;

}

//NLPC_span_seq *NLPC_get_span_seq(NLPC_document *d, unsigned int seq) {
//    return d->span_seqs[seq];
//}
NLPC_span *NLPC_get_span(
    NLPC_document *d, 
    unsigned int seq, 
    unsigned int span) {
    NLPC_span_seq *seq_ptr = d->span_seqs[seq];
    return seq_ptr->spans[span];
}

int NLPC_span_eq(NLPC_span *s1, NLPC_span *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }
    
    if (s1->start != s2->start)
        return 0;
    if (s1->stop != s2->stop)
        return 0;
    return 1;
}

//NLPC_span *NLPC_get_span(NLPC_span_seq *seq, unsigned int span) {
//    if (span < seq->length) {
  //      return seq->spans[span];
  //  } else {
   //     return NULL;
//    }
//}


unsigned char *NLPC_get_span_buffer(NLPC_span *span) {
    return span->start;
}

unsigned int NLPC_get_span_length(NLPC_span *span) {
    return span->length;
}

void NLPC_print_span(NLPC_span *span) {
    fwrite(span->start, 1, span->length, stdout);
}

NLPC_document *NLPC_new_document(unsigned char *buffer) {

    NLPC_document *d;
    if ((d = malloc(sizeof *d)) != NULL) {
        d->buffer = buffer;
        d->num_span_seqs = 0;
        //d->span_seq_lengths = NULL;
        d->max_span_seqs = 0;
        d->span_seqs = NULL;
    }

    return d;
}


void free_span_seq(NLPC_span_seq **s) {
    unsigned int i;
    for (i = 0; i < (*s)->length; i++) {
        free((*s)->spans[i]);
    }
    free(*s);
    *s = NULL;
}

void NLPC_free_document(NLPC_document **d, int free_buffer) {
    if ((*d) != NULL) {
        if (free_buffer != 0 && (*d)->buffer != NULL) {
            free((*d)->buffer);
        }
        
        unsigned int i;
        for (i = 0; i < (*d)->num_span_seqs; i++) {
            free_span_seq(&(*d)->span_seqs[i]);
        }

        free(*d);
        *d = NULL;
    }
} 

unsigned char * NLPC_get_document_buffer(NLPC_document *d) {
    return d->buffer;
}



unsigned int NLPC_get_num_span_sequences(NLPC_document *d) {
    return d->num_span_seqs;
}

unsigned int NLPC_get_max_span_sequences(NLPC_document *d) {
    return d->max_span_seqs;
}

unsigned int NLPC_span_seq_size(NLPC_document *d, unsigned int span_seq) {
    if (span_seq < d->num_span_seqs)
        return d->span_seqs[span_seq]->length;
    else
        return 0;
}

void NL_add_label(NLPC_span *span, unsigned char *name, void *data) {
    if (span->num_labels == 0) {
        //printf("Allocating labels.\n");
        span->labels = malloc(sizeof(NL_label *) * 4);
        for(int i=0; i < 4; i++) span->labels[i] = NULL;
    }

    NL_label *label = malloc(sizeof(NL_label));
    label->name = name;
    label->data = data;
    unsigned int *hash = malloc(sizeof(unsigned int));
    MurmurHash3_x64_128(
        (void *) name, 4, (uint32_t) 1986, (void *) hash);

    unsigned int index = *hash % 4;
    free(hash);

    int tries = 0;
    while(tries < 4) {
        if (span->labels[index] == NULL) {
            span->labels[index] = label;
            span->num_labels++;
            break;
        } else {
            index++;
            if (index >= 4)
                index = 0;
        }
        tries++;
    }
}

unsigned int NL_num_labels(NLPC_span* span) {
    return span->num_labels;
}

void* NL_get_label_data(NLPC_span *span, unsigned char *name) {
    if (span->num_labels == 0)
        return NULL;

    unsigned int *hash = malloc(sizeof(unsigned int));
    MurmurHash3_x64_128(
        (void *) name, 4, (uint32_t) 1986, (void *) hash);

    unsigned int index = *hash % 4;
    free(hash);

    int tries = 0;
    while(tries < 4) {
        if (span->labels[index] == NULL) {
            index++;
        } else if (strcmp(span->labels[index], name)) {
           return span->labels[index]->data;
        }
        
        if (index >= 4)
            index = 0;
        tries++;
    }
    return NULL; 
}

