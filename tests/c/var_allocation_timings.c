#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "nlp/mem_manager.h"

double timedifference_msec(struct timeval t0, struct timeval t1) {
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + 
                (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

int main() {

    struct timeval stop, start;
    int test_size = 1000;
    int num_tests = 10;
    //size_t sizes[4] = {5, 10, 15 ,25};
    //size_t sizes[4] = {2, 4, 8, 16};
    size_t sizes[10] = {1, 3, 5, 8, 16, 32, 64, 128, 256, 512};

    unsigned char ** buffers = malloc(sizeof(unsigned char*) * test_size);
    int opt, i;

//    gettimeofday(&start, NULL);
//
//    NL_memmgr *mgr = NL_new_memmgr(512, 8);
//
//    for (int t=0; t < num_tests; t++) {
//        for (i=0; i < test_size; i++) {
//            opt = i % 4;
//            buffers[i] = NL_allocate_mem(mgr);
//        }
//
//        for (i=0; i < test_size; i++) {
//            NL_deallocate_mem(mgr, buffers[i]);
//        }
//    }
//    NL_free_memmgr(&mgr);
//    gettimeofday(&stop, NULL);
//    printf("took %f\n", timedifference_msec(start, stop));

    NL_v_memmgr *vmgr;
    gettimeofday(&start, NULL);

    vmgr = NL_new_v_memmgr(512);

    for (int t=0; t < num_tests; t++) {
        for (i=0; i < test_size; i++) {
            //opt = i % 10;
            buffers[i] = NL_allocate_mem_size(vmgr, 16);
            //buffers[i] = NL_allocate_16_mem(vmgr);
        }

        for (i=0; i < test_size; i++) {
            NL_deallocate_v_mem(vmgr, buffers[i]);
        }
    }
    NL_free_v_memmgr(&vmgr);
    gettimeofday(&stop, NULL);
    printf("took %f\n", timedifference_msec(start, stop));



    gettimeofday(&start, NULL);
    vmgr = NL_new_v_memmgr(512);

    for (int t=0; t < num_tests; t++) {
        for (i=0; i < test_size; i++) {
            opt = i % 10;
            //buffers[i] = NL_allocate_mem_size(vmgr, sizes[opt]);
            buffers[i] = NL_allocate_16_mem(vmgr);
        }

        for (i=0; i < test_size; i++) {
            NL_deallocate_v_mem(vmgr, buffers[i]);
        }
    }
    NL_free_v_memmgr(&vmgr);
    gettimeofday(&stop, NULL);
    printf("took %f\n", timedifference_msec(start, stop));



//    gettimeofday(&start, NULL);
//    for (int t=0; t < num_tests; t++) {
//        for (i=0; i < test_size; i++) {
//            opt = i % 4;
//            buffers[i] = malloc(sizeof(unsigned char) * sizes[opt]);
//        }
//
//        for (i=0; i < test_size; i++) {
//            free(buffers[i]);
//        }
//    }
//    gettimeofday(&stop, NULL);
//    printf("took %f\n", timedifference_msec(start, stop));

    free(buffers);
}
