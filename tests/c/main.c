#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nlp/document.h"
#include "nlp/tokenizer.h"

int test_document() {

    int err = 0;
    char * test_string = "this is    a sample string";
    NLPC_document *doc = NLPC_new_document(test_string);
    int asgn_err = strcmp(test_string, NLPC_get_document_buffer(doc)); 

    err += asgn_err;

    printf("document creation/buffer assignment...\t");
    if (asgn_err == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }


    printf("document free...\t");
    NLPC_free_document(&doc, 0);
    if (doc != NULL) {
        err += 1;
        printf("FAIL\n");
    } else {
        printf("SUCCESS\n");
    }

    return err;
}

int test_span() {

    int err = 0;
    char * test_string = "this is    a sample string";
    NLPC_span *span1 = NLPC_new_span(test_string, test_string + 4);
    int span1_length = NLPC_get_span_length(span1);
    char *span1_buffer = NLPC_get_span_buffer(span1);


    printf("span creation/buffer assignment...\t");
    if (memcmp(span1_buffer, test_string, span1_length) != 0) {
        err += 1;
        printf("FAIL\n");
    } else { 
        printf("SUCCESS\n");
    }


    NLPC_free_span(&span1, 0);
    printf("span free...\t");
    if (span1 != NULL) {
        err += 1;
        printf("FAIL\n");

    } else {
        printf("SUCCESS\n");
    }

    return err;
}

int test_span_assignment() {

    int err = 0;
    char * test_string = "this is    a sample string";
    NLPC_document *doc = NLPC_new_document(test_string);

    

    NLPC_span **spans = malloc( sizeof(NLPC_span *) * 5);
    spans[0] = NLPC_new_span(test_string, test_string + 4);
    spans[1] = NLPC_new_span(test_string + 5, test_string + 7);
    spans[2] = NLPC_new_span(test_string + 11, test_string + 12);
    spans[3] = NLPC_new_span(test_string + 13, test_string + 19);
    spans[4] = NLPC_new_span(test_string + 20, test_string + 26);
    //need to free these

    NLPC_add_span_annotations(doc, spans, 5);

    int span_cmp_err = 0;
    unsigned int j; 
    printf("Checking annotate spans...\t");
    NLPC_span *span;  
    for (j = 0; j < 5; j++) {
        span = NLPC_get_span(doc, 0, j);    
        if (NLPC_span_eq(span, spans[j]) == 0)
            span_cmp_err = 1;
    }
    if (span_cmp_err == 1) {
        err++;
        printf("FAIL\n");
    } else {
        printf("SUCCESS\n");
    }
    free(spans);
    NLPC_free_document(&doc, 0);

    return err;
}

int test_tokenizer() {
    
    int err = 0;
    char * test_string = "this is    a sample string";
    NLPC_document *doc = NLPC_new_document(test_string);
    NLPC_tokenize_document(doc);

    NLPC_span **spans = malloc( sizeof(NLPC_span *) * 5);
    spans[0] = NLPC_new_span(test_string, test_string + 4);
    spans[1] = NLPC_new_span(test_string + 5, test_string + 7);
    spans[2] = NLPC_new_span(test_string + 11, test_string + 12);
    spans[3] = NLPC_new_span(test_string + 13, test_string + 19);
    spans[4] = NLPC_new_span(test_string + 20, test_string + 26);

    unsigned int j; 
    printf("Checking tokenize document...\t");
    NLPC_span *span;  
    for (j = 0; j < 5; j++) {
        span = NLPC_get_span(doc, 0, j);    
        if (NLPC_span_eq(span, spans[j]) == 0)
            err = 1;
    }

    if (err == 1) {
        printf("FAIL\n");
    } else {
        printf("SUCCESS\n");
    }
    for (j = 0; j < 5; j++)
        free(spans[j]);
    free(spans);

    NLPC_free_document(&doc, 0);

    return 0;
}

int main() {
    printf("TESTING\n");
    test_document();
    test_span();
    test_span_assignment();
    test_tokenizer();

    return 0;

}
