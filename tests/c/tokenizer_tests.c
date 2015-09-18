#include "nlp/tokenizer.h"
#include "nlp/tokenizer_utils.h"
#include "nlp/mem_manager.h"
#include <string.h>

int test_token1() {
    int errors = 0;
    unsigned char *buf = (unsigned char *) "This is a test of tokens .";
    unsigned char *gold[] = {
        (unsigned char *)"This", 
        (unsigned char *)"is", 
        (unsigned char *)"a", 
        (unsigned char *)"test", 
        (unsigned char *)"of", 
        (unsigned char *)"tokens", 
        (unsigned char *)"."};
    size_t num_tokens;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);
    //while (1) {
    NL_span **spans = NL_tokenize_buf(
            buf, strlen((char *)buf), &num_tokens, NULL, mgr);
    if (num_tokens != 7) {
        errors = 1;
    }

    for (int i=0; i < num_tokens; i++) {
        int diffs = memcmp(
            (void *)(spans[i]->start), 
            (void *)gold[i], 
            spans[i]->length
        ); 
        if (diffs != 0) {
            errors += 1;
            break;
        }         
    }

    for (int i=0; i < num_tokens; i++) {
        NL_deallocate_v_mem(mgr, spans[i]);
    }
    NL_deallocate_v_mem(mgr, spans);

    //}
    NL_free_v_memmgr(&mgr); 
       

    return errors;
}

int ptbtest() {

    unsigned char *test_sentences[] = {
        (unsigned char *) "This is a sentence.",
        (unsigned char *) "U.S. insurance: Conseco acquires Kemper Corp. \n</HEADLINE>\n<P>\nU.S insurance",
        (unsigned char *) 
            "Based in Eugene,Ore., PakTech needs a new distributor after Sydney-based Creative Pack Pty. Ltd. went into voluntary administration.",
        (unsigned char *) "The Iron Age (ca. 1300 – ca. 300 BC).",
        (unsigned char *) "Indo\xC2\xADnesian ship\xC2\xADping \xC2\xAD",
        (unsigned char *) "Gimme a phone, I'm gonna call.",
        (unsigned char *) "\"John & Mary's dog,\" Jane thought (to herself).\n\"What a #$%!\na- ``I like AT&T''.\"",
        (unsigned char *) "I said at 4:45pm.",
        (unsigned char *) "I can't believe they wanna keep 40% of that.\"\n``Whatcha think?''\n\"I don't --- think so...,\"",
        (unsigned char *) "You `paid' US$170,000?!\nYou should've paid only$16.75.",
        (unsigned char *) "1. Buy a new Chevrolet (37%-owned in the U.S..) . 15%",
        (unsigned char *) "I like you ;-) but do you care :(. I'm happy ^_^ but shy (x.x)!",
        (unsigned char *) "Diamond (``Not even the chair'') lives near Udaipur (84km). {1. A potential Palmer trade:}",
        (unsigned char *) "No. I like No. 24 and no.47.",
        (unsigned char *) "You can get a B.S. or a B. A. or a Ph.D (sometimes a Ph. D) from Stanford.",
        (unsigned char *) "@Harry_Styles didn`t like Mu`ammar al-Qaddafi",
        (unsigned char *) "Kenneth liked Windows 3.1, Windows 3.x, and Mesa A.B as I remember things.",
        (unsigned char *) "I like programming in F# more than C#.",
        (unsigned char *) "NBC Live will be available free through the Yahoo! Chat Web site. E! Entertainment said ``Jeopardy!'' is a game show.",
//        (unsigned char *) "I lived in O\u2019Malley and read OK! Magazine.",
//        (unsigned char *) "I lived in O\u0092Malley and read OK! Magazine.", /* invalid unicode codepoint, but inherit from cp1252 */
//        (unsigned char *) "I like: \u2022wine, \u0095cheese, \u2023salami, & \u2043speck.",
        (unsigned char *) "I don't give a f**k about your sh*tty life.",
        (unsigned char *) "First sentence.... Second sentence.",
        (unsigned char *) "First sentence . . . . Second sentence.",
        (unsigned char *) "I wasn’t really ... well, what I mean...see . . . what I'm saying, the thing is . . . I didn’t mean it."
    };


    char *ptbGold[3][100] = {
    { "This", "is", "a", "sentence", "." },
    { "U.S.", "insurance", ":", "Conseco", "acquires", "Kemper", "Corp.", ".",
      "</HEADLINE>", "<P>", "U.S", "insurance" },
    { "Based", "in", "Eugene", ",", "Ore.", ",", "PakTech", "needs", "a", "new",
      "distributor", "after", "Sydney-based", "Creative", "Pack", "Pty.", "Ltd.",
      "went", "into", "voluntary", "administration", "." }
//    { "The", "Iron", "Age", "-LRB-", "ca.", "1300", "--", "ca.", "300", "BC", "-RRB-", "." },
//    { "Indonesian", "shipping", "-" },
//    { "Gim", "me", "a", "phone", ",", "I", "'m", "gon", "na", "call", "."},
//    { "``", "John", "&", "Mary", "'s", "dog", ",", "''", "Jane", "thought", "-LRB-", "to", "herself", "-RRB-",
//      ".", "``", "What", "a", "#", "$", "%", "!", "a", "-", "``", "I", "like", "AT&T", "''", ".", "''" },
//    { "I", "said", "at", "4:45", "pm", "."},
//    { "I", "ca", "n't", "believe", "they", "wan", "na", "keep", "40", "%", "of", "that", ".", "''",
//      "``", "Whatcha", "think", "?", "''", "``", "I", "do", "n't", "--", "think", "so", "...", ",", "''" },
          // We don't yet split "Whatcha" but probably should following model of "Whaddya" --> What d ya. Maybe What cha
//    { "You", "`", "paid", "'", "US$", "170,000", "?!", "You", "should", "'ve", "paid", "only", "$", "16.75", "." },
//    { "1", ".", "Buy", "a", "new", "Chevrolet",
//      "-LRB-", "37", "%", "-", "owned", "in", "the", "U.S.", ".", "-RRB-", ".", "15", "%" },
          // Unclear if 37%-owned is right or wrong under old PTB....  Maybe should be 37 %-owned even though sort of crazy
//    { "I", "like", "you", ";--RRB-", "but", "do", "you", "care",  ":-LRB-", ".",
//      "I", "'m", "happy", "^_^", "but", "shy", "-LRB-x.x-RRB-", "!" },
//    { "Diamond", "-LRB-", "``", "Not", "even",  "the", "chair", "''", "-RRB-", "lives", "near", "Udaipur", "-LRB-", "84km", "-RRB-", ".",
//      "-LCB-", "1", ".", "A", "potential", "Palmer", "trade", ":", "-RCB-"},
//    { "No", ".", "I", "like", "No.", "24", "and", "no.", "47", "." },
//    { "You", "can", "get", "a", "B.S.", "or", "a", "B.", "A.", "or", "a", "Ph.D", "-LRB-", "sometimes", "a", "Ph.", "D", "-RRB-", "from", "Stanford", "." },
//    { "@Harry_Styles", "did", "n`t", "like", "Mu`ammar", "al-Qaddafi" },
//    { "Kenneth", "liked", "Windows", "3.1", ",", "Windows", "3.x", ",", "and", "Mesa", "A.B", "as", "I", "remember", "things", ".", },
//    { "I", "like", "programming", "in", "F#", "more", "than", "C#", "." },
//    { "NBC", "Live", "will", "be", "available", "free", "through", "the", "Yahoo!", "Chat", "Web", "site", ".",
//            "E!", "Entertainment", "said", "``", "Jeopardy!", "''", "is", "a", "game", "show", "." },
//          { "I", "lived", "in", "O'Malley", "and", "read", "OK!", "Magazine", "." },
//          { "I", "lived", "in", "O'Malley", "and", "read", "OK!", "Magazine", "." },
//          { "I", "like", ":", "\u2022", "wine", ",", "\u2022", "cheese", ",", "\u2023", "salami",
//                  ",", "&", "\u2043", "speck", "." },
//    { "I", "do", "n't", "give", "a", "f**k", "about", "your", "sh*tty", "life", "." },
//    { "First", "sentence", "...", ".", "Second", "sentence", "." },
//    { "First", "sentence", "...", ".", "Second", "sentence", "." },
//    { "I", "was", "n't", "really", "...", "well", ",", "what", "I", "mean", "...", "see", "...", "what", "I", "'m", "saying",
//      ",", "the", "thing", "is", "...", "I", "did", "n't", "mean", "it", "." },

  };

    size_t num_tokens;
    NL_v_memmgr *mgr = NL_new_v_memmgr(256);

    int err = 0;
    for (int i=0; i < 2; i++) {
        unsigned char *sent = test_sentences[i];
        printf("%s\n", sent);
        NL_span **spans = NL_tokenize_buf(
            sent, strlen((char *)sent), &num_tokens, NULL, mgr);
       
        for (int j=0; j < num_tokens; j++) {
            printf("token: ");
            fwrite(spans[j]->start, 1, spans[j]->length, stdout);

            int diffs = memcmp(
                (void *)(spans[j]->start), 
                (void *)ptbGold[i][j], 
                spans[j]->length
            );
            if (diffs != 0) {
                err = 1;
            }

            printf(" ==> %s\n", ptbGold[i][j]);
            NL_deallocate_v_mem(mgr, spans[j]);
        }
        NL_deallocate_v_mem(mgr, spans);

    //}
 
    }

    NL_free_v_memmgr(&mgr); 


    return err;
}





int unicode_quotes_count() {

    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    size_t buf_size = strlen((char *)buf);
    unsigned char *gold = (unsigned char *)
        "\xE2\x80\x98 \xE2\x80\x9C \xE2\x80\x9C \xE2\x80\x98"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";

    size_t trans_size = strlen((char *) gold);

    if (trans_size != NL_get_size_unicode_quotes(buf, buf_size))
        errors = 1;

    return errors;

}





int left_unicode_quotes_transform() {

    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    size_t buf_size = strlen((char *)buf);
    
    size_t trans_size = NL_get_size_unicode_quotes(buf, buf_size);
    unsigned char *trans = malloc(sizeof(unsigned char) * trans_size);

    unsigned char *gold = (unsigned char *)
        "\xE2\x80\x98 \xE2\x80\x9C \xE2\x80\x9C \xE2\x80\x98"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";

    NL_unicode_quotes_probably_left(buf, buf_size, trans);

    printf("GOLD       : %s\n", gold);
    printf("TRANSFORMED: %s\n", trans);
    if (strcmp((char *) trans, (char *)gold) != 0)
        errors = 1;


    free(trans);

    return errors;

}

int right_unicode_quotes_transform() {

    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' \" &quot; &apos; \xC2\x91 \xC2\x92 \xC2\x93 \xC2\x94";
    size_t buf_size = strlen((char *)buf);
    
    size_t trans_size = NL_get_size_unicode_quotes(buf, buf_size);
    unsigned char *trans = malloc(sizeof(unsigned char) * trans_size);

    unsigned char *gold = (unsigned char *)
        "\xE2\x80\x99 \xE2\x80\x9D \xE2\x80\x9D \xE2\x80\x99"
        " \xE2\x80\x98 \xE2\x80\x99 \xE2\x80\x9C \xE2\x80\x9D";

    NL_unicode_quotes_probably_right(buf, buf_size, trans);

    printf("GOLD       : %s\n", gold);
    printf("TRANSFORMED: %s\n", trans);
    if (strcmp((char *) trans, (char *)gold) != 0)
        errors = 1;


    free(trans);

    return errors;

}

int ascii_quotes_count() {
    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D \xC2\x80\x9E "
        "\xC2\xAB \xC2\xBB";

    unsigned char *gold = (unsigned char *)
        "' ' ' ' ' ' ' ' ' ' \" \" \" \" \" \" \" \" \"";

    size_t before_size = strlen((char *) buf);
    size_t after_size = strlen((char *) gold);
    size_t pred_size = NL_get_size_ascii_quotes(buf, strlen((char *) buf));   

    printf("UNICODE: %s\n", buf);
    printf("ASCII: %s\n", gold);
    printf("BEFORE SIZE: %lu\n", before_size);
    printf("AFTER SIZE: %lu\n", after_size);
    printf("PRED SIZE: %lu\n", pred_size);

    if (after_size != pred_size) {
        errors = 1;

    }
    
    return errors;

}

int ascii_quotes_transform() {
    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D \xC2\x80\x9E "
        "\xC2\xAB \xC2\xBB";

    unsigned char *gold = (unsigned char *)
        "' ' ' ' ' ' ' ' ' ' \" \" \" \" \" \" \" \" \"";
    size_t buf_size = strlen((char *) buf);
    size_t trans_size = NL_get_size_ascii_quotes(buf, buf_size);   
    unsigned char *trans = malloc(sizeof(unsigned char) * trans_size);
    
    NL_ascii_quotes(buf, buf_size, trans);
    printf("BEFORE: %s\n", buf);
    printf("AFTER : %s\n", gold);    
    printf("TRANS : %s\n", trans);    

    if (strcmp((char *) gold, (char *) trans) != 0) {
        errors = 1;
    }
    free(trans); 
    return errors;

}

int latex_quotes_count() {
    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";

    unsigned char *gold = (unsigned char *)
        "` ` ` ` ' ' ' ` ` ' `` `` `` `` '' '' `` ''";

    size_t before_size = strlen((char *) buf);
    size_t after_size = strlen((char *) gold);
    size_t pred_size = NL_get_size_latex_quotes(buf, strlen((char *) buf));   

    printf("UNICODE: %s\n", buf);
    printf("LATEX: %s\n", gold);
    printf("BEFORE SIZE: %lu\n", before_size);
    printf("AFTER SIZE: %lu\n", after_size);
    printf("PRED SIZE: %lu\n", pred_size);

    if (after_size != pred_size) {
        errors = 1;

    }
    
    return errors;

}

int latex_quotes_prob_left_transform() {
    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";

    unsigned char *gold = (unsigned char *)
        "` ` ` ` ' ' ' ` ` ' `` `` `` `` '' '' `` ''";
    size_t buf_size = strlen((char *) buf);
    size_t trans_size = NL_get_size_latex_quotes(buf, buf_size);   
    unsigned char *trans = malloc(sizeof(unsigned char) * trans_size);
    
    NL_latex_quotes_probably_left(buf, buf_size, trans);
    printf("BEFORE: %s\n", buf);
    printf("AFTER : %s\n", gold);    
    printf("TRANS : %s\n", trans);    

    if (strcmp((char *) gold, (char *) trans) != 0) {
        errors = 1;
    }
    free(trans); 
    return errors;

}

int latex_quotes_prob_right_transform() {
    int errors = 0;
    unsigned char *buf = (unsigned char *)
        "' &apos; \xC2\x91 \xE2\x80\x98 \xC2\x92 \xE2\x80\x99 \xE2\x80\x9A "
        "\xE2\x80\x9B \xE2\x80\xB9 \xE2\x80\xBA "
        "\" &quot; \xC2\x93 \xE2\x80\x9C \xC2\x94 \xC2\x80\x9D "
        "\xC2\xAB \xC2\xBB";

    unsigned char *gold = (unsigned char *)
        "' ' ` ` ' ' ' ` ` ' '' '' `` `` '' '' `` ''";
    size_t buf_size = strlen((char *) buf);
    size_t trans_size = NL_get_size_latex_quotes(buf, buf_size);   
    unsigned char *trans = malloc(sizeof(unsigned char) * trans_size);
    
    NL_latex_quotes_probably_right(buf, buf_size, trans);
    printf("BEFORE: %s\n", buf);
    printf("AFTER : %s\n", gold);    
    printf("TRANS : %s\n", trans);    

    if (strcmp((char *) gold, (char *) trans) != 0) {
        errors = 1;
    }
    free(trans); 
    return errors;

}

int copy_no_softhyphen() {
    int errors = 0;
    
    unsigned char *buf1 = (unsigned char *) 
        "hy\xC2\xADphe\xC2\xADna\xC2\xADted";
    size_t buf1_size = strlen((char *) buf1);
    unsigned char *gold1 = (unsigned char *) "hyphenated";
    unsigned char *trans1 = malloc(
        sizeof(unsigned char) * strlen((char *) gold1));
    NL_copy_no_softhyphen(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }


    unsigned char *buf2 = (unsigned char *) 
        "hy\xC2\xADphen \xC2\xAE";
    size_t buf2_size = strlen((char *) buf2);
    unsigned char *gold2 = (unsigned char *) "hyphen \xC2\xAE";
    unsigned char *trans2 = malloc(
        sizeof(unsigned char) * strlen((char *) gold2));
    NL_copy_no_softhyphen(buf2, buf2_size, trans2);

    printf("TRANS2 : %s\n", trans2);
    printf("GOLD2  : %s\n", gold2);
    if (strcmp((char *) trans2, (char *) gold2) != 0) {
        errors = 1;
    }

    free(trans1);
    free(trans2);
    return errors;
}

int normalize_amp() {
    int errors = 0;
    
    unsigned char *buf1 = (unsigned char *) 
        "&amp; &amp! &amp &am! &am &a! &a &! & &am";
    size_t buf1_size = strlen((char *) buf1);
    unsigned char *gold1 = (unsigned char *) 
        "& &amp! &amp &am! &am &a! &a &! & &am";
    unsigned char *trans1 = malloc(
        sizeof(unsigned char) * strlen((char *) gold1));
    NL_normalize_ampersand(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }

    free(trans1);
    return errors;

}

int get_size_for_escape() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "\\/ / * \\*";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2;
    size_t pred_escape_size = NL_get_size_escaped_forward_slash_asterisk(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        errors = 1;
    }

    return errors;
}

int escape_forward_slash_asterisk() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "/ \\/ * \\*";
    unsigned char *gold1 = (unsigned char *) 
        "\\/ \\/ \\* \\*";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 2;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size);
    NL_escape_forward_slash_asterisk(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }

    free(trans1);
    return errors;
}

int space_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are 4 spaces ";
    unsigned char *gold1 = (unsigned char *) 
        "there\xc2\xa0" "are\xc2\xa0" "4\xc2\xa0spaces\xc2\xa0";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size);
    NL_normalize_spaces(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }

    free(trans1);
    return errors;
}


int get_size_for_space_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are 4 spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 4;
    size_t pred_escape_size = NL_get_size_normalized_spaces(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        errors = 1;
    }

    return errors;
}

int get_size_for_parens_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are (4 )spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2*4;
    size_t pred_escape_size = NL_get_size_normalized_parentheses(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        errors = 1;
    }

    return errors;
}

int parens_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are (4) spaces";
    unsigned char *gold1 = (unsigned char *) 
        "there are -LRB-4-RRB- spaces";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4 * 2;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size);
    NL_normalize_parentheses(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }

    free(trans1);
    return errors;
}

int get_size_for_spaces_parens_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are (4) spaces ";
    size_t buf1_size = strlen((char *) buf1);
    size_t gold_escape_size = buf1_size + 2*4 + 4;
    size_t pred_escape_size = NL_get_size_normalized_spaces_parens(
        buf1, buf1_size);

    if (pred_escape_size != gold_escape_size) {
        errors = 1;
    }

    return errors;
}

int spaces_parens_normalizer() {
    int errors = 0;

    unsigned char *buf1 = (unsigned char *) 
        "there are (3) spaces";
    unsigned char *gold1 = (unsigned char *) 
        "there\xC2\xA0" "are\xC2\xA0-LRB-3-RRB-\xC2\xA0spaces";

    size_t buf1_size = strlen((char *) buf1);
    size_t escape_size = buf1_size + 4 * 2 + 3;
    unsigned char *trans1 = malloc(sizeof(unsigned char) * escape_size);
    NL_normalize_parens_spaces(buf1, buf1_size, trans1);

    printf("TRANS1 : %s\n", trans1);
    printf("GOLD1  : %s\n", gold1);
    if (strcmp((char *) trans1, (char *) gold1) != 0) {
        errors = 1;
    }

    free(trans1);
    return errors;
}

int main() {

    if (get_size_for_spaces_parens_normalizer() != 0) {
        printf("get_size_for_spaces_parens_normalizer test failed!\n");
    } else {
        printf("get_size_for_spaces_parens_normalizer test success!\n");
    }  

    if (spaces_parens_normalizer() != 0) {
        printf("spaces_parens_normalizer test failed!\n");
    } else {
        printf("spaces_parens_normalizer test success!\n");
    }   

    exit(1);

    if (get_size_for_parens_normalizer() != 0) {
        printf("get_size_for_parens_normalizer test failed!\n");
    } else {
        printf("get_size_for_parens_normalizer test success!\n");
    }   
    if (parens_normalizer() != 0) {
        printf("parens_normalizer test failed!\n");
    } else {
        printf("parens_normalizer test success!\n");
    }   



    if (get_size_for_space_normalizer() != 0) {
        printf("get_size_for_space_normalizer test failed!\n");
    } else {
        printf("get_size_for_space_normalizer test success!\n");
    }   


    if (space_normalizer() != 0) {
        printf("space_normalizer test failed!\n");
    } else {
        printf("space_normalizer test success!\n");
    }   



    if (get_size_for_escape() != 0) {
        printf("get_size_for_escape test failed!\n");
    } else {
        printf("get_size_for_escape test success!\n");
    }   

    if (escape_forward_slash_asterisk() != 0) {
        printf("escape forward slash asterisk test failed!\n");
    } else {
        printf("escape forward slash asterisk test success!\n");
    }   



    if (normalize_amp() != 0) {
        printf("normalize amp test failed!\n");
    } else {
        printf("normalize test success!\n");
    }   


    if (copy_no_softhyphen() != 0) {
        printf("copy no softhypen test failed!\n");
    } else {
        printf("copy no softhypen test success!\n");
    }   

    if (latex_quotes_count() !=0) {
        printf("latex quotes counter test failed!\n");

    } else {
        printf("latex quotes counter test success!\n");
    } 

    if (latex_quotes_prob_left_transform() !=0) {
        printf("latex quotes prob left transform test failed!\n");

    } else {
        printf("latex quotes prob left transform test success!\n");
    } 

    if (latex_quotes_prob_right_transform() !=0) {
        printf("latex quotes prob right transform test failed!\n");

    } else {
        printf("latex quotes prob right transform test success!\n");
    } 





    if (ascii_quotes_count() !=0) {
        printf("ascii quotes counter test failed!\n");

    } else {
        printf("ascii quotes counter test success!\n");
    } 

    if (ascii_quotes_transform() !=0) {
        printf("ascii quotes transform test failed!\n");

    } else {
        printf("ascii quotes transform test success!\n");
    } 





    if (unicode_quotes_count() !=0) {
        printf("unicode quotes counter test failed!\n");

    } else {
        printf("unicode quotes counter test success!\n");
    }   


    if (left_unicode_quotes_transform() !=0) {
        printf("left unicode quotes transform test failed!\n");

    } else {
        printf("left unicode quotes transform test success!\n");
    }  

    if (right_unicode_quotes_transform() !=0) {
        printf("right unicode quotes transform test failed!\n");

    } else {
        printf("right unicode quotes transform test success!\n");
    }  

    if (test_token1() != 0) {
        printf("token test1 failed!\n");

    } else {
        printf("token test1 passed!\n");
    }


    if (ptbtest() !=0) {
        printf("ptb test failed!\n");

    } else {
        printf("ptb test success!\n");

    }   

    return 0;
}