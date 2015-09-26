
#line 1 "whitespace_tokenizer.rl"
#include "whitespace_tokenizer.h"


#line 45 "whitespace_tokenizer.rl"



#line 11 "whitespace_tokenizer.c"
static const char _ws_tok_actions[] = {
	0, 1, 0, 1, 1, 2, 0, 1, 
	2, 1, 0
};

static const char _ws_tok_key_offsets[] = {
	0, 6, 12, 18, 26, 33, 43, 50, 
	57, 65, 72, 82, 89
};

static const unsigned char _ws_tok_trans_keys[] = {
	32u, 194u, 226u, 227u, 9u, 13u, 32u, 194u, 
	226u, 227u, 9u, 13u, 32u, 194u, 226u, 227u, 
	9u, 13u, 32u, 133u, 160u, 194u, 226u, 227u, 
	9u, 13u, 32u, 128u, 194u, 226u, 227u, 9u, 
	13u, 32u, 194u, 226u, 227u, 9u, 13u, 128u, 
	138u, 168u, 169u, 32u, 128u, 194u, 226u, 227u, 
	9u, 13u, 32u, 128u, 194u, 226u, 227u, 9u, 
	13u, 32u, 133u, 160u, 194u, 226u, 227u, 9u, 
	13u, 32u, 128u, 194u, 226u, 227u, 9u, 13u, 
	32u, 194u, 226u, 227u, 9u, 13u, 128u, 138u, 
	168u, 169u, 32u, 128u, 194u, 226u, 227u, 9u, 
	13u, 32u, 128u, 194u, 226u, 227u, 9u, 13u, 
	0
};

static const char _ws_tok_single_lengths[] = {
	4, 4, 4, 6, 5, 4, 5, 5, 
	6, 5, 4, 5, 5
};

static const char _ws_tok_range_lengths[] = {
	1, 1, 1, 1, 1, 3, 1, 1, 
	1, 1, 3, 1, 1
};

static const char _ws_tok_index_offsets[] = {
	0, 6, 12, 18, 26, 33, 41, 48, 
	55, 63, 70, 78, 85
};

static const char _ws_tok_indicies[] = {
	1, 2, 3, 4, 1, 0, 6, 7, 
	8, 9, 6, 5, 10, 11, 12, 13, 
	10, 0, 6, 6, 6, 7, 8, 9, 
	6, 5, 6, 14, 7, 8, 9, 6, 
	5, 6, 7, 8, 9, 6, 6, 6, 
	5, 6, 15, 7, 8, 9, 6, 5, 
	6, 6, 7, 8, 9, 6, 5, 6, 
	16, 16, 7, 8, 9, 6, 5, 6, 
	17, 7, 8, 9, 6, 5, 6, 7, 
	8, 9, 6, 16, 16, 5, 6, 18, 
	7, 8, 9, 6, 5, 6, 16, 7, 
	8, 9, 6, 5, 0
};

static const char _ws_tok_trans_targs[] = {
	1, 0, 8, 9, 11, 1, 2, 3, 
	4, 6, 2, 3, 4, 6, 5, 7, 
	0, 10, 12
};

static const char _ws_tok_trans_actions[] = {
	1, 5, 1, 1, 1, 0, 3, 0, 
	0, 0, 8, 1, 1, 1, 0, 0, 
	3, 0, 0
};

static const char _ws_tok_eof_actions[] = {
	5, 3, 5, 3, 3, 3, 3, 3, 
	3, 3, 3, 3, 3
};

static const int ws_tok_start = 0;
static const int ws_tok_error = -1;

static const int ws_tok_en_main = 0;


#line 48 "whitespace_tokenizer.rl"

NL_annotations *NL_ws_tokenize(NL_buffer *buffer, NL_v_memmgr *mgr) {
    int cs;
    unsigned char *p = buffer->bytes;  
    unsigned char *pe = p + buffer->size; 
    unsigned char *eof = pe;
    unsigned char *ts = p;

    NL_annotations *ann = NL_new_bspan_annotations(mgr);

    
#line 103 "whitespace_tokenizer.c"
	{
	cs = ws_tok_start;
	}

#line 59 "whitespace_tokenizer.rl"

    
#line 111 "whitespace_tokenizer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_keys = _ws_tok_trans_keys + _ws_tok_key_offsets[cs];
	_trans = _ws_tok_index_offsets[cs];

	_klen = _ws_tok_single_lengths[cs];
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

	_klen = _ws_tok_range_lengths[cs];
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
	_trans = _ws_tok_indicies[_trans];
	cs = _ws_tok_trans_targs[_trans];

	if ( _ws_tok_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _ws_tok_actions + _ws_tok_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 37 "whitespace_tokenizer.rl"
	{ ts = p; }
	break;
	case 1:
#line 39 "whitespace_tokenizer.rl"
	{
        NL_add_bspan(mgr, ann, ts, p - ts, NULL, 0);
    }
	break;
#line 193 "whitespace_tokenizer.c"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _ws_tok_actions + _ws_tok_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
#line 37 "whitespace_tokenizer.rl"
	{ ts = p; }
	break;
	case 1:
#line 39 "whitespace_tokenizer.rl"
	{
        NL_add_bspan(mgr, ann, ts, p - ts, NULL, 0);
    }
	break;
#line 217 "whitespace_tokenizer.c"
		}
	}
	}

	}

#line 61 "whitespace_tokenizer.rl"

    return ann;

}
