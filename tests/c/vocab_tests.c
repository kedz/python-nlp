#include "vocab_tests.h"
#include <unistd.h>

error_info **vocab_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "vocab test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_vocab *vocab = NL_new_vocab(mgr);

    if (vocab == NULL) {
        NEW_ERROR(80)
        sprintf((char *) this_error->msg,
            "NL_new_vocab returned NULL!");

    } else {

        if (vocab->size != 0) {
            NEW_ERROR(80)
            sprintf((char *) this_error->msg,
                "size is %lu, expected 0", vocab->size);
        }
        

        NL_deallocate_vocab(mgr, &vocab);
        if (vocab != NULL) {
            NEW_ERROR(80)
            sprintf((char *) this_error->msg,
                "Deallocate vocab did not set pointer to NULL!");


        }

        for (size_t i=0; i < mgr->max_pools; i++) {
            if (mgr->pools[i]->allocs != 0) {
                NEW_ERROR(80)
                sprintf((char *) this_error->msg,
                    "Pool of size %lu has %lu allocs, expected 0",
                    mgr->pools[i]->object_size, mgr->pools[i]->allocs);

            }
        }

    }

    NL_free_v_memmgr(&mgr);

    return errors;
}

error_info **vocab_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "vocab test2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_vocab *vocab = NL_new_vocab(mgr);

    if (vocab == NULL) {
        NEW_ERROR(80)
        sprintf((char *) this_error->msg,
            "NL_new_vocab returned NULL!");

    } else {
        
        NL_string string_yours_data = {(unsigned char *)"yours", 5, 0};

        NL_string *string_mine_data = NL_new_string(mgr, 4);
        memcpy(string_mine_data->bytes, "mine", 4);
        string_mine_data->flags = NL_OWN_DATA;

        size_t s1_id;
        int status1 = NL_get_string_id(mgr, vocab, &string_yours_data, &s1_id);
        if (s1_id != 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got string id %lu, expected 0", s1_id);
        } 
        if (status1 != NL_VOCAB_INSERT) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got status %d, expected %d", status1, NL_VOCAB_INSERT);
        }

        size_t s2_id;
        int status2 = NL_get_string_id(mgr, vocab, string_mine_data, &s2_id); 
        if (s2_id != 1) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got string id %lu, expected 1", s2_id);
        }
        if (status2 != NL_VOCAB_INSERT) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got status %d, expected %d", status2, NL_VOCAB_INSERT);
        }

        size_t s1_id2;
        int status3 = NL_get_string_id(mgr, vocab, 
                &string_yours_data, &s1_id2);
        if (s1_id2 != 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got string id %lu, expected 0", s1_id2);
        } 
        if (status3 != NL_VOCAB_FOUND) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got status %d, expected %d", status3, NL_VOCAB_FOUND);
        }

        size_t s2_id2;
        int status4 = NL_get_string_id(mgr, vocab, string_mine_data, &s2_id2); 
        if (s2_id2 != 1) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got string id %lu, expected 1", s2_id2);
        }
        if (status4 != NL_VOCAB_FOUND) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Got status %d, expected %d", status4, NL_VOCAB_FOUND);
        }

        if (vocab->size != 2) {
            NEW_ERROR(80)
            sprintf((char *) this_error->msg, "Found size %lu, expected %lu",
                vocab->size, (size_t) 2);

        }

        NL_deallocate_vocab(mgr, &vocab);
        if (vocab != NULL) {
            NEW_ERROR(80)
            sprintf((char *) this_error->msg,
                "Deallocate vocab did not set pointer to NULL!");

        }

        for (size_t i=0; i < mgr->max_pools; i++) {
            if (mgr->pools[i]->allocs != 0) {
                NEW_ERROR(80)
                sprintf((char *) this_error->msg,
                    "Pool of size %lu has %lu allocs, expected 0",
                    mgr->pools[i]->object_size, mgr->pools[i]->allocs);

            }
        }

    }

    NL_free_v_memmgr(&mgr);

    return errors;
}



error_info **vocab_testA(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "vocab test1";
    //size_t limit = 100000000;
    size_t limit =  32452843;
    //size_t limit =  86028157;
    unsigned char **words = malloc(sizeof(char *) * limit);
    size_t *ids = malloc(sizeof(size_t) * limit);
    printf("All malloced up\n");
    sleep(10);
    printf("All inserting...\n");
    for (size_t i=0; i < limit; i++) {
        ids[i] = i;
        words[i] = malloc(20);
        sprintf((char *) words[i], "num: %lu", i);
    }
    sleep(10);

    return errors;
}

error_info **vocab_test3(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "vocab test3";


    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_vocab *vocab = NL_new_vocab(mgr);

    size_t num_generated = 0;
    size_t limit = 255998;

    for (size_t c0=40; c0 < 128; c0++) {
        for (int c1=40; c1 < 128; c1++) {
            for (int c2=40; c2 < 128; c2++) {
                for (int c3=40; c3 < 128; c3++) {
                    for (int c4=40; c4 < 128; c4++) {
                        NL_string *string = NL_new_string(mgr, 5);
                        string->bytes[0] = c0;
                        string->bytes[1] = c1;
                        string->bytes[2] = c2;
                        string->bytes[3] = c3;
                        string->bytes[4] = c4;
                        string->flags = NL_OWN_DATA;
                        num_generated++;
                        size_t id;
                        int status = NL_get_string_id(mgr, vocab, string, 
                            &id);


                        if (id != num_generated - 1) {
                            NEW_ERROR(80);
                            sprintf((char *) this_error->msg, 
                                "Inserted string id %lu, expected %lu", 
                                id, num_generated-1);
                        }
                        if (status != NL_VOCAB_INSERT) {
                            NEW_ERROR(80);
                            sprintf((char *) this_error->msg, 
                                "Got status %d, expected %d", 
                                status, NL_VOCAB_INSERT);
                        }

                        if (vocab->size != num_generated) {
                            NEW_ERROR(80)
                            sprintf((char *) this_error->msg, 
                                "Found size %lu, expected %lu",
                                vocab->size, num_generated);
                        }

                        if (num_generated >= limit) {
                            c0 = c1 = c2 = c3 = c4 = 128;
                        } 
                        
                    }  
                }   
            }
        }
    }

    num_generated = 0;
    for (size_t c0=40; c0 < 128; c0++) {
        for (int c1=40; c1 < 128; c1++) {
            for (int c2=40; c2 < 128; c2++) {
                for (int c3=40; c3 < 128; c3++) {
                    for (int c4=40; c4 < 128; c4++) {
                        NL_string *string = NL_new_string(mgr, 5);
                        string->bytes[0] = c0;
                        string->bytes[1] = c1;
                        string->bytes[2] = c2;
                        string->bytes[3] = c3;
                        string->bytes[4] = c4;
                        string->flags = NL_OWN_DATA;
                        num_generated++;
                        size_t id;
                        int status = NL_get_string_id(mgr, vocab, string, 
                            &id);

                        if (id != num_generated - 1) {
                            NEW_ERROR(80);
                            sprintf((char *) this_error->msg, 
                                "Got string id %lu, expected %lu", 
                                id, num_generated-1);
                        }
                        if (status != NL_VOCAB_FOUND) {
                            NEW_ERROR(80);
                            sprintf((char *) this_error->msg, 
                                "Got status %d, expected %d", 
                                status, NL_VOCAB_FOUND);
                        }

                        if (vocab->size != limit ) {
                            NEW_ERROR(80)
                            sprintf((char *) this_error->msg, 
                                "Found size %lu, expected %lu",
                                vocab->size, limit );
                        }
                        
                        NL_deallocate_v_mem(mgr, (void **) &string);

                        if (num_generated >= limit) {
                            c0 = c1 = c2 = c3 = c4 = 128;
                        } 
                        
                    }  
                }   
            }
        }
    }

    NL_deallocate_vocab(mgr, &vocab);
    for (size_t i=0; i < mgr->max_pools; i++) {
        if (mgr->pools[i]->allocs != 0) {
            NEW_ERROR(80)
            sprintf((char *) this_error->msg,
                "Pool of size %lu has %lu allocs, expected 0",
                mgr->pools[i]->object_size, mgr->pools[i]->allocs);

        }
    }

    return errors;
}
