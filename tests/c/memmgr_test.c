#include "memmgr_test.h"

error_info **memmgr_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "NL_new_memmgr test";

    NL_memmgr *mgr = NULL; //NL_new_v_memmgr(256);

    if (mgr == NULL) {
        NEW_ERROR(strlen("NL_memmgr is null.") + 1);
        sprintf((char *) this_error->msg, "NL_memmgr is null.");
    }

    return errors;
}
