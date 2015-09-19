#include "ptb_inputs_test.h"
#include "memmgr_test.h"
#include "tokenizer_utils_tests.h"
#include "tokenizer_tests.h"

int run_tests(test_func *test_funcs, size_t num_tests, int verbose) {
    for (int i=0; i < num_tests; i++) {
        char **name = malloc(sizeof(char *));
        error_info **errors = NULL;
        size_t num_errors = 0;
        errors = (*test_funcs[i]) (name, &num_errors);
        char *status;
        if (num_errors == 0) {
            status = "OK";
        } else {
            status = "FAIL";
        }
        printf("%s ... %s\n", *name, status);
        for (int e=0; e<num_errors; e++) {
            if (verbose == 1) {
                printf("Error %d: %s\n", e, errors[e]->msg);
            }
            free(errors[e]->msg);
            free(errors[e]);
        }
        free(errors);
        free(name);

    }

    return 0;
}

int main(int argc, char *argv[]) {

    char *usage = "ptb_inputs_test [-v] [-h]\n"
        "\t-v\tverbose, print error messages\n"
        "\t-h\tdisplay this message\n";

    int verbose = 0;

    for (int i=0; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            printf("%s", usage);
            exit(0);
        }

    }

    MEMMGR_TESTS(memmgr_tests);
    run_tests((test_func *) &memmgr_tests, NUM_MEMMGR_TESTS, verbose);
    TOK_UTILS_TESTS(tok_utils_tests);
    run_tests((test_func *) &tok_utils_tests, NUM_TOK_UTILS_TESTS, verbose);
    PTB_INPUTS_TESTS(ptb_inputs_tests);
    run_tests((test_func *) &ptb_inputs_tests, NUM_PTB_INPUTS_TESTS, verbose);
    TOKENIZER_TESTS(tokenizer_tests);
    run_tests((test_func *) &tokenizer_tests, NUM_TOKENIZER_TESTS, verbose);

}
