
#line 1 "tokenizer_utils.rl"
#include "tokenizer_utils.h"


#line 77 "tokenizer_utils.rl"



#line 11 "tokenizer_utils.c"
static const int NonUnicodeQuoteCounter_start = 7;
static const int NonUnicodeQuoteCounter_error = -1;

static const int NonUnicodeQuoteCounter_en_main = 7;


#line 80 "tokenizer_utils.rl"

size_t NL_get_size_unicode_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    
#line 28 "tokenizer_utils.c"
	{
	cs = NonUnicodeQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 89 "tokenizer_utils.rl"
    
#line 38 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 74 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	goto st7;
tr4:
#line 73 "tokenizer_utils.rl"
	{te = p+1;{size += 3;}}
	goto st7;
tr7:
#line 74 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	goto st7;
tr10:
#line 74 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	goto st7;
st7:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 1 "NONE"
	{ts = p;}
#line 68 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr4;
		case 38u: goto tr8;
		case 39u: goto tr4;
		case 194u: goto st9;
	}
	goto tr7;
tr8:
#line 1 "NONE"
	{te = p+1;}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 84 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr10;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st3;
	goto tr0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( 145u <= (*p) && (*p) <= 148u )
		goto tr4;
	goto tr10;
	}
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 8: goto tr10;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 9: goto tr10;
	}
	}

	}

#line 90 "tokenizer_utils.rl"

    return size;
}


#line 153 "tokenizer_utils.rl"



#line 186 "tokenizer_utils.c"
static const int ProbablyLeftUnicodeQuoteTransformer_start = 8;
static const int ProbablyLeftUnicodeQuoteTransformer_error = -1;

static const int ProbablyLeftUnicodeQuoteTransformer_en_main = 8;


#line 156 "tokenizer_utils.rl"

void NL_unicode_quotes_probably_left(unsigned char *p, size_t buf_length,
    unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 203 "tokenizer_utils.c"
	{
	cs = ProbablyLeftUnicodeQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 165 "tokenizer_utils.rl"
    
#line 213 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 150 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	goto st8;
tr4:
#line 107 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	goto st8;
tr8:
#line 125 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	goto st8;
tr9:
#line 150 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	goto st8;
tr12:
#line 150 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	goto st8;
tr15:
#line 107 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	goto st8;
tr16:
#line 116 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	goto st8;
tr17:
#line 125 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	goto st8;
tr18:
#line 134 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	goto st8;
st8:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 1 "NONE"
	{ts = p;}
#line 305 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr8;
		case 38u: goto tr10;
		case 39u: goto tr4;
		case 194u: goto st10;
	}
	goto tr9;
tr10:
#line 1 "NONE"
	{te = p+1;}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 321 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr12;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 145u: goto tr15;
		case 146u: goto tr16;
		case 147u: goto tr17;
		case 148u: goto tr18;
	}
	goto tr12;
	}
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 9: goto tr12;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 10: goto tr12;
	}
	}

	}

#line 166 "tokenizer_utils.rl"
}


#line 227 "tokenizer_utils.rl"



#line 434 "tokenizer_utils.c"
static const int ProbablyRightUnicodeQuoteTransformer_start = 8;
static const int ProbablyRightUnicodeQuoteTransformer_error = -1;

static const int ProbablyRightUnicodeQuoteTransformer_en_main = 8;


#line 230 "tokenizer_utils.rl"

void NL_unicode_quotes_probably_right(unsigned char *p, size_t buf_length,
    unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 451 "tokenizer_utils.c"
	{
	cs = ProbablyRightUnicodeQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 239 "tokenizer_utils.rl"
    
#line 461 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 224 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	goto st8;
tr4:
#line 190 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	goto st8;
tr8:
#line 208 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	goto st8;
tr9:
#line 224 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	goto st8;
tr12:
#line 224 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	goto st8;
tr15:
#line 181 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	goto st8;
tr16:
#line 190 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	goto st8;
tr17:
#line 199 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	goto st8;
tr18:
#line 208 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	goto st8;
st8:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 1 "NONE"
	{ts = p;}
#line 553 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr8;
		case 38u: goto tr10;
		case 39u: goto tr4;
		case 194u: goto st10;
	}
	goto tr9;
tr10:
#line 1 "NONE"
	{te = p+1;}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 569 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr12;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	switch( (*p) ) {
		case 145u: goto tr15;
		case 146u: goto tr16;
		case 147u: goto tr17;
		case 148u: goto tr18;
	}
	goto tr12;
	}
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 9: goto tr12;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 10: goto tr12;
	}
	}

	}

#line 240 "tokenizer_utils.rl"

}


#line 276 "tokenizer_utils.rl"



#line 683 "tokenizer_utils.c"
static const int NonAsciiQuoteCounter_start = 9;
static const int NonAsciiQuoteCounter_error = -1;

static const int NonAsciiQuoteCounter_en_main = 9;


#line 279 "tokenizer_utils.rl"

size_t NL_get_size_ascii_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    
#line 700 "tokenizer_utils.c"
	{
	cs = NonAsciiQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 288 "tokenizer_utils.rl"
    
#line 710 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 273 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	goto st9;
tr4:
#line 272 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	goto st9;
tr7:
#line 273 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	goto st9;
tr11:
#line 273 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	goto st9;
st9:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 1 "NONE"
	{ts = p;}
#line 740 "tokenizer_utils.c"
	switch( (*p) ) {
		case 38u: goto tr8;
		case 194u: goto tr9;
		case 226u: goto tr10;
	}
	goto tr7;
tr8:
#line 1 "NONE"
	{te = p+1;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 755 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr11;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st3;
	goto tr0;
tr9:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 818 "tokenizer_utils.c"
	switch( (*p) ) {
		case 128u: goto st7;
		case 171u: goto tr4;
		case 187u: goto tr4;
	}
	if ( 145u <= (*p) && (*p) <= 148u )
		goto tr4;
	goto tr11;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( 157u <= (*p) && (*p) <= 158u )
		goto tr4;
	goto tr0;
tr10:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 842 "tokenizer_utils.c"
	if ( (*p) == 128u )
		goto st8;
	goto tr11;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) > 156u ) {
		if ( 185u <= (*p) && (*p) <= 186u )
			goto tr4;
	} else if ( (*p) >= 152u )
		goto tr4;
	goto tr0;
	}
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 10: goto tr11;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 11: goto tr11;
	case 7: goto tr0;
	case 12: goto tr11;
	case 8: goto tr0;
	}
	}

	}

#line 289 "tokenizer_utils.rl"

    return size;
}


#line 325 "tokenizer_utils.rl"



#line 902 "tokenizer_utils.c"
static const int AsciiQuoteTransformer_start = 10;
static const int AsciiQuoteTransformer_error = -1;

static const int AsciiQuoteTransformer_en_main = 10;


#line 328 "tokenizer_utils.rl"

void NL_ascii_quotes(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 919 "tokenizer_utils.c"
	{
	cs = AsciiQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 337 "tokenizer_utils.rl"
    
#line 929 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 322 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	goto st10;
tr4:
#line 320 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	goto st10;
tr8:
#line 321 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '"'; transform++; }}
	goto st10;
tr9:
#line 322 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	goto st10;
tr13:
#line 322 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	goto st10;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1 "NONE"
	{ts = p;}
#line 963 "tokenizer_utils.c"
	switch( (*p) ) {
		case 38u: goto tr10;
		case 194u: goto tr11;
		case 226u: goto tr12;
	}
	goto tr9;
tr10:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 978 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr13;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
tr11:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1048 "tokenizer_utils.c"
	switch( (*p) ) {
		case 128u: goto st8;
		case 171u: goto tr8;
		case 187u: goto tr8;
	}
	if ( (*p) > 146u ) {
		if ( 147u <= (*p) && (*p) <= 148u )
			goto tr8;
	} else if ( (*p) >= 145u )
		goto tr4;
	goto tr13;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( 157u <= (*p) && (*p) <= 158u )
		goto tr8;
	goto tr0;
tr12:
#line 1 "NONE"
	{te = p+1;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 1075 "tokenizer_utils.c"
	if ( (*p) == 128u )
		goto st9;
	goto tr13;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 156u )
		goto tr8;
	if ( (*p) > 155u ) {
		if ( 185u <= (*p) && (*p) <= 186u )
			goto tr4;
	} else if ( (*p) >= 152u )
		goto tr4;
	goto tr0;
	}
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 11: goto tr13;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 12: goto tr13;
	case 8: goto tr0;
	case 13: goto tr13;
	case 9: goto tr0;
	}
	}

	}

#line 338 "tokenizer_utils.rl"

    return;
}


#line 377 "tokenizer_utils.rl"



#line 1139 "tokenizer_utils.c"
static const int NonLatexQuoteCounter_start = 10;
static const int NonLatexQuoteCounter_error = -1;

static const int NonLatexQuoteCounter_en_main = 10;


#line 380 "tokenizer_utils.rl"

size_t NL_get_size_latex_quotes(unsigned char *p, size_t buf_length) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t size = 0;

    
#line 1156 "tokenizer_utils.c"
	{
	cs = NonLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 389 "tokenizer_utils.rl"
    
#line 1166 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 374 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	goto st10;
tr4:
#line 372 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	goto st10;
tr8:
#line 373 "tokenizer_utils.rl"
	{te = p+1;{size += 2;}}
	goto st10;
tr9:
#line 374 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	goto st10;
tr13:
#line 374 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	goto st10;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1 "NONE"
	{ts = p;}
#line 1200 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr8;
		case 38u: goto tr10;
		case 39u: goto tr4;
		case 194u: goto tr11;
		case 226u: goto tr12;
	}
	goto tr9;
tr10:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 1217 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr13;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
tr11:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1287 "tokenizer_utils.c"
	switch( (*p) ) {
		case 128u: goto st8;
		case 171u: goto tr8;
		case 187u: goto tr8;
	}
	if ( (*p) > 146u ) {
		if ( 147u <= (*p) && (*p) <= 148u )
			goto tr8;
	} else if ( (*p) >= 145u )
		goto tr4;
	goto tr13;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 157u )
		goto tr8;
	goto tr0;
tr12:
#line 1 "NONE"
	{te = p+1;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 1314 "tokenizer_utils.c"
	if ( (*p) == 128u )
		goto st9;
	goto tr13;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 156u )
		goto tr8;
	if ( (*p) > 155u ) {
		if ( 185u <= (*p) && (*p) <= 186u )
			goto tr4;
	} else if ( (*p) >= 152u )
		goto tr4;
	goto tr0;
	}
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 11: goto tr13;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 12: goto tr13;
	case 8: goto tr0;
	case 13: goto tr13;
	case 9: goto tr0;
	}
	}

	}

#line 390 "tokenizer_utils.rl"

    return size;
}


#line 441 "tokenizer_utils.rl"



#line 1378 "tokenizer_utils.c"
static const int ProbablyLeftLatexQuoteCounter_start = 10;
static const int ProbablyLeftLatexQuoteCounter_error = -1;

static const int ProbablyLeftLatexQuoteCounter_en_main = 10;


#line 444 "tokenizer_utils.rl"

void NL_latex_quotes_probably_left(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 1395 "tokenizer_utils.c"
	{
	cs = ProbablyLeftLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 453 "tokenizer_utils.rl"
    
#line 1405 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 438 "tokenizer_utils.rl"
	{{p = ((te))-1;}{*transform = *p; transform++;}}
	goto st10;
tr4:
#line 426 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	goto st10;
tr8:
#line 427 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	goto st10;
tr9:
#line 436 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                                 *transform = '\''; transform++; }}
	goto st10;
tr10:
#line 430 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	goto st10;
tr11:
#line 431 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	goto st10;
tr12:
#line 433 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	goto st10;
tr13:
#line 438 "tokenizer_utils.rl"
	{te = p+1;{*transform = *p; transform++;}}
	goto st10;
tr17:
#line 438 "tokenizer_utils.rl"
	{te = p;p--;{*transform = *p; transform++;}}
	goto st10;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1 "NONE"
	{ts = p;}
#line 1458 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr8;
		case 38u: goto tr14;
		case 39u: goto tr4;
		case 194u: goto tr15;
		case 226u: goto tr16;
	}
	goto tr13;
tr14:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 1475 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr17;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
tr15:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1545 "tokenizer_utils.c"
	switch( (*p) ) {
		case 128u: goto st8;
		case 145u: goto tr10;
		case 146u: goto tr11;
		case 147u: goto tr12;
		case 148u: goto tr9;
		case 171u: goto tr12;
		case 187u: goto tr9;
	}
	goto tr17;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 157u )
		goto tr9;
	goto tr0;
tr16:
#line 1 "NONE"
	{te = p+1;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 1571 "tokenizer_utils.c"
	if ( (*p) == 128u )
		goto st9;
	goto tr17;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 152u: goto tr10;
		case 155u: goto tr10;
		case 156u: goto tr12;
		case 185u: goto tr10;
		case 186u: goto tr11;
	}
	if ( 153u <= (*p) && (*p) <= 154u )
		goto tr11;
	goto tr0;
	}
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 11: goto tr17;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 12: goto tr17;
	case 8: goto tr0;
	case 13: goto tr17;
	case 9: goto tr0;
	}
	}

	}

#line 454 "tokenizer_utils.rl"

}


#line 503 "tokenizer_utils.rl"



#line 1636 "tokenizer_utils.c"
static const int ProbablyRightLatexQuoteCounter_start = 10;
static const int ProbablyRightLatexQuoteCounter_error = -1;

static const int ProbablyRightLatexQuoteCounter_en_main = 10;


#line 506 "tokenizer_utils.rl"

void NL_latex_quotes_probably_right(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 1653 "tokenizer_utils.c"
	{
	cs = ProbablyRightLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 515 "tokenizer_utils.rl"
    
#line 1663 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 500 "tokenizer_utils.rl"
	{{p = ((te))-1;}{*transform = *p; transform++;}}
	goto st10;
tr4:
#line 488 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	goto st10;
tr8:
#line 489 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                           *transform = '\''; transform++; }}
	goto st10;
tr9:
#line 498 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                                 *transform = '\''; transform++; }}
	goto st10;
tr10:
#line 492 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	goto st10;
tr11:
#line 493 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	goto st10;
tr12:
#line 495 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	goto st10;
tr13:
#line 500 "tokenizer_utils.rl"
	{te = p+1;{*transform = *p; transform++;}}
	goto st10;
tr17:
#line 500 "tokenizer_utils.rl"
	{te = p;p--;{*transform = *p; transform++;}}
	goto st10;
st10:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 1 "NONE"
	{ts = p;}
#line 1716 "tokenizer_utils.c"
	switch( (*p) ) {
		case 34u: goto tr8;
		case 38u: goto tr14;
		case 39u: goto tr4;
		case 194u: goto tr15;
		case 226u: goto tr16;
	}
	goto tr13;
tr14:
#line 1 "NONE"
	{te = p+1;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 1733 "tokenizer_utils.c"
	switch( (*p) ) {
		case 97u: goto st0;
		case 113u: goto st4;
	}
	goto tr17;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	if ( (*p) == 112u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 111u )
		goto st2;
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 115u )
		goto st3;
	goto tr0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 59u )
		goto tr4;
	goto tr0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 117u )
		goto st5;
	goto tr0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 111u )
		goto st6;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 116u )
		goto st7;
	goto tr0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 59u )
		goto tr8;
	goto tr0;
tr15:
#line 1 "NONE"
	{te = p+1;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 1803 "tokenizer_utils.c"
	switch( (*p) ) {
		case 128u: goto st8;
		case 145u: goto tr10;
		case 146u: goto tr11;
		case 147u: goto tr12;
		case 148u: goto tr9;
		case 171u: goto tr12;
		case 187u: goto tr9;
	}
	goto tr17;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 157u )
		goto tr9;
	goto tr0;
tr16:
#line 1 "NONE"
	{te = p+1;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 1829 "tokenizer_utils.c"
	if ( (*p) == 128u )
		goto st9;
	goto tr17;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 152u: goto tr10;
		case 155u: goto tr10;
		case 156u: goto tr12;
		case 185u: goto tr10;
		case 186u: goto tr11;
	}
	if ( 153u <= (*p) && (*p) <= 154u )
		goto tr11;
	goto tr0;
	}
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 11: goto tr17;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	case 3: goto tr0;
	case 4: goto tr0;
	case 5: goto tr0;
	case 6: goto tr0;
	case 7: goto tr0;
	case 12: goto tr17;
	case 8: goto tr0;
	case 13: goto tr17;
	case 9: goto tr0;
	}
	}

	}

#line 516 "tokenizer_utils.rl"

}


#line 539 "tokenizer_utils.rl"



#line 1894 "tokenizer_utils.c"
static const int CopyNoSoftHypen_start = 0;
static const int CopyNoSoftHypen_error = -1;

static const int CopyNoSoftHypen_en_main = 0;


#line 542 "tokenizer_utils.rl"

void NL_copy_no_softhyphen(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs;
    unsigned char *pe = p + buf_length; 

    
#line 1909 "tokenizer_utils.c"
	{
	cs = CopyNoSoftHypen_start;
	}

#line 549 "tokenizer_utils.rl"
    
#line 1916 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 0:
	if ( (*p) == 194u )
		goto st1;
	goto tr0;
tr0:
#line 525 "tokenizer_utils.rl"
	{
        *transform = *(p); transform++;
    }
	goto st2;
tr2:
#line 529 "tokenizer_utils.rl"
	{
        *transform = *(p - 1);
        transform++;       
        *transform = *p;
        transform++;       
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 1945 "tokenizer_utils.c"
	if ( (*p) == 194u )
		goto st1;
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 173u )
		goto st2;
	goto tr2;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 

	_test_eof: {}
	}

#line 550 "tokenizer_utils.rl"

}


#line 564 "tokenizer_utils.rl"



#line 1972 "tokenizer_utils.c"
static const int NormalizeAmps_start = 3;
static const int NormalizeAmps_error = -1;

static const int NormalizeAmps_en_main = 3;


#line 567 "tokenizer_utils.rl"

void NL_normalize_ampersand(unsigned char *p, size_t buf_length,
        unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 1990 "tokenizer_utils.c"
	{
	cs = NormalizeAmps_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 577 "tokenizer_utils.rl"
    
#line 2000 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 561 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	goto st3;
tr3:
#line 560 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '&'; transform++; }}
	goto st3;
tr4:
#line 561 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	goto st3;
tr6:
#line 561 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	goto st3;
st3:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 1 "NONE"
	{ts = p;}
#line 2030 "tokenizer_utils.c"
	if ( (*p) == 38u )
		goto tr5;
	goto tr4;
tr5:
#line 1 "NONE"
	{te = p+1;}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 2042 "tokenizer_utils.c"
	switch( (*p) ) {
		case 65u: goto st0;
		case 97u: goto st0;
	}
	goto tr6;
st0:
	if ( ++p == pe )
		goto _test_eof0;
case 0:
	switch( (*p) ) {
		case 77u: goto st1;
		case 109u: goto st1;
	}
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 80u: goto st2;
		case 112u: goto st2;
	}
	goto tr0;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 59u )
		goto tr3;
	goto tr0;
	}
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 4: goto tr6;
	case 0: goto tr0;
	case 1: goto tr0;
	case 2: goto tr0;
	}
	}

	}

#line 578 "tokenizer_utils.rl"

}


#line 593 "tokenizer_utils.rl"



#line 2102 "tokenizer_utils.c"
static const int CountUnescapedForwardSlashesAsterisks_start = 0;
static const int CountUnescapedForwardSlashesAsterisks_error = -1;

static const int CountUnescapedForwardSlashesAsterisks_en_main = 0;


#line 596 "tokenizer_utils.rl"

size_t NL_get_size_escaped_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t count = 0;

    
#line 2121 "tokenizer_utils.c"
	{
	cs = CountUnescapedForwardSlashesAsterisks_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 607 "tokenizer_utils.rl"
    
#line 2131 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 590 "tokenizer_utils.rl"
	{te = p+1;{ count++; }}
	goto st0;
tr1:
#line 589 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	goto st0;
tr3:
#line 590 "tokenizer_utils.rl"
	{te = p;p--;{ count++; }}
	goto st0;
tr4:
#line 588 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	goto st0;
st0:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 1 "NONE"
	{ts = p;}
#line 2161 "tokenizer_utils.c"
	switch( (*p) ) {
		case 42u: goto tr1;
		case 47u: goto tr1;
		case 92u: goto st1;
	}
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 42u: goto tr4;
		case 47u: goto tr4;
	}
	goto tr3;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: goto tr3;
	}
	}

	}

#line 608 "tokenizer_utils.rl"

    return count;
}


#line 637 "tokenizer_utils.rl"



#line 2201 "tokenizer_utils.c"
static const int EscapedForwardSlashesAsterisks_start = 0;
static const int EscapedForwardSlashesAsterisks_error = -1;

static const int EscapedForwardSlashesAsterisks_en_main = 0;


#line 640 "tokenizer_utils.rl"

void NL_escape_forward_slash_asterisk(unsigned char *p, 
    size_t buf_length, unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 2219 "tokenizer_utils.c"
	{
	cs = EscapedForwardSlashesAsterisks_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 650 "tokenizer_utils.rl"
    
#line 2229 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 634 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *ts; transform++; }}
	goto st0;
tr1:
#line 630 "tokenizer_utils.rl"
	{te = p+1;{ 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        }}
	goto st0;
tr2:
#line 626 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        }}
	goto st0;
tr4:
#line 634 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *ts; transform++; }}
	goto st0;
tr5:
#line 622 "tokenizer_utils.rl"
	{te = p+1;{ 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        }}
	goto st0;
tr6:
#line 618 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        }}
	goto st0;
st0:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 1 "NONE"
	{ts = p;}
#line 2279 "tokenizer_utils.c"
	switch( (*p) ) {
		case 42u: goto tr1;
		case 47u: goto tr2;
		case 92u: goto st1;
	}
	goto tr0;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 42u: goto tr5;
		case 47u: goto tr6;
	}
	goto tr4;
	}
	_test_eof0: cs = 0; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 1: goto tr4;
	}
	}

	}

#line 651 "tokenizer_utils.rl"

}


#line 664 "tokenizer_utils.rl"



#line 2318 "tokenizer_utils.c"
static const int CountSpaces_start = 0;
static const int CountSpaces_error = -1;

static const int CountSpaces_en_main = 0;


#line 667 "tokenizer_utils.rl"

size_t NL_get_size_normalized_spaces(unsigned char *p, 
    size_t buf_length) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;
    size_t count = 0;

    
#line 2337 "tokenizer_utils.c"
	{
	cs = CountSpaces_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 678 "tokenizer_utils.rl"
    
#line 2347 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 661 "tokenizer_utils.rl"
	{te = p+1;{ count++; }}
	goto st0;
tr1:
#line 660 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	goto st0;
st0:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 1 "NONE"
	{ts = p;}
#line 2369 "tokenizer_utils.c"
	if ( (*p) == 32u )
		goto tr1;
	goto tr0;
	}
	_test_eof0: cs = 0; goto _test_eof; 

	_test_eof: {}
	}

#line 679 "tokenizer_utils.rl"

    return count;
}


#line 696 "tokenizer_utils.rl"



#line 2389 "tokenizer_utils.c"
static const int NormalizeSpaces_start = 0;
static const int NormalizeSpaces_error = -1;

static const int NormalizeSpaces_en_main = 0;


#line 699 "tokenizer_utils.rl"

void NL_normalize_spaces(unsigned char *p, 
    size_t buf_length, unsigned char *transform) {

    int cs, act;
    unsigned char *ts, *te = 0;
    unsigned char *pe = p + buf_length; 
    unsigned char *eof = pe;

    
#line 2407 "tokenizer_utils.c"
	{
	cs = NormalizeSpaces_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 709 "tokenizer_utils.rl"
    
#line 2417 "tokenizer_utils.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr0:
#line 693 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *ts; transform++; }}
	goto st0;
tr1:
#line 689 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = 0xC2; transform++;
            *transform = 0xA0; transform++;
        }}
	goto st0;
st0:
#line 1 "NONE"
	{ts = 0;}
	if ( ++p == pe )
		goto _test_eof0;
case 0:
#line 1 "NONE"
	{ts = p;}
#line 2442 "tokenizer_utils.c"
	if ( (*p) == 32u )
		goto tr1;
	goto tr0;
	}
	_test_eof0: cs = 0; goto _test_eof; 

	_test_eof: {}
	}

#line 710 "tokenizer_utils.rl"

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
