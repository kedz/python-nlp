#include "tokenizer_utils.h"

%%{


#  private static final Pattern singleQuote = Pattern.compile("&apos;|'");
#  private static final Pattern doubleQuote = Pattern.compile("\"|&quot;");

#  // 91,92,93,94 aren't valid unicode points, but sometimes they show
#  // up from cp1252 and need to be translated
#  private static final Pattern leftSingleQuote = Pattern.compile("[\u0091\u2018\u201B\u2039]");
#  private static final Pattern rightSingleQuote = Pattern.compile("[\u0092\u2019\u203A]");
#  private static final Pattern leftDoubleQuote = Pattern.compile("[\u0093\u201C\u00AB]");
#  private static final Pattern rightDoubleQuote = Pattern.compile("[\u0094\u201D\u00BB]");

#  private static final Pattern unicodeLeftSingleQuote = Pattern.compile("\u0091");
#  private static final Pattern unicodeRightSingleQuote = Pattern.compile("\u0092");
#  private static final Pattern unicodeLeftDoubleQuote = Pattern.compile("\u0093");
#  private static final Pattern unicodeRightDoubleQuote = Pattern.compile("\u0094");

#  private static String unicodeQuotes(String in, boolean probablyLeft) {
#    String s1 = in;
#    if (probablyLeft) {
#      s1 = singleQuote.matcher(s1).replaceAll("\u2018");
#      s1 = doubleQuote.matcher(s1).replaceAll("\u201c");
#    } else {
#      s1 = singleQuote.matcher(s1).replaceAll("\u2019");
#      s1 = doubleQuote.matcher(s1).replaceAll("\u201d");
#    }
#    s1 = unicodeLeftSingleQuote.matcher(s1).replaceAll("\u2018");
#    s1 = unicodeRightSingleQuote.matcher(s1).replaceAll("\u2019");
#    s1 = unicodeLeftDoubleQuote.matcher(s1).replaceAll("\u201c");
#    s1 = unicodeRightDoubleQuote.matcher(s1).replaceAll("\u201d");
#    return s1;
#  }




    machine NonUnicodeQuoteCounter;
    alphtype unsigned char;

    SINGLE_QUOTE = "'"  | "&apos;" ;
    DOUBLE_QUOTE = "\"" | "&quot;" ;
    LEFT_SINGLE_QUOTE = 0xC2 0x91 ;  # u0091
    RIGHT_SINGLE_QUOTE = 0xC2 0x92 ;  # u0092

    LEFT_DOUBLE_QUOTE = 0xC2 0x93 ;  # u0093
    RIGHT_DOUBLE_QUOTE = 0xC2 0x94 ;  # u0094
    QUOTE =   SINGLE_QUOTE 
            | DOUBLE_QUOTE 
            | LEFT_SINGLE_QUOTE
            | RIGHT_SINGLE_QUOTE
            | LEFT_DOUBLE_QUOTE
            | RIGHT_DOUBLE_QUOTE ;

#  91,92,93,94 aren't valid unicode points, but sometimes they show
#  up from cp1252 and need to be translated

#    SINGLE_QUOTE = "'"  | "&apos;";
#    DOUBLE_QUOTE = "\"" | "&quot;";
#    LEFT_SINGLE_QUOTE = 0xC2 0x91   # u0091
#        | 0xE2 0x80 0x98            # u2018
#        | 0xE2 0x80 0x9B            # u201B
#        | 0xE2 0x80 0xB9            # u2039
#        ;
#    RIGHT_SINGLE_QUOTE = 0xC2 0x92  # u0092
#        | 0xE2 0x80 0x99            # u2019
#        | 0xE2 0x80 0xBA            # u203A
#        ;

    main := |* 
        QUOTE => {size += 3;};
        any => {size++;};
    *|;

}%%

%% write data nofinal;

size_t NL_get_size_unicode_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    %% write init;
    %% write exec;

    return size;
}

%%{

    machine ProbablyLeftUnicodeQuoteTransformer;
    alphtype unsigned char;

    SINGLE_QUOTE = "'"  | "&apos;" ;
    DOUBLE_QUOTE = "\"" | "&quot;" ;
    LEFT_SINGLE_QUOTE = 0xC2 0x91 ;  # u0091
    RIGHT_SINGLE_QUOTE = 0xC2 0x92 ;  # u0092

    LEFT_DOUBLE_QUOTE = 0xC2 0x93 ;  # u0093
    RIGHT_DOUBLE_QUOTE = 0xC2 0x94 ;  # u0094

    action TransformLeftSingleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }

    action TransformRightSingleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }

    action TransformLeftDoubleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }

    action TransformRightDoubleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }

    main := |* 
        SINGLE_QUOTE        => TransformLeftSingleQuote ;
        DOUBLE_QUOTE        => TransformLeftDoubleQuote ;
        LEFT_SINGLE_QUOTE   => TransformLeftSingleQuote ;
        LEFT_DOUBLE_QUOTE   => TransformLeftDoubleQuote ;
        RIGHT_SINGLE_QUOTE  => TransformRightSingleQuote ;
        RIGHT_DOUBLE_QUOTE  => TransformRightDoubleQuote ; 
        any => { *transform = *fpc; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_unicode_quotes_probably_left(unsigned char *p, size_t buf_length,
    unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;
}

%%{

    machine ProbablyRightUnicodeQuoteTransformer;
    alphtype unsigned char;

    SINGLE_QUOTE = "'"  | "&apos;" ;
    DOUBLE_QUOTE = "\"" | "&quot;" ;
    LEFT_SINGLE_QUOTE = 0xC2 0x91 ;  # u0091
    RIGHT_SINGLE_QUOTE = 0xC2 0x92 ;  # u0092

    LEFT_DOUBLE_QUOTE = 0xC2 0x93 ;  # u0093
    RIGHT_DOUBLE_QUOTE = 0xC2 0x94 ;  # u0094

    action TransformLeftSingleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }

    action TransformRightSingleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }

    action TransformLeftDoubleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }

    action TransformRightDoubleQuote {
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }

    main := |* 
        SINGLE_QUOTE        => TransformRightSingleQuote ;
        DOUBLE_QUOTE        => TransformRightDoubleQuote ;
        LEFT_SINGLE_QUOTE   => TransformLeftSingleQuote ;
        LEFT_DOUBLE_QUOTE   => TransformLeftDoubleQuote ;
        RIGHT_SINGLE_QUOTE  => TransformRightSingleQuote ;
        RIGHT_DOUBLE_QUOTE  => TransformRightDoubleQuote ; 
        any => { *transform = *fpc; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_unicode_quotes_probably_right(unsigned char *p, size_t buf_length,
    unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

%%{

    machine NonAsciiQuoteCounter;
    alphtype unsigned char;

    SINGLE_QUOTES =   "&apos;" 
                    | 0xC2 0x91         # U+0091 
                    | 0xE2 0x80 0x98    # U+2018 unicode left single quote
                    | 0xC2 0x92         # U+0092
                    | 0xE2 0x80 0x99    # U+2019 unicode right single quote
                    | 0xE2 0x80 0x9A    # U+201A low single quote
                    | 0xE2 0x80 0x9B    # U+201B low single quote
                    | 0xE2 0x80 0xB9    # U+2039 left pointing angle
                    | 0xE2 0x80 0xBA    # U+203A right pointing angle
                    ;

    DOUBLE_QUOTES =   "&quot;"
                    | 0xC2 0x93         # U+0093
                    | 0xE2 0x80 0x9C    # U+201C unicode left double quote
                    | 0xC2 0x94         # U+0094
                    | 0xC2 0x80 0x9D    # U+201D unicode right double quote
                    | 0xC2 0x80 0x9E    # U+201E low double quote
                    | 0xC2 0xAB         # U+00AB left double angle
                    | 0xC2 0xBB         # U+00BB right double angle
                    ;

    QUOTE =   SINGLE_QUOTES | DOUBLE_QUOTES;

    main := |* 
        QUOTE => {size++;};
        any => {size++;};
    *|;

}%%

%% write data nofinal;

size_t NL_get_size_ascii_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    %% write init;
    %% write exec;

    return size;
}

%%{

    machine AsciiQuoteTransformer;
    alphtype unsigned char;

    SINGLE_QUOTES =   "&apos;" 
                    | 0xC2 0x91         # U+0091 
                    | 0xE2 0x80 0x98    # U+2018 unicode left single quote
                    | 0xC2 0x92         # U+0092
                    | 0xE2 0x80 0x99    # U+2019 unicode right single quote
                    | 0xE2 0x80 0x9A    # U+201A low single quote
                    | 0xE2 0x80 0x9B    # U+201B low single quote
                    | 0xE2 0x80 0xB9    # U+2039 left pointing angle
                    | 0xE2 0x80 0xBA    # U+203A right pointing angle
                    ;

    DOUBLE_QUOTES =   "&quot;"
                    | 0xC2 0x93         # U+0093
                    | 0xE2 0x80 0x9C    # U+201C unicode left double quote
                    | 0xC2 0x94         # U+0094
                    | 0xC2 0x80 0x9D    # U+201D unicode right double quote
                    | 0xC2 0x80 0x9E    # U+201E low double quote
                    | 0xC2 0xAB         # U+00AB left double angle
                    | 0xC2 0xBB         # U+00BB right double angle
                    ;

    main := |* 
        SINGLE_QUOTES => { *transform = '\''; transform++; };
        DOUBLE_QUOTES => { *transform = '"'; transform++; };
        any => { *transform = *fpc; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_ascii_quotes(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

    return;
}

%%{

    machine NonLatexQuoteCounter;
    alphtype unsigned char;

    SINGLE_QUOTES =   "'" 
                    | "&apos;" 
                    | 0xC2 0x91         # U+0091 
                    | 0xE2 0x80 0x98    # U+2018 unicode left single quote
                    | 0xC2 0x92         # U+0092
                    | 0xE2 0x80 0x99    # U+2019 unicode right single quote
                    | 0xE2 0x80 0x9A    # U+201A low single quote
                    | 0xE2 0x80 0x9B    # U+201B low single quote
                    | 0xE2 0x80 0xB9    # U+2039 left pointing angle
                    | 0xE2 0x80 0xBA    # U+203A right pointing angle
                    ;

    DOUBLE_QUOTES =   "\""
                    | "&quot;"
                    | 0xC2 0x93         # U+0093
                    | 0xE2 0x80 0x9C    # U+201C unicode left double quote
                    | 0xC2 0x94         # U+0094
                    | 0xC2 0x80 0x9D    # U+201D unicode right double quote
                    | 0xC2 0xAB         # U+00AB left double angle
                    | 0xC2 0xBB         # U+00BB right double angle
                    ;

    QUOTE =   SINGLE_QUOTES | DOUBLE_QUOTES;

    main := |* 
        SINGLE_QUOTES => {size++;};
        DOUBLE_QUOTES => {size += 2;};
        any => {size++;};
    *|;

}%%

%% write data nofinal;

size_t NL_get_size_latex_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    %% write init;
    %% write exec;

    return size;
}

%%{

    machine ProbablyLeftLatexQuoteCounter;
    alphtype unsigned char;

    SINGLE_QUOTES = "'" | "&apos;" ;
    DOUBLE_QUOTES = "\"" | "&quot;" ;

    LEFT_SINGLE_QUOTES =  0xC2 0x91         # U+0091 
                        | 0xE2 0x80 0x98    # U+2018 unicode left single quote
                        | 0xE2 0x80 0x9B    # U+201B low single quote
                        | 0xE2 0x80 0xB9    # U+2039 left pointing angle
                        ; 

    RIGHT_SINGLE_QUOTES = 0xC2 0x92         # U+0092
                        | 0xE2 0x80 0x99    # U+2019 unicode right single quote
                        | 0xE2 0x80 0x9A    # U+201A low single quote
                        | 0xE2 0x80 0xBA    # U+203A right pointing angle
                        ;

    LEFT_DOUBLE_QUOTES =  0xC2 0x93         # U+0093
                        | 0xE2 0x80 0x9C    # U+201C unicode left double quote
                        | 0xC2 0xAB         # U+00AB left double angle
                        ;

    RIGHT_DOUBLE_QUOTES = 0xC2 0x94         # U+0094
                        | 0xC2 0x80 0x9D    # U+201D unicode right double quote
                        | 0xC2 0xBB         # U+00BB right double angle
                        ;


    main := |* 
        SINGLE_QUOTES => { *transform = '`'; transform++; };
        DOUBLE_QUOTES => { *transform = '`'; transform++; 
                           *transform = '`'; transform++; };

        LEFT_SINGLE_QUOTES => { *transform = '`'; transform++; };
        RIGHT_SINGLE_QUOTES => { *transform = '\''; transform++; };
    
        LEFT_DOUBLE_QUOTES => { *transform = '`'; transform++; 
                           *transform = '`'; transform++; };
    
        RIGHT_DOUBLE_QUOTES => { *transform = '\''; transform++; 
                                 *transform = '\''; transform++; };
        any => {*transform = *fpc; transform++;};
    *|;

}%%

%% write data nofinal;

void NL_latex_quotes_probably_left(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

%%{

    machine ProbablyRightLatexQuoteCounter;
    alphtype unsigned char;

    SINGLE_QUOTES = "'" | "&apos;" ;
    DOUBLE_QUOTES = "\"" | "&quot;" ;

    LEFT_SINGLE_QUOTES =  0xC2 0x91         # U+0091 
                        | 0xE2 0x80 0x98    # U+2018 unicode left single quote
                        | 0xE2 0x80 0x9B    # U+201B low single quote
                        | 0xE2 0x80 0xB9    # U+2039 left pointing angle
                        ; 

    RIGHT_SINGLE_QUOTES = 0xC2 0x92         # U+0092
                        | 0xE2 0x80 0x99    # U+2019 unicode right single quote
                        | 0xE2 0x80 0x9A    # U+201A low single quote
                        | 0xE2 0x80 0xBA    # U+203A right pointing angle
                        ;

    LEFT_DOUBLE_QUOTES =  0xC2 0x93         # U+0093
                        | 0xE2 0x80 0x9C    # U+201C unicode left double quote
                        | 0xC2 0xAB         # U+00AB left double angle
                        ;

    RIGHT_DOUBLE_QUOTES = 0xC2 0x94         # U+0094
                        | 0xC2 0x80 0x9D    # U+201D unicode right double quote
                        | 0xC2 0xBB         # U+00BB right double angle
                        ;

    main := |* 
        SINGLE_QUOTES => { *transform = '\''; transform++; };
        DOUBLE_QUOTES => { *transform = '\''; transform++; 
                           *transform = '\''; transform++; };

        LEFT_SINGLE_QUOTES => { *transform = '`'; transform++; };
        RIGHT_SINGLE_QUOTES => { *transform = '\''; transform++; };
    
        LEFT_DOUBLE_QUOTES => { *transform = '`'; transform++; 
                           *transform = '`'; transform++; };
    
        RIGHT_DOUBLE_QUOTES => { *transform = '\''; transform++; 
                                 *transform = '\''; transform++; };
        any => {*transform = *fpc; transform++;};
    *|;

}%%

%% write data nofinal;

void NL_latex_quotes_probably_right(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

%%{

    machine CopyNoSoftHypen;
    alphtype unsigned char;

    SF = 0xC2 0xAD;
    action Act1 {
        *transform = *(fpc); transform++;
    }

    action Act2 {
        *transform = *(fpc - 1);
        transform++;       
        *transform = *fpc;
        transform++;       
    }

    main := ( (0xC2 (0xAD | ^0xAD >Act2) | ^0xC2 >Act1) )+ ;
              

}%%

%% write data nofinal;

void NL_copy_no_softhyphen(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs;
    unsigned char *pe = p + buf_length; 

    %% write init;
    %% write exec;

}

%%{

    machine NormalizeAmps;
    alphtype unsigned char;

              
    main := |* 
        /&amp;/i => { *transform = '&'; transform++; };
        any => { *transform = *fpc; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_normalize_ampersand(unsigned char *p, size_t buf_length,
        unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

%%{

    machine CountUnescapedForwardSlashesAsterisks;
    alphtype unsigned char;

              
    main := |* 
        "\\/" | "\\*" => { count += 2; };
        "/"   | "*"   => { count += 2; };
        any => { count++; };
    *|;

}%%

%% write data nofinal;

size_t NL_get_size_escaped_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t count = 0;

    %% write init;
    %% write exec;

    return count;
}

%%{

    machine EscapedForwardSlashesAsterisks;
    alphtype unsigned char;
              
    main := |* 
        "\\/" => {
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        };
        "\\*" => { 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        };
        "/" => {
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        };
        "*" => { 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        };
        any => { *transform = *ts; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_escape_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length, unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

%%{

    machine CountSpaces;
    alphtype unsigned char;
              
    main := |* 
        " " => { count += 2; };
        any => { count++; };
    *|;

}%%

%% write data nofinal;

size_t NL_get_size_normalized_spaces(unsigned char *p, 
    size_t buf_length) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t count = 0;

    %% write init;
    %% write exec;

    return count;
}

%%{

    machine NormalizeSpaces;
    alphtype unsigned char;
              
    main := |* 
        " " => {
            *transform = 0xC2; transform++;
            *transform = 0xA0; transform++;
        };
        [^ ] => { *transform = *ts; transform++; };
    *|;

}%%

%% write data nofinal;

void NL_normalize_spaces(unsigned char *p, 
    size_t buf_length, unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    %% write init;
    %% write exec;

}

size_t NL_get_size_normalized_parentheses(unsigned char *p, 
    size_t buf_length) {

    unsigned char *end = p + buf_length;
    size_t count = buf_length;
    while ( p < end ) {
        if (*p == '(' || *p == ')')
            count += 4;
        p++;
    }

    return count;
}

void NL_normalize_parentheses(unsigned char *p, size_t buf_length, 
        unsigned char *transform) {

    unsigned char *end = p + buf_length;
    while ( p < end ) {
        if (*p == '(') {
            *transform = '-'; transform++;
            *transform = 'L'; transform++;
            *transform = 'R'; transform++;
            *transform = 'B'; transform++;
            *transform = '-'; transform++;
        } else if (*p == ')') {
            *transform = '-'; transform++;
            *transform = 'R'; transform++;
            *transform = 'R'; transform++;
            *transform = 'B'; transform++;
            *transform = '-'; transform++;
        } else {
            *transform = *p; transform++;
        }
        p++;
    }

}

size_t NL_get_size_normalized_spaces_parens(unsigned char *p, 
    size_t buf_length) {

    unsigned char *end = p + buf_length;
    size_t count = buf_length;
    while ( p < end ) {
        if (*p == '(' || *p == ')')
            count += 4;
        else if (*p ==  ' ')
            count++;
        p++;
    }

    return count;
}

void NL_normalize_parens_spaces(unsigned char *p, size_t buf_length, 
        unsigned char *transform) {

    unsigned char *end = p + buf_length;
    while ( p < end ) {
        if (*p == '(') {
            *transform = '-'; transform++;
            *transform = 'L'; transform++;
            *transform = 'R'; transform++;
            *transform = 'B'; transform++;
            *transform = '-'; transform++;
        } else if (*p == ')') {
            *transform = '-'; transform++;
            *transform = 'R'; transform++;
            *transform = 'R'; transform++;
            *transform = 'B'; transform++;
            *transform = '-'; transform++;
        } else if (*p == ' ') {
            *transform = 0xC2; transform++;
            *transform = 0xA0; transform++;
        } else {
            *transform = *p; transform++;
        }
        p++;
    }

}

size_t NL_get_size_normalized_spaces_slashes(unsigned char *p, 
    size_t buf_length) {

    unsigned char *end = p + buf_length;
    size_t count = buf_length;
    while ( p < end ) {
        if (*p ==  ' ' || *p == '/')
            count++;
        else if (*p == '\\') { 
            if (p < end - 1 && *(p+1) != ' ') {
                p++;
            }
        }
        p++;
    }

    return count;
}

void NL_normalize_parens_slashes(unsigned char *p, size_t buf_length, 
        unsigned char *transform) {

    unsigned char *end = p + buf_length;
    while ( p < end ) {
        if (*p == ' ') {
            *transform = 0xC2; transform++;
            *transform = 0xA0; transform++;
        } else if (*p == '/') {
            *transform = '\\'; transform++;
            *transform = '/'; transform++;
        } else if (*p == '\\') {
            if (p < end - 1 && *(p+1) != ' ') {
                *transform = *p; transform++; p++;
            } 
            *transform = *p; transform++;
        } else {
            *transform = *p; transform++;
        }
        p++;
    }

}
