#include "ontonotes_tests.h"

error_info **tokenizer_test1(char **name, size_t *num_errors) {

    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ontonotes test1";

    unsigned char * onbuf = (unsigned char *)
"------------------------------------------------------------------------------------------------------------------------\
\
Plain sentence:\
---------------\
    Pierre Vinken, 61 years old, will join the board as a nonexecutive director Nov. 29.\
\
Treebanked sentence:\
--------------------\
    Pierre Vinken , 61 years old , will join the board as a nonexecutive director Nov. 29 .\
\
Tree:\
-----\
    (TOP (S (NP-SBJ (NP (NNP Pierre)\
                        (NNP Vinken))\
                    (, ,)\
                    (ADJP (NML (CD 61)\
                               (NNS years))\
                          (JJ old))\
                    (, ,))\
            (VP (MD will)\
                (VP (VB join)\
                    (NP (DT the)\
                        (NN board))\
                    (PP-CLR (IN as)\
                            (NP (DT a)\
                                (JJ nonexecutive)\
                                (NN director)))\
                    (NP-TMP (NNP Nov.)\
                            (CD 29))))\
            (. .)))\
";
    
                                    


