#include "nlp/document.h"
#include <string.h>
#include <stdio.h>

int span_test1() {
    int error = 0;
    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, NULL);
    if (memcmp(span->start, buf, 6) != 0) 
        error = 1;
    NL_free_span(&span, NULL);

    return error;
}

int span_test2() {
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    int error = 0;
    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, mgr);
    if (memcmp(span->start, buf, 6) != 0) 
        error = 1;
    NL_free_span(&span, mgr);

    NL_free_v_memmgr(&mgr);
    return error;
}

int doc_test1() {
    int error = 0;
    unsigned char *buffer = (unsigned char *) "This is a test buffer.";
    size_t buffer_length = strlen((char *)buffer);

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);

    NL_document *doc = NL_doc_from_buffer_length(buffer, buffer_length, mgr); 
    if (strcmp((char *)(doc->buffer), (char *) buffer) != 0) {
        error = 1;
    }
    
    if (strlen((char *)(doc->buffer)) != doc->buffer_length) {
        error = 1;
    }

    NL_deallocate_v_mem(mgr, doc);

    NL_free_v_memmgr(&mgr);
    return error;
}


int main() {
    if (span_test1() != 0) {
        printf("Span test1 failed!\n");
    } else {
        printf("Span test1 passed!\n");
    }

    if (span_test2() != 0) {
        printf("Span test2 failed!\n");
    } else {
        printf("Span test2 passed!\n");
    }

    if (doc_test1() != 0) {
        printf("Doc test1 failed!\n");
    } else {
        printf("Doc test1 passed!\n");
    }


}
