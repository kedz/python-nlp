#include "murmur_hash_tests.h"

error_info **murmur_hash_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "murmur hash test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    

    unsigned char *bytes = (unsigned char *) "Hello, world!";
    size_t size = strlen((char *) bytes);
    NL_hash *hash = NL_allocate_mem_size(mgr, NL_SIZEOF_HASH);
    MurmurHash3_x64_128(bytes, size, 123, hash);
    char * expected = "8743acad421c8c73d373c3f5f19732fd";
    char * hash_str = NL_allocate_mem_size(mgr, 33);
    sprintf(hash_str, "%08x%08x%08x%08x", 
            (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3]);

    if (strcmp(hash_str, expected) != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Expected hash %s but found %s",
                expected, hash_str);
    }
    NL_free_v_memmgr(&mgr);
    return errors;
}

error_info **murmur_hash_test2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "murmur hash test2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    

    unsigned char *bytes = (unsigned char *) "Hello, world!";
    size_t size = strlen((char *) bytes);
    NL_hash *hash = NL_allocate_mem_size(mgr, NL_SIZEOF_HASH);
    MurmurHash3_x64_128(bytes, size, 321, hash);
    char * expected = "f86d4004ca47f42bb9546c7979200aee";
    char * hash_str = NL_allocate_mem_size(mgr, 33);
    sprintf(hash_str, "%08x%08x%08x%08x", 
            (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3]);

    if (strcmp(hash_str, expected) != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Expected hash %s but found %s",
                expected, hash_str);
    }
    NL_free_v_memmgr(&mgr);
    return errors;
}

error_info **murmur_hash_test3(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "murmur hash test3";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    

    unsigned char *bytes = (unsigned char *) "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    size_t size = strlen((char *) bytes);
    NL_hash *hash = NL_allocate_mem_size(mgr, NL_SIZEOF_HASH);
    MurmurHash3_x64_128(bytes, size, 123, hash);
    char * expected = "becf7e04dbcf74637751664ef66e73e0";
    char * hash_str = NL_allocate_mem_size(mgr, 33);
    sprintf(hash_str, "%08x%08x%08x%08x", 
            (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3]);

    if (strcmp(hash_str, expected) != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Expected hash %s but found %s",
                expected, hash_str);
    }
    NL_free_v_memmgr(&mgr);
    return errors;
}

error_info **murmur_hash_test4(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "murmur hash test4";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    

    unsigned char *bytes = (unsigned char *) "";
    size_t size = strlen((char *) bytes);
    NL_hash *hash = NL_allocate_mem_size(mgr, NL_SIZEOF_HASH);
    MurmurHash3_x64_128(bytes, size, 123, hash);
    char * expected = "4cd9597081679d1abd92f8784bace33d";
    char * hash_str = NL_allocate_mem_size(mgr, 33);
    sprintf(hash_str, "%08x%08x%08x%08x", 
            (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3]);

    if (strcmp(hash_str, expected) != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Expected hash %s but found %s",
                expected, hash_str);
    }
    NL_free_v_memmgr(&mgr);
    return errors;
}

error_info **murmur_hash_test5(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "murmur hash test5";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    

    unsigned char *bytes = (unsigned char *) "test";
    size_t size = strlen((char *) bytes);
    NL_hash *hash;
    NL_HASH(bytes, size, mgr, hash)
    char * expected = "aff084b0ce9faf0bda0f4c516ea56643";
    char * hash_str = NL_allocate_mem_size(mgr, 33);
    sprintf(hash_str, "%08x%08x%08x%08x", 
            (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3]);

    if (strcmp(hash_str, expected) != 0) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, "Expected hash %s but found %s",
                expected, hash_str);
    }
    NL_deallocate_v_mem(mgr, (void **) &hash_str);
    NL_deallocate_v_mem(mgr, (void **) &hash);

    for (int i=0; i < mgr->max_pools; i++) {
        if (mgr->pools[i]->allocs > 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Memmory pool of size %lu has %lu allocations. Expected 0.",
                mgr->pools[i]->object_size, mgr->pools[i]->allocs);

        }

    }

    NL_free_v_memmgr(&mgr);
    return errors;
}

