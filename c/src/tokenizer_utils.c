
#line 1 "tokenizer_utils.rl"
#include "tokenizer_utils.h"


#line 77 "tokenizer_utils.rl"



#line 11 "tokenizer_utils.c"
static const char _NonUnicodeQuoteCounter_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6
};

static const char _NonUnicodeQuoteCounter_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	11, 13
};

static const unsigned char _NonUnicodeQuoteCounter_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 34u, 
	38u, 39u, 194u, 97u, 113u, 145u, 148u, 0
};

static const char _NonUnicodeQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 4, 
	2, 0
};

static const char _NonUnicodeQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1
};

static const char _NonUnicodeQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	19, 22
};

static const char _NonUnicodeQuoteCounter_trans_targs[] = {
	1, 7, 2, 7, 3, 7, 7, 7, 
	5, 7, 6, 7, 3, 7, 7, 8, 
	7, 9, 7, 0, 4, 7, 7, 7, 
	7, 7, 7, 7, 7, 7, 7, 7, 
	7, 0
};

static const char _NonUnicodeQuoteCounter_trans_actions[] = {
	0, 13, 0, 13, 0, 13, 7, 13, 
	0, 13, 0, 13, 0, 13, 7, 5, 
	7, 0, 9, 0, 0, 11, 7, 11, 
	13, 13, 13, 13, 13, 13, 13, 11, 
	11, 0
};

static const char _NonUnicodeQuoteCounter_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0
};

static const char _NonUnicodeQuoteCounter_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 3, 
	0, 0
};

static const char _NonUnicodeQuoteCounter_eof_trans[] = {
	31, 31, 31, 31, 31, 31, 31, 0, 
	33, 33
};

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

    
#line 89 "tokenizer_utils.c"
	{
	cs = NonUnicodeQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 89 "tokenizer_utils.rl"
    
#line 99 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _NonUnicodeQuoteCounter_actions + _NonUnicodeQuoteCounter_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 118 "tokenizer_utils.c"
		}
	}

	_keys = _NonUnicodeQuoteCounter_trans_keys + _NonUnicodeQuoteCounter_key_offsets[cs];
	_trans = _NonUnicodeQuoteCounter_index_offsets[cs];

	_klen = _NonUnicodeQuoteCounter_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _NonUnicodeQuoteCounter_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _NonUnicodeQuoteCounter_trans_targs[_trans];

	if ( _NonUnicodeQuoteCounter_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _NonUnicodeQuoteCounter_actions + _NonUnicodeQuoteCounter_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 73 "tokenizer_utils.rl"
	{te = p+1;{size += 3;}}
	break;
	case 4:
#line 74 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	break;
	case 5:
#line 74 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	break;
	case 6:
#line 74 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	break;
#line 203 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _NonUnicodeQuoteCounter_actions + _NonUnicodeQuoteCounter_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 216 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _NonUnicodeQuoteCounter_eof_trans[cs] > 0 ) {
		_trans = _NonUnicodeQuoteCounter_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 90 "tokenizer_utils.rl"

    return size;
}


#line 153 "tokenizer_utils.rl"



#line 243 "tokenizer_utils.c"
static const char _ProbablyLeftUnicodeQuoteTransformer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11
};

static const char _ProbablyLeftUnicodeQuoteTransformer_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 12, 14
};

static const unsigned char _ProbablyLeftUnicodeQuoteTransformer_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	34u, 38u, 39u, 194u, 97u, 113u, 145u, 146u, 
	147u, 148u, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	4, 2, 4
};

static const char _ProbablyLeftUnicodeQuoteTransformer_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 21, 24
};

static const char _ProbablyLeftUnicodeQuoteTransformer_trans_targs[] = {
	1, 8, 2, 8, 3, 8, 8, 8, 
	5, 8, 6, 8, 7, 8, 8, 8, 
	8, 9, 8, 10, 8, 0, 4, 8, 
	8, 8, 8, 8, 8, 8, 8, 8, 
	8, 8, 8, 8, 8, 8, 8, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_trans_actions[] = {
	0, 23, 0, 23, 0, 23, 7, 23, 
	0, 23, 0, 23, 0, 23, 9, 23, 
	9, 5, 7, 0, 19, 0, 0, 21, 
	11, 15, 13, 17, 21, 23, 23, 23, 
	23, 23, 23, 23, 23, 21, 21, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	3, 0, 0
};

static const char _ProbablyLeftUnicodeQuoteTransformer_eof_trans[] = {
	37, 37, 37, 37, 37, 37, 37, 37, 
	0, 39, 39
};

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

    
#line 324 "tokenizer_utils.c"
	{
	cs = ProbablyLeftUnicodeQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 165 "tokenizer_utils.rl"
    
#line 334 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _ProbablyLeftUnicodeQuoteTransformer_actions + _ProbablyLeftUnicodeQuoteTransformer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 353 "tokenizer_utils.c"
		}
	}

	_keys = _ProbablyLeftUnicodeQuoteTransformer_trans_keys + _ProbablyLeftUnicodeQuoteTransformer_key_offsets[cs];
	_trans = _ProbablyLeftUnicodeQuoteTransformer_index_offsets[cs];

	_klen = _ProbablyLeftUnicodeQuoteTransformer_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _ProbablyLeftUnicodeQuoteTransformer_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _ProbablyLeftUnicodeQuoteTransformer_trans_targs[_trans];

	if ( _ProbablyLeftUnicodeQuoteTransformer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ProbablyLeftUnicodeQuoteTransformer_actions + _ProbablyLeftUnicodeQuoteTransformer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 107 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	break;
	case 4:
#line 125 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	break;
	case 5:
#line 107 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	break;
	case 6:
#line 125 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	break;
	case 7:
#line 116 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	break;
	case 8:
#line 134 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	break;
	case 9:
#line 150 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	break;
	case 10:
#line 150 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	break;
	case 11:
#line 150 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	break;
#line 500 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _ProbablyLeftUnicodeQuoteTransformer_actions + _ProbablyLeftUnicodeQuoteTransformer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 513 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _ProbablyLeftUnicodeQuoteTransformer_eof_trans[cs] > 0 ) {
		_trans = _ProbablyLeftUnicodeQuoteTransformer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 166 "tokenizer_utils.rl"
}


#line 227 "tokenizer_utils.rl"



#line 538 "tokenizer_utils.c"
static const char _ProbablyRightUnicodeQuoteTransformer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11
};

static const char _ProbablyRightUnicodeQuoteTransformer_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 12, 14
};

static const unsigned char _ProbablyRightUnicodeQuoteTransformer_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	34u, 38u, 39u, 194u, 97u, 113u, 145u, 146u, 
	147u, 148u, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	4, 2, 4
};

static const char _ProbablyRightUnicodeQuoteTransformer_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 21, 24
};

static const char _ProbablyRightUnicodeQuoteTransformer_trans_targs[] = {
	1, 8, 2, 8, 3, 8, 8, 8, 
	5, 8, 6, 8, 7, 8, 8, 8, 
	8, 9, 8, 10, 8, 0, 4, 8, 
	8, 8, 8, 8, 8, 8, 8, 8, 
	8, 8, 8, 8, 8, 8, 8, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_trans_actions[] = {
	0, 23, 0, 23, 0, 23, 7, 23, 
	0, 23, 0, 23, 0, 23, 9, 23, 
	9, 5, 7, 0, 19, 0, 0, 21, 
	11, 15, 13, 17, 21, 23, 23, 23, 
	23, 23, 23, 23, 23, 21, 21, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	3, 0, 0
};

static const char _ProbablyRightUnicodeQuoteTransformer_eof_trans[] = {
	37, 37, 37, 37, 37, 37, 37, 37, 
	0, 39, 39
};

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

    
#line 619 "tokenizer_utils.c"
	{
	cs = ProbablyRightUnicodeQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 239 "tokenizer_utils.rl"
    
#line 629 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _ProbablyRightUnicodeQuoteTransformer_actions + _ProbablyRightUnicodeQuoteTransformer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 648 "tokenizer_utils.c"
		}
	}

	_keys = _ProbablyRightUnicodeQuoteTransformer_trans_keys + _ProbablyRightUnicodeQuoteTransformer_key_offsets[cs];
	_trans = _ProbablyRightUnicodeQuoteTransformer_index_offsets[cs];

	_klen = _ProbablyRightUnicodeQuoteTransformer_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _ProbablyRightUnicodeQuoteTransformer_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _ProbablyRightUnicodeQuoteTransformer_trans_targs[_trans];

	if ( _ProbablyRightUnicodeQuoteTransformer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ProbablyRightUnicodeQuoteTransformer_actions + _ProbablyRightUnicodeQuoteTransformer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 190 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	break;
	case 4:
#line 208 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	break;
	case 5:
#line 181 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x98; 
        transform++; 
    }}
	break;
	case 6:
#line 199 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9C; 
        transform++; 
    }}
	break;
	case 7:
#line 190 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x99; 
        transform++; 
    }}
	break;
	case 8:
#line 208 "tokenizer_utils.rl"
	{te = p+1;{
        *transform = 0xE2; 
        transform++; 
        *transform = 0x80; 
        transform++; 
        *transform = 0x9D; 
        transform++; 
    }}
	break;
	case 9:
#line 224 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	break;
	case 10:
#line 224 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	break;
	case 11:
#line 224 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	break;
#line 795 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _ProbablyRightUnicodeQuoteTransformer_actions + _ProbablyRightUnicodeQuoteTransformer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 808 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _ProbablyRightUnicodeQuoteTransformer_eof_trans[cs] > 0 ) {
		_trans = _ProbablyRightUnicodeQuoteTransformer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 240 "tokenizer_utils.rl"

}


#line 276 "tokenizer_utils.rl"



#line 834 "tokenizer_utils.c"
static const char _NonAsciiQuoteCounter_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6
};

static const char _NonAsciiQuoteCounter_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	9, 13, 16, 18, 23
};

static const unsigned char _NonAsciiQuoteCounter_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 157u, 
	158u, 152u, 156u, 185u, 186u, 38u, 194u, 226u, 
	97u, 113u, 128u, 171u, 187u, 145u, 148u, 128u, 
	0
};

static const char _NonAsciiQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 3, 2, 3, 1
};

static const char _NonAsciiQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 1, 
	2, 0, 0, 1, 0
};

static const char _NonAsciiQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 19, 23, 26, 31
};

static const char _NonAsciiQuoteCounter_indicies[] = {
	1, 0, 2, 0, 3, 0, 4, 0, 
	5, 0, 6, 0, 3, 0, 4, 0, 
	4, 4, 0, 8, 9, 10, 7, 12, 
	13, 11, 14, 4, 4, 4, 11, 15, 
	11, 0
};

static const char _NonAsciiQuoteCounter_trans_targs[] = {
	9, 1, 2, 3, 9, 5, 6, 9, 
	10, 11, 12, 9, 0, 4, 7, 8
};

static const char _NonAsciiQuoteCounter_trans_actions[] = {
	13, 0, 0, 0, 7, 0, 0, 9, 
	5, 5, 5, 11, 0, 0, 0, 0
};

static const char _NonAsciiQuoteCounter_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0
};

static const char _NonAsciiQuoteCounter_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 3, 0, 0, 0
};

static const char _NonAsciiQuoteCounter_eof_trans[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 0, 12, 12, 12
};

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

    
#line 916 "tokenizer_utils.c"
	{
	cs = NonAsciiQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 288 "tokenizer_utils.rl"
    
#line 926 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _NonAsciiQuoteCounter_actions + _NonAsciiQuoteCounter_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 945 "tokenizer_utils.c"
		}
	}

	_keys = _NonAsciiQuoteCounter_trans_keys + _NonAsciiQuoteCounter_key_offsets[cs];
	_trans = _NonAsciiQuoteCounter_index_offsets[cs];

	_klen = _NonAsciiQuoteCounter_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _NonAsciiQuoteCounter_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _NonAsciiQuoteCounter_indicies[_trans];
_eof_trans:
	cs = _NonAsciiQuoteCounter_trans_targs[_trans];

	if ( _NonAsciiQuoteCounter_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _NonAsciiQuoteCounter_actions + _NonAsciiQuoteCounter_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 272 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	break;
	case 4:
#line 273 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	break;
	case 5:
#line 273 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	break;
	case 6:
#line 273 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	break;
#line 1031 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _NonAsciiQuoteCounter_actions + _NonAsciiQuoteCounter_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 1044 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _NonAsciiQuoteCounter_eof_trans[cs] > 0 ) {
		_trans = _NonAsciiQuoteCounter_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 289 "tokenizer_utils.rl"

    return size;
}


#line 325 "tokenizer_utils.rl"



#line 1071 "tokenizer_utils.c"
static const char _AsciiQuoteTransformer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7
};

static const char _AsciiQuoteTransformer_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 10, 15, 18, 20, 27
};

static const unsigned char _AsciiQuoteTransformer_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	157u, 158u, 156u, 152u, 155u, 185u, 186u, 38u, 
	194u, 226u, 97u, 113u, 128u, 171u, 187u, 145u, 
	146u, 147u, 148u, 128u, 0
};

static const char _AsciiQuoteTransformer_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	0, 1, 3, 2, 3, 1
};

static const char _AsciiQuoteTransformer_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 2, 0, 0, 2, 0
};

static const char _AsciiQuoteTransformer_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 18, 22, 26, 29, 35
};

static const char _AsciiQuoteTransformer_indicies[] = {
	1, 0, 2, 0, 3, 0, 4, 0, 
	5, 0, 6, 0, 7, 0, 8, 0, 
	8, 0, 8, 4, 4, 0, 10, 11, 
	12, 9, 14, 15, 13, 16, 8, 8, 
	4, 8, 13, 17, 13, 0
};

static const char _AsciiQuoteTransformer_trans_targs[] = {
	10, 1, 2, 3, 10, 5, 6, 7, 
	10, 10, 11, 12, 13, 10, 0, 4, 
	8, 9
};

static const char _AsciiQuoteTransformer_trans_actions[] = {
	15, 0, 0, 0, 7, 0, 0, 0, 
	9, 11, 5, 5, 5, 13, 0, 0, 
	0, 0
};

static const char _AsciiQuoteTransformer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 0, 0
};

static const char _AsciiQuoteTransformer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 3, 0, 0, 0
};

static const char _AsciiQuoteTransformer_eof_trans[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 14, 14, 14
};

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

    
#line 1156 "tokenizer_utils.c"
	{
	cs = AsciiQuoteTransformer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 337 "tokenizer_utils.rl"
    
#line 1166 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _AsciiQuoteTransformer_actions + _AsciiQuoteTransformer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 1185 "tokenizer_utils.c"
		}
	}

	_keys = _AsciiQuoteTransformer_trans_keys + _AsciiQuoteTransformer_key_offsets[cs];
	_trans = _AsciiQuoteTransformer_index_offsets[cs];

	_klen = _AsciiQuoteTransformer_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _AsciiQuoteTransformer_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _AsciiQuoteTransformer_indicies[_trans];
_eof_trans:
	cs = _AsciiQuoteTransformer_trans_targs[_trans];

	if ( _AsciiQuoteTransformer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _AsciiQuoteTransformer_actions + _AsciiQuoteTransformer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 320 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	break;
	case 4:
#line 321 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '"'; transform++; }}
	break;
	case 5:
#line 322 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	break;
	case 6:
#line 322 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	break;
	case 7:
#line 322 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	break;
#line 1275 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _AsciiQuoteTransformer_actions + _AsciiQuoteTransformer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 1288 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _AsciiQuoteTransformer_eof_trans[cs] > 0 ) {
		_trans = _AsciiQuoteTransformer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 338 "tokenizer_utils.rl"

    return;
}


#line 377 "tokenizer_utils.rl"



#line 1315 "tokenizer_utils.c"
static const char _NonLatexQuoteCounter_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7
};

static const char _NonLatexQuoteCounter_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 9, 14, 19, 21, 28
};

static const unsigned char _NonLatexQuoteCounter_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	157u, 156u, 152u, 155u, 185u, 186u, 34u, 38u, 
	39u, 194u, 226u, 97u, 113u, 128u, 171u, 187u, 
	145u, 146u, 147u, 148u, 128u, 0
};

static const char _NonLatexQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 5, 2, 3, 1
};

static const char _NonLatexQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 2, 0, 0, 2, 0
};

static const char _NonLatexQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 18, 22, 28, 31, 37
};

static const char _NonLatexQuoteCounter_indicies[] = {
	1, 0, 2, 0, 3, 0, 4, 0, 
	5, 0, 6, 0, 7, 0, 8, 0, 
	8, 0, 8, 4, 4, 0, 8, 10, 
	4, 11, 12, 9, 14, 15, 13, 16, 
	8, 8, 4, 8, 13, 17, 13, 0
};

static const char _NonLatexQuoteCounter_trans_targs[] = {
	10, 1, 2, 3, 10, 5, 6, 7, 
	10, 10, 11, 12, 13, 10, 0, 4, 
	8, 9
};

static const char _NonLatexQuoteCounter_trans_actions[] = {
	15, 0, 0, 0, 7, 0, 0, 0, 
	9, 11, 5, 5, 5, 13, 0, 0, 
	0, 0
};

static const char _NonLatexQuoteCounter_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 0, 0
};

static const char _NonLatexQuoteCounter_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 3, 0, 0, 0
};

static const char _NonLatexQuoteCounter_eof_trans[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 14, 14, 14
};

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

    
#line 1400 "tokenizer_utils.c"
	{
	cs = NonLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 389 "tokenizer_utils.rl"
    
#line 1410 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _NonLatexQuoteCounter_actions + _NonLatexQuoteCounter_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 1429 "tokenizer_utils.c"
		}
	}

	_keys = _NonLatexQuoteCounter_trans_keys + _NonLatexQuoteCounter_key_offsets[cs];
	_trans = _NonLatexQuoteCounter_index_offsets[cs];

	_klen = _NonLatexQuoteCounter_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _NonLatexQuoteCounter_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _NonLatexQuoteCounter_indicies[_trans];
_eof_trans:
	cs = _NonLatexQuoteCounter_trans_targs[_trans];

	if ( _NonLatexQuoteCounter_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _NonLatexQuoteCounter_actions + _NonLatexQuoteCounter_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 372 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	break;
	case 4:
#line 373 "tokenizer_utils.rl"
	{te = p+1;{size += 2;}}
	break;
	case 5:
#line 374 "tokenizer_utils.rl"
	{te = p+1;{size++;}}
	break;
	case 6:
#line 374 "tokenizer_utils.rl"
	{te = p;p--;{size++;}}
	break;
	case 7:
#line 374 "tokenizer_utils.rl"
	{{p = ((te))-1;}{size++;}}
	break;
#line 1519 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _NonLatexQuoteCounter_actions + _NonLatexQuoteCounter_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 1532 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _NonLatexQuoteCounter_eof_trans[cs] > 0 ) {
		_trans = _NonLatexQuoteCounter_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 390 "tokenizer_utils.rl"

    return size;
}


#line 441 "tokenizer_utils.rl"



#line 1559 "tokenizer_utils.c"
static const char _ProbablyLeftLatexQuoteCounter_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11
};

static const char _ProbablyLeftLatexQuoteCounter_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 9, 16, 21, 23, 30
};

static const unsigned char _ProbablyLeftLatexQuoteCounter_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	157u, 152u, 155u, 156u, 185u, 186u, 153u, 154u, 
	34u, 38u, 39u, 194u, 226u, 97u, 113u, 128u, 
	145u, 146u, 147u, 148u, 171u, 187u, 128u, 0
};

static const char _ProbablyLeftLatexQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 5, 5, 2, 7, 1
};

static const char _ProbablyLeftLatexQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0, 0
};

static const char _ProbablyLeftLatexQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 18, 25, 31, 34, 42
};

static const char _ProbablyLeftLatexQuoteCounter_trans_targs[] = {
	1, 10, 2, 10, 3, 10, 10, 10, 
	5, 10, 6, 10, 7, 10, 10, 10, 
	10, 10, 10, 10, 10, 10, 10, 10, 
	10, 10, 11, 10, 12, 13, 10, 0, 
	4, 10, 8, 10, 10, 10, 10, 10, 
	10, 10, 9, 10, 10, 10, 10, 10, 
	10, 10, 10, 10, 10, 10, 10, 10, 
	10, 0
};

static const char _ProbablyLeftLatexQuoteCounter_trans_actions[] = {
	0, 23, 0, 23, 0, 23, 7, 23, 
	0, 23, 0, 23, 0, 23, 9, 23, 
	17, 23, 11, 11, 15, 11, 13, 13, 
	23, 9, 5, 7, 5, 5, 19, 0, 
	0, 21, 0, 11, 13, 15, 17, 15, 
	17, 21, 0, 21, 23, 23, 23, 23, 
	23, 23, 23, 23, 23, 23, 21, 21, 
	21, 0
};

static const char _ProbablyLeftLatexQuoteCounter_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 0, 0
};

static const char _ProbablyLeftLatexQuoteCounter_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 3, 0, 0, 0
};

static const char _ProbablyLeftLatexQuoteCounter_eof_trans[] = {
	54, 54, 54, 54, 54, 54, 54, 54, 
	54, 54, 0, 57, 57, 57
};

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

    
#line 1647 "tokenizer_utils.c"
	{
	cs = ProbablyLeftLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 453 "tokenizer_utils.rl"
    
#line 1657 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _ProbablyLeftLatexQuoteCounter_actions + _ProbablyLeftLatexQuoteCounter_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 1676 "tokenizer_utils.c"
		}
	}

	_keys = _ProbablyLeftLatexQuoteCounter_trans_keys + _ProbablyLeftLatexQuoteCounter_key_offsets[cs];
	_trans = _ProbablyLeftLatexQuoteCounter_index_offsets[cs];

	_klen = _ProbablyLeftLatexQuoteCounter_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _ProbablyLeftLatexQuoteCounter_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _ProbablyLeftLatexQuoteCounter_trans_targs[_trans];

	if ( _ProbablyLeftLatexQuoteCounter_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ProbablyLeftLatexQuoteCounter_actions + _ProbablyLeftLatexQuoteCounter_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 426 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	break;
	case 4:
#line 427 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	break;
	case 5:
#line 430 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	break;
	case 6:
#line 431 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	break;
	case 7:
#line 433 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	break;
	case 8:
#line 436 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                                 *transform = '\''; transform++; }}
	break;
	case 9:
#line 438 "tokenizer_utils.rl"
	{te = p+1;{*transform = *p; transform++;}}
	break;
	case 10:
#line 438 "tokenizer_utils.rl"
	{te = p;p--;{*transform = *p; transform++;}}
	break;
	case 11:
#line 438 "tokenizer_utils.rl"
	{{p = ((te))-1;}{*transform = *p; transform++;}}
	break;
#line 1784 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _ProbablyLeftLatexQuoteCounter_actions + _ProbablyLeftLatexQuoteCounter_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 1797 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _ProbablyLeftLatexQuoteCounter_eof_trans[cs] > 0 ) {
		_trans = _ProbablyLeftLatexQuoteCounter_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 454 "tokenizer_utils.rl"

}


#line 503 "tokenizer_utils.rl"



#line 1823 "tokenizer_utils.c"
static const char _ProbablyRightLatexQuoteCounter_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11
};

static const char _ProbablyRightLatexQuoteCounter_key_offsets[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 
	8, 9, 16, 21, 23, 30
};

static const unsigned char _ProbablyRightLatexQuoteCounter_trans_keys[] = {
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 59u, 
	157u, 152u, 155u, 156u, 185u, 186u, 153u, 154u, 
	34u, 38u, 39u, 194u, 226u, 97u, 113u, 128u, 
	145u, 146u, 147u, 148u, 171u, 187u, 128u, 0
};

static const char _ProbablyRightLatexQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 5, 5, 2, 7, 1
};

static const char _ProbablyRightLatexQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0, 0
};

static const char _ProbablyRightLatexQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	16, 18, 25, 31, 34, 42
};

static const char _ProbablyRightLatexQuoteCounter_trans_targs[] = {
	1, 10, 2, 10, 3, 10, 10, 10, 
	5, 10, 6, 10, 7, 10, 10, 10, 
	10, 10, 10, 10, 10, 10, 10, 10, 
	10, 10, 11, 10, 12, 13, 10, 0, 
	4, 10, 8, 10, 10, 10, 10, 10, 
	10, 10, 9, 10, 10, 10, 10, 10, 
	10, 10, 10, 10, 10, 10, 10, 10, 
	10, 0
};

static const char _ProbablyRightLatexQuoteCounter_trans_actions[] = {
	0, 23, 0, 23, 0, 23, 7, 23, 
	0, 23, 0, 23, 0, 23, 9, 23, 
	17, 23, 11, 11, 15, 11, 13, 13, 
	23, 9, 5, 7, 5, 5, 19, 0, 
	0, 21, 0, 11, 13, 15, 17, 15, 
	17, 21, 0, 21, 23, 23, 23, 23, 
	23, 23, 23, 23, 23, 23, 21, 21, 
	21, 0
};

static const char _ProbablyRightLatexQuoteCounter_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 0, 0
};

static const char _ProbablyRightLatexQuoteCounter_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 3, 0, 0, 0
};

static const char _ProbablyRightLatexQuoteCounter_eof_trans[] = {
	54, 54, 54, 54, 54, 54, 54, 54, 
	54, 54, 0, 57, 57, 57
};

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

    
#line 1911 "tokenizer_utils.c"
	{
	cs = ProbablyRightLatexQuoteCounter_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 515 "tokenizer_utils.rl"
    
#line 1921 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _ProbablyRightLatexQuoteCounter_actions + _ProbablyRightLatexQuoteCounter_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 1940 "tokenizer_utils.c"
		}
	}

	_keys = _ProbablyRightLatexQuoteCounter_trans_keys + _ProbablyRightLatexQuoteCounter_key_offsets[cs];
	_trans = _ProbablyRightLatexQuoteCounter_index_offsets[cs];

	_klen = _ProbablyRightLatexQuoteCounter_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _ProbablyRightLatexQuoteCounter_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _ProbablyRightLatexQuoteCounter_trans_targs[_trans];

	if ( _ProbablyRightLatexQuoteCounter_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ProbablyRightLatexQuoteCounter_actions + _ProbablyRightLatexQuoteCounter_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 488 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	break;
	case 4:
#line 489 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                           *transform = '\''; transform++; }}
	break;
	case 5:
#line 492 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; }}
	break;
	case 6:
#line 493 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; }}
	break;
	case 7:
#line 495 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '`'; transform++; 
                           *transform = '`'; transform++; }}
	break;
	case 8:
#line 498 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '\''; transform++; 
                                 *transform = '\''; transform++; }}
	break;
	case 9:
#line 500 "tokenizer_utils.rl"
	{te = p+1;{*transform = *p; transform++;}}
	break;
	case 10:
#line 500 "tokenizer_utils.rl"
	{te = p;p--;{*transform = *p; transform++;}}
	break;
	case 11:
#line 500 "tokenizer_utils.rl"
	{{p = ((te))-1;}{*transform = *p; transform++;}}
	break;
#line 2048 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _ProbablyRightLatexQuoteCounter_actions + _ProbablyRightLatexQuoteCounter_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 2061 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _ProbablyRightLatexQuoteCounter_eof_trans[cs] > 0 ) {
		_trans = _ProbablyRightLatexQuoteCounter_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 516 "tokenizer_utils.rl"

}


#line 539 "tokenizer_utils.rl"



#line 2087 "tokenizer_utils.c"
static const char _CopyNoSoftHypen_actions[] = {
	0, 1, 0, 1, 1
};

static const char _CopyNoSoftHypen_key_offsets[] = {
	0, 1, 2
};

static const unsigned char _CopyNoSoftHypen_trans_keys[] = {
	194u, 173u, 194u, 0
};

static const char _CopyNoSoftHypen_single_lengths[] = {
	1, 1, 1
};

static const char _CopyNoSoftHypen_range_lengths[] = {
	0, 0, 0
};

static const char _CopyNoSoftHypen_index_offsets[] = {
	0, 2, 4
};

static const char _CopyNoSoftHypen_trans_targs[] = {
	1, 2, 2, 2, 1, 2, 0
};

static const char _CopyNoSoftHypen_trans_actions[] = {
	0, 1, 0, 3, 0, 1, 0
};

static const int CopyNoSoftHypen_start = 0;
static const int CopyNoSoftHypen_error = -1;

static const int CopyNoSoftHypen_en_main = 0;


#line 542 "tokenizer_utils.rl"

void NL_copy_no_softhyphen(unsigned char *p, size_t buf_length,
        unsigned char *transform) {
    int cs;
    unsigned char *pe = p + buf_length; 

    
#line 2134 "tokenizer_utils.c"
	{
	cs = CopyNoSoftHypen_start;
	}

#line 549 "tokenizer_utils.rl"
    
#line 2141 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_keys = _CopyNoSoftHypen_trans_keys + _CopyNoSoftHypen_key_offsets[cs];
	_trans = _CopyNoSoftHypen_index_offsets[cs];

	_klen = _CopyNoSoftHypen_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _CopyNoSoftHypen_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _CopyNoSoftHypen_trans_targs[_trans];

	if ( _CopyNoSoftHypen_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _CopyNoSoftHypen_actions + _CopyNoSoftHypen_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 525 "tokenizer_utils.rl"
	{
        *transform = *(p); transform++;
    }
	break;
	case 1:
#line 529 "tokenizer_utils.rl"
	{
        *transform = *(p - 1);
        transform++;       
        *transform = *p;
        transform++;       
    }
	break;
#line 2227 "tokenizer_utils.c"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 550 "tokenizer_utils.rl"

}


#line 564 "tokenizer_utils.rl"



#line 2246 "tokenizer_utils.c"
static const char _NormalizeAmps_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6
};

static const char _NormalizeAmps_key_offsets[] = {
	0, 2, 4, 5, 6
};

static const unsigned char _NormalizeAmps_trans_keys[] = {
	77u, 109u, 80u, 112u, 59u, 38u, 65u, 97u, 
	0
};

static const char _NormalizeAmps_single_lengths[] = {
	2, 2, 1, 1, 2
};

static const char _NormalizeAmps_range_lengths[] = {
	0, 0, 0, 0, 0
};

static const char _NormalizeAmps_index_offsets[] = {
	0, 3, 6, 8, 10
};

static const char _NormalizeAmps_trans_targs[] = {
	1, 1, 3, 2, 2, 3, 3, 3, 
	4, 3, 0, 0, 3, 3, 3, 3, 
	3, 0
};

static const char _NormalizeAmps_trans_actions[] = {
	0, 0, 13, 0, 0, 13, 7, 13, 
	5, 9, 0, 0, 11, 13, 13, 13, 
	11, 0
};

static const char _NormalizeAmps_to_state_actions[] = {
	0, 0, 0, 1, 0
};

static const char _NormalizeAmps_from_state_actions[] = {
	0, 0, 0, 3, 0
};

static const char _NormalizeAmps_eof_trans[] = {
	16, 16, 16, 0, 17
};

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

    
#line 2314 "tokenizer_utils.c"
	{
	cs = NormalizeAmps_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 577 "tokenizer_utils.rl"
    
#line 2324 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _NormalizeAmps_actions + _NormalizeAmps_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 2343 "tokenizer_utils.c"
		}
	}

	_keys = _NormalizeAmps_trans_keys + _NormalizeAmps_key_offsets[cs];
	_trans = _NormalizeAmps_index_offsets[cs];

	_klen = _NormalizeAmps_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _NormalizeAmps_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _NormalizeAmps_trans_targs[_trans];

	if ( _NormalizeAmps_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _NormalizeAmps_actions + _NormalizeAmps_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 560 "tokenizer_utils.rl"
	{te = p+1;{ *transform = '&'; transform++; }}
	break;
	case 4:
#line 561 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *p; transform++; }}
	break;
	case 5:
#line 561 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *p; transform++; }}
	break;
	case 6:
#line 561 "tokenizer_utils.rl"
	{{p = ((te))-1;}{ *transform = *p; transform++; }}
	break;
#line 2428 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _NormalizeAmps_actions + _NormalizeAmps_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 2441 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _NormalizeAmps_eof_trans[cs] > 0 ) {
		_trans = _NormalizeAmps_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 578 "tokenizer_utils.rl"

}


#line 593 "tokenizer_utils.rl"



#line 2467 "tokenizer_utils.c"
static const char _CountUnescapedForwardSlashesAsterisks_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5
};

static const char _CountUnescapedForwardSlashesAsterisks_key_offsets[] = {
	0, 3
};

static const unsigned char _CountUnescapedForwardSlashesAsterisks_trans_keys[] = {
	42u, 47u, 92u, 42u, 47u, 0
};

static const char _CountUnescapedForwardSlashesAsterisks_single_lengths[] = {
	3, 2
};

static const char _CountUnescapedForwardSlashesAsterisks_range_lengths[] = {
	0, 0
};

static const char _CountUnescapedForwardSlashesAsterisks_index_offsets[] = {
	0, 4
};

static const char _CountUnescapedForwardSlashesAsterisks_trans_targs[] = {
	0, 0, 1, 0, 0, 0, 0, 0, 
	0
};

static const char _CountUnescapedForwardSlashesAsterisks_trans_actions[] = {
	7, 7, 0, 9, 5, 5, 11, 11, 
	0
};

static const char _CountUnescapedForwardSlashesAsterisks_to_state_actions[] = {
	1, 0
};

static const char _CountUnescapedForwardSlashesAsterisks_from_state_actions[] = {
	3, 0
};

static const char _CountUnescapedForwardSlashesAsterisks_eof_trans[] = {
	0, 8
};

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

    
#line 2533 "tokenizer_utils.c"
	{
	cs = CountUnescapedForwardSlashesAsterisks_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 607 "tokenizer_utils.rl"
    
#line 2543 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _CountUnescapedForwardSlashesAsterisks_actions + _CountUnescapedForwardSlashesAsterisks_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 2562 "tokenizer_utils.c"
		}
	}

	_keys = _CountUnescapedForwardSlashesAsterisks_trans_keys + _CountUnescapedForwardSlashesAsterisks_key_offsets[cs];
	_trans = _CountUnescapedForwardSlashesAsterisks_index_offsets[cs];

	_klen = _CountUnescapedForwardSlashesAsterisks_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _CountUnescapedForwardSlashesAsterisks_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _CountUnescapedForwardSlashesAsterisks_trans_targs[_trans];

	if ( _CountUnescapedForwardSlashesAsterisks_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _CountUnescapedForwardSlashesAsterisks_actions + _CountUnescapedForwardSlashesAsterisks_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 588 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	break;
	case 3:
#line 589 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	break;
	case 4:
#line 590 "tokenizer_utils.rl"
	{te = p+1;{ count++; }}
	break;
	case 5:
#line 590 "tokenizer_utils.rl"
	{te = p;p--;{ count++; }}
	break;
#line 2643 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _CountUnescapedForwardSlashesAsterisks_actions + _CountUnescapedForwardSlashesAsterisks_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 2656 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _CountUnescapedForwardSlashesAsterisks_eof_trans[cs] > 0 ) {
		_trans = _CountUnescapedForwardSlashesAsterisks_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 608 "tokenizer_utils.rl"

    return count;
}


#line 637 "tokenizer_utils.rl"



#line 2683 "tokenizer_utils.c"
static const char _EscapedForwardSlashesAsterisks_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7
};

static const char _EscapedForwardSlashesAsterisks_key_offsets[] = {
	0, 3
};

static const unsigned char _EscapedForwardSlashesAsterisks_trans_keys[] = {
	42u, 47u, 92u, 42u, 47u, 0
};

static const char _EscapedForwardSlashesAsterisks_single_lengths[] = {
	3, 2
};

static const char _EscapedForwardSlashesAsterisks_range_lengths[] = {
	0, 0
};

static const char _EscapedForwardSlashesAsterisks_index_offsets[] = {
	0, 4
};

static const char _EscapedForwardSlashesAsterisks_trans_targs[] = {
	0, 0, 1, 0, 0, 0, 0, 0, 
	0
};

static const char _EscapedForwardSlashesAsterisks_trans_actions[] = {
	11, 9, 0, 13, 7, 5, 15, 15, 
	0
};

static const char _EscapedForwardSlashesAsterisks_to_state_actions[] = {
	1, 0
};

static const char _EscapedForwardSlashesAsterisks_from_state_actions[] = {
	3, 0
};

static const char _EscapedForwardSlashesAsterisks_eof_trans[] = {
	0, 8
};

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

    
#line 2749 "tokenizer_utils.c"
	{
	cs = EscapedForwardSlashesAsterisks_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 650 "tokenizer_utils.rl"
    
#line 2759 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _EscapedForwardSlashesAsterisks_actions + _EscapedForwardSlashesAsterisks_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 2778 "tokenizer_utils.c"
		}
	}

	_keys = _EscapedForwardSlashesAsterisks_trans_keys + _EscapedForwardSlashesAsterisks_key_offsets[cs];
	_trans = _EscapedForwardSlashesAsterisks_index_offsets[cs];

	_klen = _EscapedForwardSlashesAsterisks_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _EscapedForwardSlashesAsterisks_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _EscapedForwardSlashesAsterisks_trans_targs[_trans];

	if ( _EscapedForwardSlashesAsterisks_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _EscapedForwardSlashesAsterisks_actions + _EscapedForwardSlashesAsterisks_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 618 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        }}
	break;
	case 3:
#line 622 "tokenizer_utils.rl"
	{te = p+1;{ 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        }}
	break;
	case 4:
#line 626 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = '\\'; transform++; 
            *transform = '/'; transform++;
        }}
	break;
	case 5:
#line 630 "tokenizer_utils.rl"
	{te = p+1;{ 
            *transform = '\\'; transform++; 
            *transform = '*'; transform++;
        }}
	break;
	case 6:
#line 634 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *ts; transform++; }}
	break;
	case 7:
#line 634 "tokenizer_utils.rl"
	{te = p;p--;{ *transform = *ts; transform++; }}
	break;
#line 2879 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _EscapedForwardSlashesAsterisks_actions + _EscapedForwardSlashesAsterisks_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 2892 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _EscapedForwardSlashesAsterisks_eof_trans[cs] > 0 ) {
		_trans = _EscapedForwardSlashesAsterisks_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 651 "tokenizer_utils.rl"

}


#line 664 "tokenizer_utils.rl"



#line 2918 "tokenizer_utils.c"
static const char _CountSpaces_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3
};

static const char _CountSpaces_key_offsets[] = {
	0
};

static const unsigned char _CountSpaces_trans_keys[] = {
	32u, 0
};

static const char _CountSpaces_single_lengths[] = {
	1
};

static const char _CountSpaces_range_lengths[] = {
	0
};

static const char _CountSpaces_index_offsets[] = {
	0
};

static const char _CountSpaces_trans_targs[] = {
	0, 0, 0
};

static const char _CountSpaces_trans_actions[] = {
	5, 7, 0
};

static const char _CountSpaces_to_state_actions[] = {
	1
};

static const char _CountSpaces_from_state_actions[] = {
	3
};

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

    
#line 2978 "tokenizer_utils.c"
	{
	cs = CountSpaces_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 678 "tokenizer_utils.rl"
    
#line 2988 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _CountSpaces_actions + _CountSpaces_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 3007 "tokenizer_utils.c"
		}
	}

	_keys = _CountSpaces_trans_keys + _CountSpaces_key_offsets[cs];
	_trans = _CountSpaces_index_offsets[cs];

	_klen = _CountSpaces_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _CountSpaces_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _CountSpaces_trans_targs[_trans];

	if ( _CountSpaces_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _CountSpaces_actions + _CountSpaces_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 660 "tokenizer_utils.rl"
	{te = p+1;{ count += 2; }}
	break;
	case 3:
#line 661 "tokenizer_utils.rl"
	{te = p+1;{ count++; }}
	break;
#line 3079 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _CountSpaces_actions + _CountSpaces_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 3092 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 679 "tokenizer_utils.rl"

    return count;
}


#line 696 "tokenizer_utils.rl"



#line 3111 "tokenizer_utils.c"
static const char _NormalizeSpaces_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3
};

static const char _NormalizeSpaces_key_offsets[] = {
	0
};

static const unsigned char _NormalizeSpaces_trans_keys[] = {
	32u, 0
};

static const char _NormalizeSpaces_single_lengths[] = {
	1
};

static const char _NormalizeSpaces_range_lengths[] = {
	0
};

static const char _NormalizeSpaces_index_offsets[] = {
	0
};

static const char _NormalizeSpaces_trans_targs[] = {
	0, 0, 0
};

static const char _NormalizeSpaces_trans_actions[] = {
	5, 7, 0
};

static const char _NormalizeSpaces_to_state_actions[] = {
	1
};

static const char _NormalizeSpaces_from_state_actions[] = {
	3
};

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

    
#line 3170 "tokenizer_utils.c"
	{
	cs = NormalizeSpaces_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 709 "tokenizer_utils.rl"
    
#line 3180 "tokenizer_utils.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _NormalizeSpaces_actions + _NormalizeSpaces_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 3199 "tokenizer_utils.c"
		}
	}

	_keys = _NormalizeSpaces_trans_keys + _NormalizeSpaces_key_offsets[cs];
	_trans = _NormalizeSpaces_index_offsets[cs];

	_klen = _NormalizeSpaces_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _NormalizeSpaces_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _NormalizeSpaces_trans_targs[_trans];

	if ( _NormalizeSpaces_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _NormalizeSpaces_actions + _NormalizeSpaces_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 689 "tokenizer_utils.rl"
	{te = p+1;{
            *transform = 0xC2; transform++;
            *transform = 0xA0; transform++;
        }}
	break;
	case 3:
#line 693 "tokenizer_utils.rl"
	{te = p+1;{ *transform = *ts; transform++; }}
	break;
#line 3274 "tokenizer_utils.c"
		}
	}

_again:
	_acts = _NormalizeSpaces_actions + _NormalizeSpaces_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 3287 "tokenizer_utils.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
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
