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

int span_test3() {
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    int error = 0;
    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, mgr);
    if (span->label != NULL) 
        error = 1;

    NL_free_span(&span, mgr);

    NL_free_v_memmgr(&mgr);
    return error;
}

int span_test4() {
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    int error = 0;
    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, mgr);
    if (span->label_length != 0) 
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

int label_test1() {
    int error = 0;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    unsigned char *test = (unsigned char *) "test";
    NL_label label = NL_create_label(test, 4, mgr);
    if (memcmp((char *) label, (char *) test, 4) != 0)
        error++;

    NL_deallocate_v_mem(mgr, label);
    NL_free_v_memmgr(&mgr);

    return error;
}

int label_test2() {
    int error = 0;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_label test = (NL_label) "test1\x00";

    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, mgr);

    NL_set_span_label(span, test, 5);
    if (memcmp((char *) test, span->label, 5) != 0) {
        error++;
    }
    if (span->label_length != 5) {
        error++;
    }

    NL_free_span(&span, mgr);
    NL_free_v_memmgr(&mgr);

    return error;
}

int label_test3() {
    int error = 0;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_label test = NL_create_label((unsigned char *) "test1", 5, mgr);
    unsigned char *buf = (unsigned char *) "buffer";
    NL_span *span = NL_new_span(buf, 6, mgr);

    NL_set_span_label(span, test, 5);
    if (memcmp((char *) test, span->label, 5) != 0) {
        error++;
    }
    if (span->label_length != 5) {
        error++;
    }

    NL_free_span(&span, mgr);
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

    if (span_test3() != 0) {
        printf("Span test3 failed!\n");
    } else {
        printf("Span test3 passed!\n");
    }

    if (span_test4() != 0) {
        printf("Span test4 failed!\n");
    } else {
        printf("Span test4 passed!\n");
    }

    if (label_test1() != 0) {
        printf("Label test1 failed!\n");
    } else {
        printf("Label test1 passed!\n");
    }

    if (label_test2() != 0) {
        printf("Label test2 failed!\n");
    } else {
        printf("Label test2 passed!\n");
    }

    if (label_test3() != 0) {
        printf("Label test3 failed!\n");
    } else {
        printf("Label test3 passed!\n");
    }



    if (doc_test1() != 0) {
        printf("Doc test1 failed!\n");
    } else {
        printf("Doc test1 passed!\n");
    }


}
