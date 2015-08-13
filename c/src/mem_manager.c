#include "mem_manager.h"
#include <stdlib.h>

struct NL_memmgr {

    int temp;

};

NL_memmgr *NL_new_memmgr() {
    NL_memmgr *m = malloc(sizeof(NL_memmgr));
    m->temp = 42;
    return m;
}

void NL_free_memmgr(NL_memmgr **m_ptr) {
    free(*m_ptr);
    *m_ptr = NULL;
}
