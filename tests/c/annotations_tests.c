#include "annotations_tests.h"

error_info **annotations_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "annotations test 1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_annotations *ann = NL_new_bspan_annotations(mgr);

    if (ann == NULL) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, 
                "NL_new_bspan_annotations returned NULL!");

    } else {
        if (ann->size != 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found size %lu but expected 0!",
               ann->size);
        } 

        if (ann->_object_size != sizeof(NL_bspan)) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found obect size %lu but expected %lu!",
               ann->_object_size, sizeof(NL_bspan));
        }

        NL_deallocate_bspan_annotations(mgr, &ann);
        if (ann != NULL) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "NL_deallocate_bspan_annotations did not return NULL!");
        }
    }



    for (size_t i=0; i < mgr->max_pools; i++) {
        if (mgr->pools[i]->allocs > 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Memory pool size %lu has %lu allocs, expected 0",
                mgr->pools[i]->object_size, mgr->pools[i]->allocs);

        }
    }

    NL_free_v_memmgr(&mgr);


    return errors;
}

error_info **annotations_test2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "annotations test 2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_annotations *ann = NL_new_bspan_annotations(mgr);

    if (ann == NULL) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, 
                "NL_new_bspan_annotations returned NULL!");

    } else {
        if (ann->size != 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found size %lu but expected 0!",
               ann->size);
        } 

        if (ann->_object_size != sizeof(NL_bspan)) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found obect size %lu but expected %lu!",
               ann->_object_size, sizeof(NL_bspan));
        }

        NL_NEW_BUFFER(buffer, "This is a test.")
        NL_add_bspan(mgr, ann, buffer.bytes, 4, NULL, 0);
        if (ann->size != 1) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found size %lu but expected 1!",
               ann->size);
        }
        
        NL_bspan *span = NL_get_bspan(ann, 0);
        if (span->bytes != buffer.bytes) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
                "Span points to wrong bytes!");
        }
        if (span->size != 4) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
                "Found size %lu, but expected 4", span->size);
        }

        if (ann->_list_size != NL_BASE_ANN_LIST_SIZE) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
                "Found _list_size %lu, but expected %d", 
                ann->_list_size, NL_BASE_ANN_LIST_SIZE);
        }

        NL_deallocate_bspan_annotations(mgr, &ann);
        if (ann != NULL) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "NL_deallocate_bspan_annotations did not return NULL!");
        }

    }

    for (size_t i=0; i < mgr->max_pools; i++) {
        if (mgr->pools[i]->allocs > 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Memory pool size %lu has %lu allocs, expected 0",
                mgr->pools[i]->object_size, mgr->pools[i]->allocs);

        }
    }

    NL_free_v_memmgr(&mgr);


    return errors;
}

error_info **annotations_test3(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "annotations test 3";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    NL_annotations *ann = NL_new_bspan_annotations(mgr);

    if (ann == NULL) {
        NEW_ERROR(80);
        sprintf((char *) this_error->msg, 
                "NL_new_bspan_annotations returned NULL!");

    } else {
        if (ann->size != 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found size %lu but expected 0!",
               ann->size);
        } 

        if (ann->_object_size != sizeof(NL_bspan)) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg,
               "Found obect size %lu but expected %lu!",
               ann->_object_size, sizeof(NL_bspan));
        }

        NL_NEW_BUFFER(buffer, "This is a test.")
        
        for (size_t i=0; i < 1000000; i++) {
            NL_add_bspan(mgr, ann, buffer.bytes, 4, NULL, 0);
            if (ann->size != i + 1) {
                NEW_ERROR(80);
                sprintf((char *) this_error->msg,
                   "Found size %lu but expected 1!",
                   ann->size);
            }
            
            NL_bspan *span = NL_get_bspan(ann, i);
            if (span->bytes != buffer.bytes) {
                NEW_ERROR(80);
                sprintf((char *) this_error->msg,
                    "Span points to wrong bytes!");
            }
            if (span->size != 4) {
                NEW_ERROR(80);
                sprintf((char *) this_error->msg,
                    "Found size %lu, but expected 4", span->size);
            }
        }

        NL_deallocate_bspan_annotations(mgr, &ann);
        if (ann != NULL) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "NL_deallocate_bspan_annotations did not return NULL!");
        }

    }

    for (size_t i=0; i < mgr->max_pools; i++) {
        if (mgr->pools[i]->allocs > 0) {
            NEW_ERROR(80);
            sprintf((char *) this_error->msg, 
                "Memory pool size %lu has %lu allocs, expected 0",
                mgr->pools[i]->object_size, mgr->pools[i]->allocs);

        }
    }

    NL_free_v_memmgr(&mgr);


    return errors;
}

