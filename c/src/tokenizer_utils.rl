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

