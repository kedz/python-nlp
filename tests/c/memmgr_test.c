#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nlp/document.h"
#include "nlp/mem_manager.h"
#include <time.h>


int main() {

    NL_memmgr *manager = NL_new_memmgr();
    time_t start;
    time_t end;
    time_t duration;
    int size = 32768;
    unsigned char *p = (unsigned char *) "This is a test for tokenizing.";
    size_t length = 4;

    start = time(NULL);
    for (int t = 0; t < 10000; t++) {
        NL_span **spans;
        spans = malloc(sizeof(NL_span *) * size);
        for (int i=0; i < size; i++) {
            spans[i] = NL_new_span(p, length, manager);
        }
            //    NL_new_span(p, length, NULL);
        for (int i=0; i < size; i++) {
            NL_free_span(&spans[i], manager);
        }
        free(spans);
    }
    NL_free_memmgr(&manager);
    end = time(NULL);
    duration = end - start;
    printf("%ld\n", duration);


    start = time(NULL);
    for (int t = 0; t < 5000; t++) {
        NL_span **spans;
        spans = malloc(sizeof(NL_span *) * size);
        for (int i=0; i < size; i++) {
            spans[i] = NL_new_span(p, length, NULL);
        }
        for (int i=0; i < size; i++) {
            NL_free_span(&spans[i], NULL);
        }
        free(spans);
    }
    end = time(NULL);
    duration = end - start;
    printf("%ld\n", duration);


    return 0;
}
