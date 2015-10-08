#include "conll_reader.h"

%%{

    machine ws_tok;
    alphtype unsigned char;

    WORD = ([^ \t\n]+) >{ ts = fpc;} ;
    POS = ([^\n]+) >{ ts = fpc;} ;
    TAB = ([ \t]+) >{ NL_add_bspan(mgr, tokens, ts, fpc - ts, NULL, 0); };
    POSEND = '\n' >{ NL_add_bspan(mgr, pos, ts, fpc - ts, NULL, 0); };

    SENT = '\n' >{ 
        NL_add_sspan(
            mgr, sents, sent_start, tokens->size - sent_start, NULL, 0);
        sent_start = tokens->size;
    };
    main :=  (WORD TAB POS POSEND SENT?)+;

}%%

%% write data nofinal;

NL_doc *NL_read_conll_buffer(NL_buffer *buffer, NL_v_memmgr *mgr) {
    int cs;
    unsigned char *p = buffer->bytes;  
    unsigned char *pe = p + buffer->size; 
    unsigned char *eof = pe;
    unsigned char *ts = p;
    NL_annotations *tokens = NL_new_bspan_annotations(mgr);
    NL_annotations *pos = NL_new_bspan_annotations(mgr);
    NL_annotations *sents = NL_new_sspan_annotations(mgr);

    size_t sent_start = 0;

    %% write init;

    %% write exec;

    NL_doc *doc = NL_allocate_mem_size(mgr, sizeof(NL_doc));
    doc->buffer = buffer;
    doc->tokens = tokens;
    doc->pos_tags = pos;
    doc->ner_tags = NULL;
    doc->sentences = sents;

    return doc;

}
