#include "ptb_inputs_test.h"


#define TOKEN_TEST                                                            \
  size_t *num_tokens = NL_allocate_mem_size(mgr, sizeof(size_t));             \
  *num_tokens = 0;                                                            \
  NL_span **tokens = NL_tokenize_buf(buf, buf_len, num_tokens, cfg, mgr);    \
  for (int i=0; i < *num_tokens; i++) {                                       \
      if (i < gold_num_tokens) {                                              \
          unsigned char *token = NULL;                                        \
          size_t token_length = 0;                                            \
          if (tokens[i]->label_length > 0) {                                  \
              token = tokens[i]->label;                                       \
              token_length = tokens[i]->label_length;                         \
          } else {                                                            \
              token = tokens[i]->start;                                       \
              token_length = tokens[i]->length;                               \
          }                                                                   \
          unsigned char *gold_token = gold[i];                                \
          size_t gold_length = strlen((char *) gold_token);                   \
          if (token_length != gold_length                                     \
                      || memcmp(token, gold_token, token_length) != 0) {      \
                                                                              \
              *num_errors += 1;                                               \
              errors = realloc(errors, *num_errors * sizeof(error_info *));   \
              errors[*num_errors -1] = malloc(sizeof(error_info));            \
              error_info *this_error = errors[*num_errors -1];                \
              this_error->msg = NULL;                                         \
                                                                              \
              size_t cpy_s1 = strlen("Tokenizer returned \"");                \
              size_t cpy_s2 = strlen("\" but expected \"");                   \
              size_t cpy_s3 = strlen("\".");                                  \
              size_t msg_size = cpy_s1 + cpy_s2 + cpy_s3                      \
                  + token_length + gold_length + 1;                           \
              this_error->msg = malloc(sizeof(char) * msg_size);              \
              this_error->msg[msg_size-1] = '\0';                             \
              memcpy(this_error->msg, "Tokenizer returned \"", cpy_s1);       \
              memcpy(&this_error->msg[cpy_s1], token, token_length);          \
              memcpy(&this_error->msg[cpy_s1 + token_length],                 \
                     "\" but expected \"", cpy_s2);                           \
              memcpy(&this_error->msg[cpy_s1 + token_length + cpy_s2],        \
                     gold_token, gold_length);                                \
              memcpy(                                                         \
                  &this_error->msg[cpy_s1+token_length+cpy_s2+gold_length],   \
                  "\".", cpy_s3);                                             \
          }                                                                   \
      }                                                                       \
      NL_free_span(&tokens[i], mgr);                                          \
  }                                                                           \
  NL_deallocate_v_mem(mgr, tokens);                                           \
  NL_deallocate_v_mem(mgr, cfg);                                              \
                                                                              \
  if (*num_tokens != gold_num_tokens) {                                       \
      *num_errors += 1;                                                       \
      errors = realloc(errors, *num_errors * sizeof(error_info *));           \
      errors[*num_errors -1] = malloc(sizeof(error_info));                    \
      error_info *this_error = errors[*num_errors -1];                        \
      this_error->msg = malloc(sizeof(char *) *200);                          \
                                                                              \
      sprintf(                                                                \
          (char *) this_error->msg,                                           \
          "Tokenizer returned %lu tokens, should be %lu.",                    \
          *num_tokens, gold_num_tokens);                                      \
                                                                              \
  }                                                                           \
                                                                              \
  NL_deallocate_v_mem(mgr, num_tokens);                                       \
                                                                              \
  int pool_size = 2;                                                          \
  for (int i=0; i < mgr->max_pools; i++) {                                    \
      unsigned int allocs = mgr->pools[i]->allocs;                            \
      if (allocs > 0) {                                                       \
          *num_errors += 1;                                                   \
          errors = realloc(errors, *num_errors * sizeof(error_info *));       \
          errors[*num_errors -1] = malloc(sizeof(error_info));                \
          error_info *this_error = errors[*num_errors -1];                    \
          errors[*num_errors-1]->msg = malloc(sizeof(char) * 80);             \
          sprintf(                                                            \
              (char *) this_error->msg,                                       \
              "Memory manager leak %d allocations in pool size %d.",          \
              allocs, pool_size);                                             \
      }                                                                       \
      pool_size = pool_size * 2;                                              \
                                                                              \
  }                                                                           \
  NL_free_v_memmgr(&mgr);                                                     \



error_info **ptb_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test1";
    
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 5;
    unsigned char *buf = (unsigned char *)"This is a sentence.";
    unsigned char *gold[] = {
        (unsigned char *)"This", 
        (unsigned char *)"is", 
        (unsigned char *)"a", 
        (unsigned char *)"sentence", 
        (unsigned char *)".",
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 12;
    unsigned char *buf = (unsigned char *)
        "U.S. insurance: Conseco acquires Kemper Corp. \n"
        "</HEADLINE>\n<P>\nU.S insurance";
    unsigned char *gold[] = {
        (unsigned char*)"U.S.",
        (unsigned char*)"insurance",
        (unsigned char*)":",
        (unsigned char*)"Conseco",
        (unsigned char*)"acquires",
        (unsigned char*)"Kemper",
        (unsigned char*)"Corp.",
        (unsigned char*)".",
        (unsigned char*)"</HEADLINE>",
        (unsigned char*)"<P>",
        (unsigned char*)"U.S",
        (unsigned char*)"insurance"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test3(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test3";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 22;
    unsigned char *buf = (unsigned char *)
        "Based in Eugene,Ore., PakTech needs a new distributor after "
        "Sydney-based Creative Pack Pty. Ltd. went into voluntary "
        "administration.";
    unsigned char *gold[] = {
        (unsigned char*)"Based",
        (unsigned char*)"in",
        (unsigned char*)"Eugene",
        (unsigned char*)",",
        (unsigned char*)"Ore.",
        (unsigned char*)",",
        (unsigned char*)"PakTech",
        (unsigned char*)"needs",
        (unsigned char*)"a",
        (unsigned char*)"new",
        (unsigned char*)"distributor",
        (unsigned char*)"after",
        (unsigned char*)"Sydney-based",
        (unsigned char*)"Creative",
        (unsigned char*)"Pack",
        (unsigned char*)"Pty.",
        (unsigned char*)"Ltd.",
        (unsigned char*)"went",
        (unsigned char*)"into",
        (unsigned char*)"voluntary",
        (unsigned char*)"administration",
        (unsigned char*)"." 
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test4(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test4";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 12;
    unsigned char *buf = (unsigned char *)
        "The Iron Age (ca. 1300 – ca. 300 BC).";
    unsigned char *gold[] = {
        (unsigned char*)"The",
        (unsigned char*)"Iron",
        (unsigned char*)"Age",
        (unsigned char*)"-LRB-",
        (unsigned char*)"ca.",
        (unsigned char*)"1300",
        (unsigned char*)"--",
        (unsigned char*)"ca.",
        (unsigned char*)"300",
        (unsigned char*)"BC",
        (unsigned char*)"-RRB-",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test5(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test5";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 3;
    unsigned char *buf = (unsigned char *)
        "Indo\xC2\xADnesian ship\xC2\xADping \xC2\xAD";
    unsigned char *gold[] = {
        (unsigned char*)"Indonesian",
        (unsigned char*)"shipping",
        (unsigned char*)"-"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test6(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test6";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 11;
    unsigned char *buf = (unsigned char *)
        "Gimme a phone, I'm gonna call.";
    unsigned char *gold[] = {
        (unsigned char*)"Gim",
        (unsigned char*)"me",
        (unsigned char*)"a",
        (unsigned char*)"phone",
        (unsigned char*)",",
        (unsigned char*)"I",
        (unsigned char*)"'m",
        (unsigned char*)"gon",
        (unsigned char*)"na",
        (unsigned char*)"call",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test7(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test7";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 31;
    unsigned char *buf = (unsigned char *)
        "\"John & Mary's dog,\" Jane thought (to herself).\n\""
        "What a #$%!\na- ``I like AT&T''.\"";
    unsigned char *gold[] = {
        (unsigned char*)"``",
        (unsigned char*)"John",
        (unsigned char*)"&",
        (unsigned char*)"Mary",
        (unsigned char*)"'s",
        (unsigned char*)"dog",
        (unsigned char*)",",
        (unsigned char*)"''",
        (unsigned char*)"Jane",
        (unsigned char*)"thought",
        (unsigned char*)"-LRB-",
        (unsigned char*)"to",
        (unsigned char*)"herself",
        (unsigned char*)"-RRB-",
        (unsigned char*)".",
        (unsigned char*)"``",
        (unsigned char*)"What",
        (unsigned char*)"a",
        (unsigned char*)"#",
        (unsigned char*)"$",
        (unsigned char*)"%",
        (unsigned char*)"!",
        (unsigned char*)"a",
        (unsigned char*)"-",
        (unsigned char*)"``",
        (unsigned char*)"I",
        (unsigned char*)"like",
        (unsigned char*)"AT&T",
        (unsigned char*)"''",
        (unsigned char*)".",
        (unsigned char*)"''"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test8(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test8";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 6;
    unsigned char *buf = (unsigned char *)
        "I said at 4:45pm.";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"said",
        (unsigned char*)"at",
        (unsigned char*)"4:45",
        (unsigned char*)"pm",
        (unsigned char*)".",
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test9(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test9";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 29;
    unsigned char *buf = (unsigned char *)
        "I can't believe they wanna keep 40% of that.\"\n"
        "``Whatcha think?''\n\"I don't --- think so...,\"";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"ca",
        (unsigned char*)"n't",
        (unsigned char*)"believe",
        (unsigned char*)"they",
        (unsigned char*)"wan",
        (unsigned char*)"na",
        (unsigned char*)"keep",
        (unsigned char*)"40",
        (unsigned char*)"%",
        (unsigned char*)"of",
        (unsigned char*)"that",
        (unsigned char*)".",
        (unsigned char*)"''",
        (unsigned char*)"``",
        (unsigned char*)"Whatcha",
        (unsigned char*)"think",
        (unsigned char*)"?",
        (unsigned char*)"''",
        (unsigned char*)"``",
        (unsigned char*)"I",
        (unsigned char*)"do",
        (unsigned char*)"n't",
        (unsigned char*)"--",
        (unsigned char*)"think",
        (unsigned char*)"so",
        (unsigned char*)"...",
        (unsigned char*)",",
        (unsigned char*)"''"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test10(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test10";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 15;
    unsigned char *buf = (unsigned char *)
        "You `paid' US$170,000?!\nYou should've paid only$16.75.";
    unsigned char *gold[] = {
        (unsigned char*)"You",
        (unsigned char*)"`",
        (unsigned char*)"paid",
        (unsigned char*)"'",
        (unsigned char*)"US$",
        (unsigned char*)"170,000",
        (unsigned char*)"?!",
        (unsigned char*)"You",
        (unsigned char*)"should",
        (unsigned char*)"'ve",
        (unsigned char*)"paid",
        (unsigned char*)"only",
        (unsigned char*)"$",
        (unsigned char*)"16.75",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test11(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test11";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 19;
    unsigned char *buf = (unsigned char *)
        "1. Buy a new Chevrolet (37%-owned in the U.S..) . 15%";
    unsigned char *gold[] = {
        (unsigned char*)"1",
        (unsigned char*)".",
        (unsigned char*)"Buy",
        (unsigned char*)"a",
        (unsigned char*)"new",
        (unsigned char*)"Chevrolet",
        (unsigned char*)"-LRB-",
        (unsigned char*)"37",
        (unsigned char*)"%",
        (unsigned char*)"-",
        (unsigned char*)"owned",
        (unsigned char*)"in",
        (unsigned char*)"the",
        (unsigned char*)"U.S.",
        (unsigned char*)".",
        (unsigned char*)"-RRB-",
        (unsigned char*)".",
        (unsigned char*)"15",
        (unsigned char*)"%"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test12(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test12";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 18;
    unsigned char *buf = (unsigned char *)
        "I like you ;-) but do you care :(. I'm happy ^_^ but shy (x.x)!";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"like",
        (unsigned char*)"you",
        (unsigned char*)";--RRB-",
        (unsigned char*)"but",
        (unsigned char*)"do",
        (unsigned char*)"you",
        (unsigned char*)"care",
        (unsigned char*)":-LRB-",
        (unsigned char*)".",
        (unsigned char*)"I",
        (unsigned char*)"'m",
        (unsigned char*)"happy",
        (unsigned char*)"^_^",
        (unsigned char*)"but",
        (unsigned char*)"shy",
        (unsigned char*)"-LRB-x.x-RRB-",
        (unsigned char*)"!" 
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test13(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test13";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 25;
    unsigned char *buf = (unsigned char *)
        "Diamond (``Not even the chair'') lives near Udaipur (84km). "
        "{1. A potential Palmer trade:}";
    unsigned char *gold[] = {
        (unsigned char*)"Diamond",
        (unsigned char*)"-LRB-",
        (unsigned char*)"``",
        (unsigned char*)"Not",
        (unsigned char*)"even", 
        (unsigned char*)"the",
        (unsigned char*)"chair",
        (unsigned char*)"''",
        (unsigned char*)"-RRB-",
        (unsigned char*)"lives",
        (unsigned char*)"near",
        (unsigned char*)"Udaipur",
        (unsigned char*)"-LRB-",
        (unsigned char*)"84km",
        (unsigned char*)"-RRB-",
        (unsigned char*)".",
        (unsigned char*)"-LCB-",
        (unsigned char*)"1",
        (unsigned char*)".",
        (unsigned char*)"A",
        (unsigned char*)"potential",
        (unsigned char*)"Palmer",
        (unsigned char*)"trade",
        (unsigned char*)":",
        (unsigned char*)"-RCB-"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test14(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test14";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 10;
    unsigned char *buf = (unsigned char *)
        "No. I like No. 24 and no.47.";
    unsigned char *gold[] = {
        (unsigned char*)"No",
        (unsigned char*)".",
        (unsigned char*)"I",
        (unsigned char*)"like",
        (unsigned char*)"No.",
        (unsigned char*)"24",
        (unsigned char*)"and",
        (unsigned char*)"no.",
        (unsigned char*)"47",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test15(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test15";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 21;
    unsigned char *buf = (unsigned char *)
        "You can get a B.S. or a B. A. or a Ph.D (sometimes a Ph. D) "
        "from Stanford.";
    unsigned char *gold[] = {
        (unsigned char*)"You",
        (unsigned char*)"can",
        (unsigned char*)"get",
        (unsigned char*)"a",
        (unsigned char*)"B.S.",
        (unsigned char*)"or",
        (unsigned char*)"a",
        (unsigned char*)"B.",
        (unsigned char*)"A.",
        (unsigned char*)"or",
        (unsigned char*)"a",
        (unsigned char*)"Ph.D",
        (unsigned char*)"-LRB-",
        (unsigned char*)"sometimes",
        (unsigned char*)"a",
        (unsigned char*)"Ph.",
        (unsigned char*)"D",
        (unsigned char*)"-RRB-",
        (unsigned char*)"from",
        (unsigned char*)"Stanford",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test16(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test16";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 6;
    unsigned char *buf = (unsigned char *)
        "@Harry_Styles didn`t like Mu`ammar al-Qaddafi";
    unsigned char *gold[] = {
        (unsigned char*)"@Harry_Styles",
        (unsigned char*)"did",
        (unsigned char*)"n`t",
        (unsigned char*)"like",
        (unsigned char*)"Mu`ammar",
        (unsigned char*)"al-Qaddafi"
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test17(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test17";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 16;
    unsigned char *buf = (unsigned char *)
        "Kenneth liked Windows 3.1, Windows 3.x,"
        " and Mesa A.B as I remember things.";
    unsigned char *gold[] = {
        (unsigned char*)"Kenneth",
        (unsigned char*)"liked",
        (unsigned char*)"Windows",
        (unsigned char*)"3.1",
        (unsigned char*)",",
        (unsigned char*)"Windows",
        (unsigned char*)"3.x",
        (unsigned char*)",",
        (unsigned char*)"and",
        (unsigned char*)"Mesa",
        (unsigned char*)"A.B",
        (unsigned char*)"as",
        (unsigned char*)"I",
        (unsigned char*)"remember",
        (unsigned char*)"things",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test18(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test18";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 9;
    unsigned char *buf = (unsigned char *)
        "I like programming in F# more than C#.";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"like",
        (unsigned char*)"programming",
        (unsigned char*)"in",
        (unsigned char*)"F#",
        (unsigned char*)"more",
        (unsigned char*)"than",
        (unsigned char*)"C#",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test19(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test19";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 24;
    unsigned char *buf = (unsigned char *)
        "NBC Live will be available free through the Yahoo! Chat Web site. "
        "E! Entertainment said ``Jeopardy!'' is a game show.";
    unsigned char *gold[] = {
        (unsigned char*)"NBC",
        (unsigned char*)"Live",
        (unsigned char*)"will",
        (unsigned char*)"be",
        (unsigned char*)"available",
        (unsigned char*)"free",
        (unsigned char*)"through",
        (unsigned char*)"the",
        (unsigned char*)"Yahoo!",
        (unsigned char*)"Chat",
        (unsigned char*)"Web",
        (unsigned char*)"site",
        (unsigned char*)".",
        (unsigned char*)"E!",
        (unsigned char*)"Entertainment",
        (unsigned char*)"said",
        (unsigned char*)"``",
        (unsigned char*)"Jeopardy!",
        (unsigned char*)"''",
        (unsigned char*)"is",
        (unsigned char*)"a",
        (unsigned char*)"game",
        (unsigned char*)"show",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test20(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test20";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 9;
    unsigned char *buf = (unsigned char *)
        "I lived in O\xE2\x80\x99Malley and read OK! Magazine.";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"lived",
        (unsigned char*)"in",
        (unsigned char*)"O'Malley",
        (unsigned char*)"and",
        (unsigned char*)"read",
        (unsigned char*)"OK!",
        (unsigned char*)"Magazine",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test21(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test21";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 9;
    unsigned char *buf = (unsigned char *)
        "I lived in O\xC2\x92Malley and read OK! Magazine."; /* invalid unicode codepoint, but inherit from cp1252 */
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"lived",
        (unsigned char*)"in",
        (unsigned char*)"O'Malley",
        (unsigned char*)"and",
        (unsigned char*)"read",
        (unsigned char*)"OK!",
        (unsigned char*)"Magazine",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test22(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test22";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 16;
    unsigned char *buf = (unsigned char *)
        "I like: \xE2\x80\xA2wine, \xC2\x95" "cheese, \xE2\x80\xA3salami, "
        "& \xE2\x81\x83speck.";
    unsigned char *gold[] = {

        (unsigned char*)"I",
        (unsigned char*)"like",
        (unsigned char*)":",
        (unsigned char*)"\xE2\x80\xA2",
        (unsigned char*)"wine",
        (unsigned char*)",",
        (unsigned char*)"\xE2\x80\xA2",
        (unsigned char*)"cheese",
        (unsigned char*)",",
        (unsigned char*)"\xE2\x80\xA3",
        (unsigned char*)"salami",
        (unsigned char*)",",
        (unsigned char*)"&",
        (unsigned char*)"\xE2\x81\x83",
        (unsigned char*)"speck",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test23(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test23";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 15;
    unsigned char *buf = (unsigned char *)
        "I don't give a f**k about your sh*tty life.";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"do",
        (unsigned char*)"n't",
        (unsigned char*)"give",
        (unsigned char*)"a",
        (unsigned char*)"f",
        (unsigned char*)"**",
        (unsigned char*)"k",
        (unsigned char*)"about",
        (unsigned char*)"your",
        (unsigned char*)"sh",
        (unsigned char*)"*",
        (unsigned char*)"tty",
        (unsigned char*)"life",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test24(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test24";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 6;
    unsigned char *buf = (unsigned char *)
        "First sentence.... Second sentence.";
    unsigned char *gold[] = {
        (unsigned char*)"First",
        (unsigned char*)"sentence",
        (unsigned char*)"...",
        (unsigned char*)"Second",
        (unsigned char*)"sentence",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test25(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test25";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 6;
    unsigned char *buf = (unsigned char *)
        "First sentence . . . . Second sentence.";
    unsigned char *gold[] = {
        (unsigned char*)"First",
        (unsigned char*)"sentence",
        (unsigned char*)"...",
        (unsigned char*)"Second",
        (unsigned char*)"sentence",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **ptb_test26(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "ptb-test26";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 28;
    unsigned char *buf = (unsigned char *)
         "I wasn’t really ... well, what I mean...see . . . "
         "what I'm saying, the thing is . . . I didn’t mean it.";
    unsigned char *gold[] = {
        (unsigned char*)"I",
        (unsigned char*)"was",
        (unsigned char*)"n't",
        (unsigned char*)"really",
        (unsigned char*)"...",
        (unsigned char*)"well",
        (unsigned char*)",",
        (unsigned char*)"what",
        (unsigned char*)"I",
        (unsigned char*)"mean",
        (unsigned char*)"...",
        (unsigned char*)"see",
        (unsigned char*)"...",
        (unsigned char*)"what",
        (unsigned char*)"I",
        (unsigned char*)"'m",
        (unsigned char*)"saying",
        (unsigned char*)",",
        (unsigned char*)"the",
        (unsigned char*)"thing",
        (unsigned char*)"is",
        (unsigned char*)"...",
        (unsigned char*)"I",
        (unsigned char*)"did",
        (unsigned char*)"n't",
        (unsigned char*)"mean",
        (unsigned char*)"it",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **corp_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "corp-test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);
    cfg->strict_ptb3 = 1;

    size_t gold_num_tokens = 18;
    unsigned char *buf = (unsigned char *)
        "So, too, many analysts predict, will Exxon Corp., "
        "Chevron Corp. and Amoco Corp.";
    unsigned char *gold[] = {
        (unsigned char*)"So",
        (unsigned char*)",",
        (unsigned char*)"too",
        (unsigned char*)",",
        (unsigned char*)"many",
        (unsigned char*)"analysts",
        (unsigned char*)"predict",
        (unsigned char*)",",
        (unsigned char*)"will",
        (unsigned char*)"Exxon",
        (unsigned char*)"Corp.",
        (unsigned char*)",",
        (unsigned char*)"Chevron",
        (unsigned char*)"Corp.",
        (unsigned char*)"and",
        (unsigned char*)"Amoco",
        (unsigned char*)"Corp",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}


error_info **corp_test2(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "corp-test2";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 18;
    unsigned char *buf = (unsigned char *)
        "So, too, many analysts predict, will Exxon Corp., "
        "Chevron Corp. and Amoco Corp.";
    unsigned char *gold[] = {
        (unsigned char*)"So",
        (unsigned char*)",",
        (unsigned char*)"too",
        (unsigned char*)",",
        (unsigned char*)"many",
        (unsigned char*)"analysts",
        (unsigned char*)"predict",
        (unsigned char*)",",
        (unsigned char*)"will",
        (unsigned char*)"Exxon",
        (unsigned char*)"Corp.",
        (unsigned char*)",",
        (unsigned char*)"Chevron",
        (unsigned char*)"Corp.",
        (unsigned char*)"and",
        (unsigned char*)"Amoco",
        (unsigned char*)"Corp.",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **jacob_eisenstein_apos_test(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "jacob-eisenstein-apos-test";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 2;
    unsigned char *buf = (unsigned char *)
        "it's";
    unsigned char *gold[] = {
        (unsigned char*)"it",
        (unsigned char*)"'s",
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}

error_info **sgml_test1(char **name, size_t *num_errors) {
    error_info **errors = NULL;
    *num_errors = 0;
    *name = "sgml-test1";

    NL_v_memmgr *mgr = NL_new_v_memmgr(256);    
    NL_PTBTokConfig *cfg = NL_new_PTB_tokenizer_config(mgr);

    size_t gold_num_tokens = 40;
    unsigned char *buf = (unsigned char *)
        "Significant improvements in peak FEV1 were demonstrated with "
        "tiotropium/olodaterol 5/2 μg (p = 0.008), 5/5 μg (p = 0.012), "
        "and 5/10 μg (p < 0.0001) versus tiotropium monotherapy [51].";
    unsigned char *gold[] = {
        (unsigned char*)"Significant",
        (unsigned char*)"improvements",
        (unsigned char*)"in",
        (unsigned char*)"peak",
        (unsigned char*)"FEV1",
        (unsigned char*)"were",
        (unsigned char*)"demonstrated",
        (unsigned char*)"with",
        (unsigned char*)"tiotropium/olodaterol",
        (unsigned char*)"5/2",
        (unsigned char*)"μg",
        (unsigned char*)"-LRB-",
        (unsigned char*)"p",
        (unsigned char*)"=",
        (unsigned char*)"0.008",
        (unsigned char*)"-RRB-",
        (unsigned char*)",",
        (unsigned char*)"5/5",
        (unsigned char*)"μg",
        (unsigned char*)"-LRB-",
        (unsigned char*)"p",
        (unsigned char*)"=",
        (unsigned char*)"0.012",
        (unsigned char*)"-RRB-",
        (unsigned char*)",",
        (unsigned char*)"and",
        (unsigned char*)"5/10",
        (unsigned char*)"μg",
        (unsigned char*)"-LRB-",
        (unsigned char*)"p",
        (unsigned char*)"<",
        (unsigned char*)"0.0001",
        (unsigned char*)"-RRB-",
        (unsigned char*)"versus",
        (unsigned char*)"tiotropium",
        (unsigned char*)"monotherapy",
        (unsigned char*)"-LSB-",
        (unsigned char*)"51",
        (unsigned char*)"-RSB-",
        (unsigned char*)"."
    }; 

    size_t buf_len = strlen((char *)buf); 

    TOKEN_TEST

    return errors;
}



//int main(int argc, char *argv[]) {
//
//    char *usage = "ptb_inputs_test [-v] [-h]\n"
//        "\t-v\tverbose, print error messages\n"
//        "\t-h\tdisplay this message\n";
//
//    int verbose = 0;
//
//    for (int i=0; i < argc; i++) {
//        if (strcmp(argv[i], "-v") == 0) {
//            verbose = 1;
//        } else if (strcmp(argv[i], "-h") == 0) {
//            printf("%s", usage);
//            exit(0);
//        }
//
//    }
//
//    for (int i=0; i < num_tests; i++) {
//        char **name = malloc(sizeof(char *));
//        error_info **errors = NULL;
//        size_t num_errors = 0;
//        errors = (*tests[i]) (name, &num_errors);
//        char *status;
//        if (num_errors == 0) {
//            status = "OK";
//        } else {
//            status = "FAIL";
//        }
//        printf("%s ... %s\n", *name, status);
//        for (int e=0; e<num_errors; e++) {
//            if (verbose == 1) {
//                printf("Error %d: %s\n", e, errors[e]->msg);
//            }
//            free(errors[e]->msg);
//            free(errors[e]);
//        }
//        free(errors);
//        free(name);
//    }
//}
