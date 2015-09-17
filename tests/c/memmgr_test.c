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

error_info **vmemmgr_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_new_v_memmgr test";

    size_t block_size = 16;
    size_t max_pools = 8;

    NL_v_memmgr *mgr =  NL_new_v_memmgr(16);

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
        if (mgr->max_pools != max_pools) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_v_memmgr max_pool is %lu, should be %lu", 
                mgr->max_pools, max_pools);
        }
        size_t object_size = 2;
        for (int j=0; j < mgr->max_pools; j++) {
            
            NL_memmgr *smgr = mgr->pools[j];

            if (smgr == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_memmgr pool %d is not initialized!", j);

            } else {
                if (smgr->object_size != object_size) {
                    NEW_ERROR(200);
                    sprintf(
                        (char *) this_error->msg, 
                        "NL_memmgr pool %d has object size %lu, expected %lu", 
                        j, smgr->object_size, object_size);

                }
            }

            object_size = object_size * 2;
        }

        NL_free_v_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_memmgr was not freed.");

        }

    }

    return errors;
}

error_info **vmemmgr_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_v_memmgr test2";

    size_t block_size = 16;
    size_t max_pools = 8;

    NL_v_memmgr *mgr =  NL_new_v_memmgr(16);

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
        if (mgr->max_pools != max_pools) {
            NEW_ERROR(200);
            sprintf(
                (char *) this_error->msg, 
                "NL_v_memmgr max_pool is %lu, should be %lu", 
                mgr->max_pools, max_pools);
        }


        int size_tests = 1024;
        int allocs_arr[17];
        int pool_sizes[17];
        int tmp = 2;
        for (int i =0; i < 17; i++) { 
            allocs_arr[i] = 0;
            pool_sizes[i] = tmp; tmp  = tmp * 2;
        }
        unsigned char *mems[1024];
        for (size_t i= size_tests-1; i > 0; i--) {

            int floor_log = (int) log2((float) i);
            size_t bin = floor_log;
            if (bin > 0 && pool_sizes[bin-1] == i)
                bin--;
            allocs_arr[bin]++;   

            mems[i] = NL_allocate_mem_size(mgr, i);
            if (mems[i] == NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "NL_v_memmgr failed to allocate memory of size %lu", i);
            } else {
                if (mems[i][mgr->pools[bin]->object_size] != 0xDE ||
                        mems[i][mgr->pools[bin]->object_size + 1] != 0xAD) {
                    NEW_ERROR(200);
                    sprintf(
                        (char *) this_error->msg, 
                        "Allocation of memory of size %lu missing guard byte", 
                        i);

                }
                if (mgr->pools[bin]->allocs != allocs_arr[bin]) {
                    NEW_ERROR(200);
                    sprintf(
                        (char *) this_error->msg, 
                        "Allocation of memory of size %lu assigned to wrong "
                        "pool", 
                        i);
                }
            }

        }

        for (size_t i=1; i < size_tests; i++) {

            int floor_log = (int) log2((float) i);
            size_t bin = floor_log;
            if (bin > 0 && pool_sizes[bin-1] == i)
                bin--;
            allocs_arr[bin]--;   

            if (mems[i] != NULL) {
                NL_deallocate_v_mem(mgr, (void **) &mems[i]);

                if (mems[i] != NULL) {
                    NEW_ERROR(200);
                    sprintf(
                        (char *) this_error->msg, 
                        "Deallocation of size %lu failed.", i);
                }
                if (mgr->pools[bin]->allocs != allocs_arr[bin]) {
                    NEW_ERROR(200);
                    sprintf(
                        (char *) this_error->msg, 
                        "Deallocation of memory of size %lu assigned to wrong "
                        "pool", 
                        i);
                }

            }
        }
        for (size_t i=0; i < mgr->max_pools; i++) {
            if (mgr->pools[i]->allocs > 0) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "Memmory pool %lu has %d allocs, should be 0",
                    i, mgr->pools[i]->allocs);
            }

        }

        NL_free_v_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_memmgr was not freed.");

        }

    }

    return errors;
}

error_info **vmemmgr_test3(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_v_memmgr allocate16 test3";


    NL_v_memmgr *mgr =  NL_new_v_memmgr(16);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_v_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_v_memmgr is null.");
    } else {
        unsigned char *mem = NULL;
        mem = NL_allocate_16_mem(mgr);
        if (mem == NULL) {
            NEW_ERROR(strlen("Allocation failed.") + 1);
            sprintf((char *) this_error->msg, "Allocation failed.");

        } else {
            if (mem[16] != 0xDE || mem[17] != 0xAD) {
                NEW_ERROR(strlen("Guard bytes not set.") + 1);
                sprintf((char *) this_error->msg, "Guard bytes not set.");
            }
            
            if (mgr->pools[3]->allocs != 1) {
                NEW_ERROR(strlen("Allocation from wrong pool.") + 1);
                sprintf((char *) this_error->msg, 
                    "Allocation from wrong pool.");
            }

            NL_deallocate_v_mem(mgr, (void **)  &mem);

            if (mem != NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "Deallocation of size failed.");
                }

        }

        NL_free_v_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_v_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_v_memmgr was not freed.");

        }

    }

    return errors;
}

error_info **vmemmgr_test4(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_v_memmgr allocate32 test4";


    NL_v_memmgr *mgr =  NL_new_v_memmgr(16);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_v_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_v_memmgr is null.");
    } else {
        unsigned char *mem = NULL;
        mem = NL_allocate_32_mem(mgr);
        if (mem == NULL) {
            NEW_ERROR(strlen("Allocation failed.") + 1);
            sprintf((char *) this_error->msg, "Allocation failed.");

        } else {
            if (mem[32] != 0xDE || mem[33] != 0xAD) {
                NEW_ERROR(strlen("Guard bytes not set.") + 1);
                sprintf((char *) this_error->msg, "Guard bytes not set.");
            }
            
            if (mgr->pools[4]->allocs != 1) {
                NEW_ERROR(strlen("Allocation from wrong pool.") + 1);
                sprintf((char *) this_error->msg, 
                    "Allocation from wrong pool.");
            }

            NL_deallocate_v_mem(mgr, (void **)  &mem);

            if (mem != NULL) {
                NEW_ERROR(200);
                sprintf(
                    (char *) this_error->msg, 
                    "Deallocation of size failed.");
                }

        }

        NL_free_v_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_v_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_v_memmgr was not freed.");

        }

    }

    return errors;
}

error_info **vmemmgr_test5(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_v_memmgr allocate 0 test5";


    NL_v_memmgr *mgr =  NL_new_v_memmgr(16);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_v_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_v_memmgr is null.");
    } else {
        unsigned char *mem = NULL;
        mem = NL_allocate_mem_size(mgr, 0);
        if (mem != NULL) {
            NEW_ERROR(strlen("Allocation should be none.") + 1);
            sprintf((char *) this_error->msg, "Allocation should be none.");

        } 

        for (int i=0; i < mgr->max_pools; i++) {    
            if (mgr->pools[i]->allocs != 0) {
                NEW_ERROR(200);
                sprintf((char *) this_error->msg, 
                    "Allocations from pool %d is %d, should be 0.",
                    i, mgr->pools[i]->allocs);
            }
        }

        NL_free_v_memmgr(&mgr);
        if (mgr != NULL) {

            NEW_ERROR(strlen("NL_v_memmgr was not freed.") + 1);
            sprintf((char *) this_error->msg, "NL_v_memmgr was not freed.");

        }

    }

    return errors;
}
