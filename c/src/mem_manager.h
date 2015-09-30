#ifndef H_NL_MEMMGR
#define H_NL_MEMMGR

#include <stddef.h>
#include <inttypes.h>
#include <stdint.h>

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
    size_t allocs;
    unsigned char id_byte;
} NL_memmgr;

typedef struct NL_v_memmgr {
    size_t max_pools;
    size_t block_size;
    NL_memmgr **pools;    

} NL_v_memmgr;

NL_v_memmgr *NL_new_v_memmgr(size_t block_size);
void NL_free_v_memmgr(NL_v_memmgr **);

void *NL_allocate_mem_size(NL_v_memmgr *mgr, size_t object_size);
void NL_deallocate_v_mem(NL_v_memmgr *mgr, void **data);
void *NL_allocate_16_mem(NL_v_memmgr *mgr); // test these and edge cases 0 and too big
void *NL_allocate_32_mem(NL_v_memmgr *mgr);

NL_memmgr *NL_new_memmgr(size_t block_size, size_t object_size, 
    unsigned char id_byte);
void NL_free_memmgr(NL_memmgr **m_ptr);

void *NL_allocate_mem(NL_memmgr *mgr);
void NL_deallocate_mem(NL_memmgr *mgr, void **data);

void __NL_allocate_block(NL_memmgr *mgr);
void __NL_release_pool(NL_memmgr *mgr);
#define NL_V_MEMMGR_INIT_POOL_SIZE 8

#endif
