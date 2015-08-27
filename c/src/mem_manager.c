#include "mem_manager.h"
#include "document.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

inline NL_v_memmgr *NL_new_v_memmgr(size_t block_size) {
    NL_v_memmgr *manager = malloc(sizeof(NL_v_memmgr));
    if (manager != NULL) {
        manager->block_size = block_size;
        manager->max_pools = 8;
        manager->pools = malloc(sizeof(NL_memmgr*) * manager->max_pools);
        size_t size = 1;
        for (int i=0; i < manager->max_pools; i++) {
            size = size * 2;
            manager->pools[i] = NL_new_memmgr(block_size, size);
        }

    }

    return manager;
}

static const int tab64[64] = {
    63,  0, 58,  1, 59, 47, 53,  2,
    60, 39, 48, 27, 54, 33, 42,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5};

static inline int log2_64 (uint64_t value) {
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value |= value >> 32;
    return tab64[
        ((uint64_t)((value - (value >> 1))*0x07EDD5E59A4E28C2)) >> 58];
}

inline void *NL_allocate_mem_size(NL_v_memmgr *mgr, size_t object_size) {

    int bucket = log2_64((uint64_t) object_size);
    if (bucket >= mgr->max_pools) {
        //printf("I am allocating bucket %d\n", bucket);
        mgr->pools = realloc(mgr->pools, sizeof(NL_memmgr*) * (bucket + 1));
        size_t size = mgr->pools[mgr->max_pools-1]->object_size;
        for (int i=mgr->max_pools; i < bucket + 1; i++) {
            size = size * 2;
            //printf("Allocating new pool of size %lu at position %d\n",
            //    size, i);
            mgr->pools[i] = NL_new_memmgr(mgr->block_size, size);
        }
        mgr->max_pools = bucket + 1;
        //for (int i=0; i < mgr->max_pools; i++) {
        //    printf("%lu, ", mgr->pools[i]->object_size);
        //}
       // printf("\n");

    }

    //printf("%lu : %d slot with size %lu\n", 
    //    object_size, bucket, mgr->pools[bucket]->object_size);    
    return NL_allocate_mem(mgr->pools[bucket]);

}

inline void *NL_allocate_16_mem(NL_v_memmgr *mgr) {
    return NL_allocate_mem(mgr->pools[3]);
}

inline void *NL_allocate_32_mem(NL_v_memmgr *mgr) {
    return NL_allocate_mem(mgr->pools[4]);
}

inline void NL_deallocate_v_mem(NL_v_memmgr *mgr, void *data) {

    size_t object_size;
    for (int i=0; i < mgr->max_pools; i++) {
        object_size = mgr->pools[i]->object_size;
        unsigned char * guard_byte = ((unsigned char *) data) + object_size;
        if (*guard_byte == 0xDE && *(guard_byte + 1) == 0xAD) {
            return NL_deallocate_mem(mgr->pools[i], data);   
        }
    }

    fprintf(stderr, 
        "Warning: deallocation of variably sized memory failed.\n"
        "Couldn't find guard bytes.\n");

    return;
}


inline void NL_free_v_memmgr(NL_v_memmgr ** mgr) {
    if (mgr != NULL) {
        for (int i=0; i < (*mgr)->max_pools; i++) {
            NL_free_memmgr(&(*mgr)->pools[i]);
        }
        free((*mgr)->pools);
        free(*mgr);
        *mgr = NULL;
            
    }
}

inline NL_memmgr *NL_new_memmgr(size_t block_size, size_t object_size) {
    NL_memmgr *m = malloc(sizeof(NL_memmgr));
    if (m != NULL) {
        m->block_size = block_size;
        m->object_size = object_size;
        m->actual_block_size = (object_size + 2) * block_size;
        m->actual_object_size = object_size + 2;
        m->available = 0;
        m->free_list = NULL;
        m->mem_list = NULL;
        m->empty_containers = NULL;
    }

    return m;
}



inline void __NL_allocate_block(NL_memmgr *mgr) {
    //void *block = malloc(mgr->actual_block_size);
    void *block = calloc(1, mgr->actual_block_size);
    NL_mem_list *block_container = malloc(sizeof(NL_mem_list));

    if (block == NULL || block_container == NULL) {
        fprintf(stderr, "NL_memmgr failed to allocate new block.\n"); 
        exit(1);
    }

    block_container->data = block;
    size_t guard_start = mgr->object_size; 
    //size_t block_size = mgr->block_size;
    

    for (int i=0; i < mgr->actual_block_size; i+=mgr->actual_object_size) {

        unsigned char *guard_byte = &((unsigned char *)block)[i] + guard_start;
        *guard_byte = 0xde;
        guard_byte++; 
        *guard_byte = 0xad;   //end of block
        //guard_byte++;
        /*guard_byte = 0x00;   //block is available
        guard_byte = (block_size & 0xFF);
        guard_byte++;
        *guard_byte = 0x00;   //block is available
        guard_byte = ((block_size >> 8) & 0xFF);
    */
        NL_mem_list *object_container = malloc(sizeof(NL_mem_list));

        if (object_container == NULL) {
            fprintf(stderr, "NL_memmgr failed to allocate new block.\n"); 
            exit(1);
        }
        object_container->data = &((unsigned char *) block)[i];
        object_container->next = mgr->free_list;
        mgr->free_list = object_container;

    }

    block_container->next = mgr->mem_list;
    mgr->mem_list = block_container;
    
    mgr->available += mgr->block_size;
}

inline void *NL_allocate_mem(NL_memmgr *mgr) {
    if (mgr->available == 0) {
        __NL_allocate_block(mgr);
    }
   
    NL_mem_list *container = mgr->free_list;
    mgr->free_list = container->next;
    
    container->next = mgr->empty_containers;
    mgr->empty_containers = container;
    mgr->available -= 1;

    return (void *) container->data;
}

inline void NL_deallocate_mem(NL_memmgr *mgr, void *data) {
    NL_mem_list *container = mgr->empty_containers;
    mgr->empty_containers = container->next;
     
    container->data = data;
    container->next = mgr->free_list;
    mgr->free_list = container;
    mgr->available += 1;


}

inline void __NL_release_pool(NL_memmgr *mgr) {
    NL_mem_list *next = mgr->free_list;
    for (; next; next = mgr->free_list) {
        mgr->free_list = mgr->free_list->next;
        free(next);
    }

    next = mgr->empty_containers;
    for (; next; next = mgr->empty_containers) {
        mgr->empty_containers = mgr->empty_containers->next;
        free(next);
    }

    next = mgr->mem_list;
    for (; next; next = mgr->mem_list) {
        mgr->mem_list = mgr->mem_list->next;
        free(next->data);
        free(next);
    }

}

inline void NL_free_memmgr(NL_memmgr **m_ptr) {
    
    __NL_release_pool(*m_ptr);
    free(*m_ptr);
    *m_ptr = NULL;
}
