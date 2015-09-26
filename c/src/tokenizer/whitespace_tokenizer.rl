#include "whitespace_tokenizer.h"

%%{

    machine ws_tok;
    alphtype unsigned char;

    include WChar "unicode.rl";

    SPACE = " " 
        | "\t" 
        | 0xC2 0xA0
        | 0xE2 0x80 0x80..0x8A
        | 0xE3 0x80 0x80 ;

    SPACES = SPACE+;

    ALL_SPACES =      SPACES 
                    | 0xE2 0x80 0x8B  # U+200B zero width space
                    | 0xE2 0x80 0x8E  # U+200E left-to-right mark
                    | 0xE2 0x80 0x8F  # U+200F right-to-left mark
                    | 0xEF 0xBB 0xBF  # U+FEFF zero width no-break space
                    ;

    NEWLINE = "\r"
        | "\r" ? "\n" 
        | 0xE2 0x80 0xA8
        | 0xE2 0x80 0xA9
        | 0x0B
        | 0x0C 
        | 0xC2 0x85;

    SPACENL = SPACE | NEWLINE ;

    action NextToken {
        NL_add_bspan(mgr, ann, ts, fpc - ts, NULL, 0);
    }
 

    WS = SPACENL+ >NextToken;

    WORD = ((any+) -- (SPACENL+)) >{ ts = fpc; } ;
    TWS = (SPACENL+)  >NextToken;

    SWS = (SPACENL+) %{ ts = fpc; };

    main :=   (SWS ((WORD TWS)+)) 
            | (SWS ((WORD TWS)+) WORD) %NextToken
            | ((WORD TWS)+) 
            | (((WORD TWS)+) WORD) %NextToken; 

}%%

%% write data nofinal;

NL_annotations *NL_ws_tokenize(NL_buffer *buffer, NL_v_memmgr *mgr) {
    int cs;
    unsigned char *p = buffer->bytes;  
    unsigned char *pe = p + buffer->size; 
    unsigned char *eof = pe;
    unsigned char *ts = p;

    NL_annotations *ann = NL_new_bspan_annotations(mgr);

    %% write init;

    %% write exec;

    return ann;

}
