#include "annotations.h"

NL_annotations *NL_new_bspan_annotations(NL_v_memmgr *mgr) {
    NL_annotations *ann = NL_allocate_mem_size(mgr, sizeof(NL_annotations));
    if (ann != NULL) {

        ann->size = 0;
        ann->_object_size = sizeof(NL_bspan);
        ann->_num_lists = 1;
        ann->_max_lists = NL_BASE_ANN_LISTS_SIZE;
        ann->_current_position = 0;
        ann->_lists = NL_allocate_mem_size(
            mgr, sizeof(void *) * NL_BASE_ANN_LISTS_SIZE);
        if (ann->_lists != NULL) {
            ann->_lists[0] = NL_allocate_mem_size(
                mgr, ann->_object_size * NL_BASE_ANN_LIST_SIZE);
        } else {
            return NULL;
        }

        ann->flags = 0;
    }    
    return ann;
}

NL_annotations *NL_new_sspan_annotations(NL_v_memmgr *mgr) {
    NL_annotations *ann = NL_allocate_mem_size(mgr, sizeof(NL_annotations));
    if (ann != NULL) {

        ann->size = 0;
        ann->_object_size = sizeof(NL_sspan);
        ann->_num_lists = 1;
        ann->_max_lists = NL_BASE_ANN_LISTS_SIZE;
        ann->_current_position = 0;
        ann->_lists = NL_allocate_mem_size(
            mgr, sizeof(void *) * NL_BASE_ANN_LISTS_SIZE);
        if (ann->_lists != NULL) {
            ann->_lists[0] = NL_allocate_mem_size(
                mgr, ann->_object_size * NL_BASE_ANN_LIST_SIZE);
        } else {
            return NULL;
        }

        ann->flags = 0;
    }    
    return ann;
}

#define ALLOCATE_NEW_LISTS                                                    \
    if (ann->_num_lists >= ann->_max_lists) {                                 \
        ann->_max_lists = ann->_max_lists * 2;                                \
        void **_new_lists = NL_allocate_mem_size(                             \
            mgr, sizeof(void *) * ann->_max_lists);                           \
        memcpy(_new_lists, ann->_lists, ann->_num_lists * sizeof(void *));    \
        NL_deallocate_v_mem(mgr, (void **) &ann->_lists);                     \
        ann->_lists = _new_lists;                                             \
    }                                                                         \
    ann->_num_lists++;                                                        \
    ann->_lists[ann->_num_lists - 1] = NL_allocate_mem_size(                  \
        mgr, ann->_object_size * NL_BASE_ANN_LIST_SIZE);                      \
    ann->_current_position = 0;                                               \


inline void NL_add_bspan(NL_v_memmgr *mgr, NL_annotations *ann, 
        unsigned char *bytes, size_t size, void *data, NL_flags flags) {

    if (ann->_current_position >= NL_BASE_ANN_LIST_SIZE) {
        ALLOCATE_NEW_LISTS
    }
    
    NL_bspan *span = ann->_lists[ann->_num_lists - 1] 
        + ann->_object_size * ann->_current_position;
    span->bytes = bytes;
    span->size = size;
    //fwrite(span->bytes, 1, span->size, stdout);
    //fwrite("\n", 1, 1, stdout);
    span->data = data;
    span->flags = flags;
    ann->size++;
    ann->_current_position++;

}

inline void NL_add_sspan(NL_v_memmgr *mgr, NL_annotations *ann, 
        size_t span_id, size_t size, void *data, NL_flags flags) {
    if (ann->_current_position >= NL_BASE_ANN_LIST_SIZE) {
        ALLOCATE_NEW_LISTS
    }
    
    NL_sspan *span = ann->_lists[ann->_num_lists - 1] 
        + ann->_object_size * ann->_current_position;
    span->span_id = span_id;
    span->size = size;
    span->data = data;
    span->flags = flags;
    ann->size++;
    ann->_current_position++;


}

inline NL_bspan *NL_get_bspan(NL_annotations *ann, size_t index) {
    if (index < ann->size) {
        size_t block = 0;
        while (index >= NL_BASE_ANN_LIST_SIZE) {
            index = index - NL_BASE_ANN_LIST_SIZE;
            block++;
        }
   
        return (NL_bspan *) (ann->_lists[block] + index * ann->_object_size);
    } else {
        return NULL;
    }
}

inline NL_sspan *NL_get_sspan(NL_annotations *ann, size_t index) {
     if (index < ann->size) {
        size_t block = 0;
        while (index >= NL_BASE_ANN_LIST_SIZE) {
            index = index - NL_BASE_ANN_LIST_SIZE;
            block++;
        }
   
        return (NL_sspan *) (ann->_lists[block] + index * ann->_object_size);
    } else {
        return NULL;
    }       
}

void NL_deallocate_bspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann) {
    NL_bspan *span = NULL;
    for (size_t i = 0; i < (*ann)->size; i++) {
        span = NL_get_bspan(*ann, i);
        if ((span->flags & NL_OWN_DATA) && span->data != NULL) {
            NL_deallocate_v_mem(mgr, (void **) &(span->data)); 
        }
    }
    for (size_t i=0; i < (*ann)->_num_lists; i++) {
        NL_deallocate_v_mem(mgr, &(*ann)->_lists[i]);
    }

    NL_deallocate_v_mem(mgr, (void **) &(*ann)->_lists);
    NL_deallocate_v_mem(mgr, (void **) ann);
}

void NL_deallocate_sspan_annotations(NL_v_memmgr *mgr, NL_annotations **ann) {
    NL_sspan *span = NULL;
    for (size_t i = 0; i < (*ann)->size; i++) {
        span = NL_get_sspan(*ann, i);
        if ((span->flags & NL_OWN_DATA) && span->data != NULL) {
            NL_deallocate_v_mem(mgr, (void **) &(span->data)); 
        }
    }
    for (size_t i=0; i < (*ann)->_num_lists; i++) {
        NL_deallocate_v_mem(mgr, &(*ann)->_lists[i]);
    }

    NL_deallocate_v_mem(mgr, (void **) &(*ann)->_lists);
    NL_deallocate_v_mem(mgr, (void **) ann);

}


NL_string *NL_new_string(NL_v_memmgr *mgr, size_t size) {
    void *data = NL_allocate_mem_size(mgr, size + sizeof(NL_string));
    if (data == NULL)
        return NULL;
    NL_string *string = data;
    string->bytes = data + sizeof(NL_string);
    string->size = size;
    return string;
}

