#include "annotations.h"

NL_annotations *NL_new_bspan_annotations(NL_v_memmgr *mgr) {
    NL_annotations *ann = NL_allocate_mem_size(mgr, sizeof(NL_annotations));
    if (ann != NULL) {

        ann->size = 0;
        ann->_object_size = sizeof(NL_bspan);
        ann->_list_size = NL_BASE_ANN_LIST_SIZE;
        ann->list = NL_allocate_mem_size(
            mgr, NL_BASE_ANN_LIST_SIZE * ann->_object_size);

        if (ann->list == NULL)
            return NULL;
    }    
    return ann;
}

inline void NL_add_bspan(NL_v_memmgr *mgr, NL_annotations *ann, 
        unsigned char *bytes, size_t size, void *data, NL_flags flags) {

    if (ann->size >= ann->_list_size) {
        ann->_list_size = ann->_list_size * 2;
        void *new_list = NL_allocate_mem_size(
           mgr, ann->_list_size * ann->_object_size);
        if (new_list == NULL) {
            printf("EXITING BADNESS!\n");
            exit(1); // This is bad!
        }
        memcpy(new_list, ann->list, ann->size * ann->_object_size);        
        NL_deallocate_v_mem(mgr, (void **) &ann->list);
        ann->list = new_list;
    } 
    NL_bspan *span = ann->list + ann->size * ann->_object_size;
    span->bytes = bytes;
    span->size = size;
    span->data = data;
    span->flags = flags;
    ann->size++;

}

inline NL_bspan *NL_get_bspan(NL_annotations *ann, size_t index) {
    if (index < ann->size) {
        return (NL_bspan *) (ann->list + index * ann->_object_size);
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
    NL_deallocate_v_mem(mgr, (void **) &(*ann)->list);
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

