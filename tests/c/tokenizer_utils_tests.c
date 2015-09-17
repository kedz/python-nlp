#include "tokenizer_utils_tests.h"


error_info **tutils_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for normed spaces and escaped slashes";

    unsigned char *buf1 = (unsigned char *) 
        "there are /4\\/\\\\/\\ spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2 + 4;
    size_t pred_escape_size = NL_get_size_normalized_spaces_slashes(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test2(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: norm spaces and escap slashes";


    unsigned char *buf1 = (unsigned char *) 
        "there are /4\\/\\\\/\\ spaces ";
    unsigned char *gold1 = (unsigned char *) 
        "there\xC2\xA0" "are\xC2\xA0\\/4\\/\\\\\\/\\" "\xC2\xA0spaces\xC2\xA0";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 2 + 4;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_normalize_parens_slashes(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test3(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for normed spaces and parens";

    unsigned char *buf1 = (unsigned char *) 
        "there are (4) spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2*4 + 4;
    size_t pred_escape_size = NL_get_size_normalized_spaces_parens(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test4(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: norm spaces and parens";


    unsigned char *buf1 = (unsigned char *) 
        "there are (3) spaces";
    unsigned char *gold1 = (unsigned char *) 
        "there\xC2\xA0" "are\xC2\xA0-LRB-3-RRB-\xC2\xA0spaces";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4*2 + 3;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_normalize_parens_spaces(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test5(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for normed parens";

    unsigned char *buf1 = (unsigned char *) 
        "there are (4 )spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2*4;
    size_t pred_escape_size = NL_get_size_normalized_parentheses(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test6(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: norm parens";


    unsigned char *buf1 = (unsigned char *) 
        "there are (4) spaces";
    unsigned char *gold1 = (unsigned char *) 
        "there are -LRB-4-RRB- spaces";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4*2;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_normalize_parentheses(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test7(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for normed space";

    unsigned char *buf1 = (unsigned char *) 
        "there are 4 spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 4;
    size_t pred_escape_size = NL_get_size_normalized_spaces(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test8(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: norm spaces";


    unsigned char *buf1 = (unsigned char *) 
        "there are 4 spaces ";
    unsigned char *gold1 = (unsigned char *) 
        "there\xc2\xa0" "are\xc2\xa0" "4\xc2\xa0spaces\xc2\xa0";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_normalize_spaces(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test9(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for escaped f slash and asterisk";

    unsigned char *buf1 = (unsigned char *) 
        "\\/ / * \\*";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2;
    size_t pred_escape_size = NL_get_size_escaped_forward_slash_asterisk(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test10(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: escape f slash and asterisk";


    unsigned char *buf1 = (unsigned char *) 
        "/ \\/ * \\*";
    unsigned char *gold1 = (unsigned char *) 
        "\\/ \\/ \\* \\*";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 2;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_escape_forward_slash_asterisk(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test11(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: norm amp";


    unsigned char *buf1 = (unsigned char *) 
        "&amp; &amp! &amp &am! &am &a! &a &! & &am";
    unsigned char *gold1 = (unsigned char *) 
        "& &amp! &amp &am! &am &a! &a &! & &am";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_normalize_ampersand(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test12(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: copy no softhyphens";


    unsigned char *buf1 = (unsigned char *) 
        "hy\xC2\xADphe\xC2\xADna\xC2\xADted";
    unsigned char *gold1 = (unsigned char *) "hyphenated";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_copy_no_softhyphen(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test13(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for unicode quotes";

    unsigned char *buf1 = (unsigned char *) 
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    size_t buf1_size = strlen((char *) buf1);
    unsigned char *gold = (unsigned char *)
        "\xE2\x80\x98 \xE2\x80\x9C \xE2\x80\x9C \xE2\x80\x98"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";
    size_t gold_escape_size = strlen((char *) gold);
    size_t pred_escape_size = NL_get_size_unicode_quotes(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test14(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: left unicode quotes transform";


    unsigned char *buf1 = (unsigned char *) 
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    unsigned char *gold1 = (unsigned char *) 
        "\xE2\x80\x98 \xE2\x80\x9C \xE2\x80\x9C \xE2\x80\x98"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_unicode_quotes_probably_left(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test15(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: right unicode quotes transform";


    unsigned char *buf1 = (unsigned char *) 
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    unsigned char *gold1 = (unsigned char *) 
        "\xE2\x80\x99 \xE2\x80\x9D \xE2\x80\x9D \xE2\x80\x99"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_unicode_quotes_probably_right(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test16(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for ascii quotes";

    unsigned char *buf1 = (unsigned char *) 
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D \xC2\x80\x9E "
        "\xC2\xAB \xC2\xBB";
    size_t buf1_size = strlen((char *) buf1);
    unsigned char *gold = (unsigned char *)
        "' ' ' ' ' ' ' ' ' ' \" \" \" \" \" \" \" \" \"";
    size_t gold_escape_size = strlen((char *) gold);
    size_t pred_escape_size = NL_get_size_ascii_quotes(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test17(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: ascii quotes transform";


    unsigned char *buf1 = (unsigned char *) 
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D \xC2\x80\x9E "
        "\xC2\xAB \xC2\xBB";
    unsigned char *gold1 = (unsigned char *) 
        "' ' ' ' ' ' ' ' ' ' \" \" \" \" \" \" \" \" \"";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_ascii_quotes(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test18(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: get size for latex quotes";

    unsigned char *buf1 = (unsigned char *) 
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";

    size_t buf1_size = strlen((char *) buf1);
    unsigned char *gold = (unsigned char *)
        "` ` ` ` ' ' ' ` ` ' `` `` `` `` '' '' `` ''";
    size_t gold_escape_size = strlen((char *) gold);
    size_t pred_escape_size = NL_get_size_latex_quotes(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        NEW_ERROR(200)
        sprintf((char *) this_error->msg,
            "Size should be %lu but function returned %lu",
            gold_escape_size, pred_escape_size);
    }

    return errors;
}

error_info **tutils_test19(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: left latex quotes transform";


    unsigned char *buf1 = (unsigned char *) 
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";
    unsigned char *gold1 = (unsigned char *) 
        "` ` ` ` ' ' ' ` ` ' `` `` `` `` '' '' `` ''";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_latex_quotes_probably_left(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}

error_info **tutils_test20(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "tok utils: left latex quotes transform";


    unsigned char *buf1 = (unsigned char *) 
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";
    unsigned char *gold1 = (unsigned char *) 
        "' ' ` ` ' ' ' ` ` ' '' '' `` `` '' '' `` ''";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = strlen((char *) gold1);
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size + 1);
    trans1[escape_size] = '\0';

    NL_latex_quotes_probably_right(buf1, buf1_size, trans1);

    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        NEW_ERROR(400)
        sprintf((char *) this_error->msg,
            "Expected: \"%s\" but got \"%s\"",
            gold1, trans1);
    }

    free(trans1);
    return errors;
}
