#ifndef H_NL_TESTS
#define H_NL_TESTS

typedef struct error_info {
    unsigned char *test_name;
    unsigned char *msg;
} error_info;

typedef error_info** (*test_func) (char **, size_t*);

#define NEW_ERROR(msg_size)                                                   \
    *num_errors += 1;                                                         \
    errors = realloc(errors, *num_errors * sizeof(error_info *));             \
    errors[*num_errors -1] = malloc(sizeof(error_info));                      \
    error_info *this_error = errors[*num_errors -1];                          \
    errors[*num_errors-1]->msg = malloc(sizeof(char) * msg_size);             \


#endif
