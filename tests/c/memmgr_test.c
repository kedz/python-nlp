#include "memmgr_test.h"

error_info **memmgr_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_new_memmgr test";

    size_t block_size = 16;
    size_t object_size = 8;
    size_t actual_object_size = object_size + 2;
    size_t actual_block_size = block_size * actual_object_size;

    NL_memmgr *mgr = NL_new_memmgr(16, 8);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_memmgr is null.");
    } else {
        if (mgr->block_size != block_size) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr block size is %lu, should be %lu", 
                mgr->block_size, block_size);
        }
        if (mgr->object_size != object_size) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr object size is %lu, should be %lu", 
                mgr->object_size, object_size);
        }

        if (mgr->actual_block_size != actual_block_size) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr block size is %lu, should be %lu", 
                mgr->actual_block_size, actual_block_size);
        }

        if (mgr->actual_object_size != actual_object_size) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr object size is %lu, should be %lu", 
                mgr->actual_object_size, actual_object_size);
        }

        if (mgr->available != 0) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->available is %lu, should be 0", 
                mgr->available);
        }

        if (mgr->allocs != 0) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->allocs is %d, should be 0", 
                mgr->allocs);
        }

        if (mgr->free_list != NULL) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->free_list should be NULL");
        }

        if (mgr->mem_list != NULL) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->mem_list should be NULL");
        }

        if (mgr->empty_containers != NULL) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->empty_containers should be NULL");
        }

        NL_free_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_memmgr was not freed.");

        }

    }

    return errors;
}

#define ALLOCS 32

error_info **memmgr_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_memmgr test";

    size_t block_size = 16;
    size_t object_size = 8;
    size_t actual_object_size = object_size + 2;
    size_t actual_block_size = block_size * actual_object_size;

    NL_memmgr *mgr = NL_new_memmgr(16, 8);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_memmgr is null.");
    } else {
        unsigned char *some_mem_arr[ALLOCS] = {NULL};
        for (int i=0; i < ALLOCS; i++) {

            some_mem_arr[i] = NL_allocate_mem(mgr);
            if (some_mem_arr[i] == NULL) {
                NEW_ERROR(strlen("NL_allocate_mem failed.") + 1);
                sprintf((char *) this_error->msg, "NL_allocate_mem failed.");
            } else {
                if (some_mem_arr[i][actual_object_size - 2] != 0xDE ||
                        some_mem_arr[i][actual_object_size - 1] != 0xAD) {

                    NEW_ERROR(
                        strlen("NL_allocate_mem guard bytes not set.") + 1);
                    sprintf((char *) this_error->msg, 
                    "NL_allocate_mem guard bytes not set.");

                }

            } 

            if (mgr->available != block_size - 1 - i % block_size) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->available is %lu, should be 0", 
                    mgr->available);
            }

            if (mgr->allocs != i + 1) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->allocs is %d, should be %d", 
                    mgr->allocs, i + 1);
            }


            if ((i+1) % block_size != 0 && mgr->free_list == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->free_list should not be NULL");
            } else if ((i+1) % block_size == 0 && mgr->free_list != NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg,
                    "NL_memmgr->free_list should be NULL");
            } 

            if (mgr->mem_list == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->mem_list should not be NULL");
            }

        }


        for (int i=0; i < ALLOCS; i++) {

            NL_deallocate_mem(mgr, (void *) &some_mem_arr[i]);
            if (some_mem_arr[i] != NULL) {
                NEW_ERROR(strlen("NL_allocate_mem failed.") + 1);
                sprintf((char *) this_error->msg, "NL_allocate_mem failed.");
            } 

            if (mgr->available != i + 1) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->available is %lu, should be %d", 
                    mgr->available, i + 1);
            }

            if (mgr->allocs != ALLOCS - 1 - i) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->allocs is %d, should be %d", 
                    mgr->allocs, ALLOCS - i - 1);
            }


            if (mgr->free_list == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->free_list should not be NULL");
            } 

            if (mgr->mem_list == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr->mem_list should not be NULL");
            }

        }

        if (mgr->empty_containers != NULL) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_memmgr->empty_containers should be NULL");
        }

        NL_free_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_memmgr was not freed.");

        }

    }

    return errors;
}

