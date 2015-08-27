#ifndef H_NL_MEMMGR
#define H_NL_MEMMGR


#include <stddef.h>


typedef struct NL_mem_list NL_mem_list;
struct NL_mem_list {
    NL_mem_list *next;
    unsigned char * data;   
};

typedef struct NL_memmgr {
    size_t block_size;
    size_t object_size;
    size_t actual_block_size;
    size_t actual_object_size;
    size_t available;
    NL_mem_list *free_list;
    NL_mem_list *mem_list;
    NL_mem_list *empty_containers;
    
} NL_memmgr;

typedef struct NL_v_memmgr {
    size_t num_pools;
    size_t max_pools;
    size_t **pool_sizes;
    size_t block_size;
    NL_memmgr **pools;    

} NL_v_memmgr;

NL_v_memmgr *NL_new_v_memmgr(size_t block_size);
void NL_free_v_memmgr(NL_v_memmgr **);

void *NL_allocate_mem_size(NL_v_memmgr *mgr, size_t object_size);
void NL_deallocate_v_mem(NL_v_memmgr *mgr, void *data);
void *NL_allocate_16_mem(NL_v_memmgr *mgr);
void *NL_allocate_32_mem(NL_v_memmgr *mgr);

NL_memmgr *NL_new_memmgr(size_t block_size, size_t object_size);
void NL_free_memmgr(NL_memmgr **m_ptr);

void *NL_allocate_mem(NL_memmgr *mgr);
void NL_deallocate_mem(NL_memmgr *mgr, void * data);

#endif
