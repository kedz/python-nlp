
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
	112u, 111u, 115u, 59u, 117u, 111u, 116u, 153u, 
	158u, 152u, 155u, 185u, 186u, 38u, 194u, 226u, 
	97u, 113u, 128u, 171u, 187u, 145u, 148u, 128u, 
	0
};

static const char _NonAsciiQuoteCounter_single_lengths[] = {
	1, 1, 1, 1, 1, 1, 1, 2, 
	0, 3, 2, 3, 1
};

static const char _NonAsciiQuoteCounter_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	2, 0, 0, 1, 0
};

static const char _NonAsciiQuoteCounter_index_offsets[] = {
	0, 2, 4, 6, 8, 10, 12, 14, 
	17, 20, 24, 27, 32
};

static const char _NonAsciiQuoteCounter_indicies[] = {
	1, 0, 2, 0, 3, 0, 4, 0, 
	5, 0, 6, 0, 3, 0, 4, 4, 
	0, 4, 4, 0, 8, 9, 10, 7, 
	12, 13, 11, 14, 4, 4, 4, 11, 
	15, 11, 0
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
