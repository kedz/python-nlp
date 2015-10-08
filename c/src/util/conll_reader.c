
#line 1 "conll_reader.rl"
#include "conll_reader.h"


#line 20 "conll_reader.rl"



#line 11 "conll_reader.c"
static const char _ws_tok_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4
};

static const char _ws_tok_key_offsets[] = {
	0, 0, 3, 6, 9, 10, 13, 16
};

static const unsigned char _ws_tok_trans_keys[] = {
	32u, 9u, 10u, 9u, 10u, 32u, 9u, 10u, 
	32u, 10u, 9u, 10u, 32u, 9u, 10u, 32u, 
	32u, 9u, 10u, 0
};

static const char _ws_tok_single_lengths[] = {
	0, 1, 3, 3, 1, 3, 3, 1
};

static const char _ws_tok_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 0, 1
};

static const char _ws_tok_index_offsets[] = {
	0, 0, 3, 7, 11, 13, 17, 21
};

static const char _ws_tok_indicies[] = {
	1, 1, 0, 3, 1, 3, 2, 5, 
	1, 5, 4, 7, 6, 5, 7, 5, 
	4, 1, 8, 1, 0, 1, 1, 0, 
	0
};

static const char _ws_tok_trans_targs[] = {
	2, 0, 2, 3, 4, 5, 4, 6, 
	7
};

static const char _ws_tok_trans_actions[] = {
	1, 0, 0, 5, 3, 3, 0, 7, 
	9
};

static const int ws_tok_start = 1;
static const int ws_tok_error = 0;

static const int ws_tok_en_main = 1;


#line 23 "conll_reader.rl"

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

    
#line 77 "conll_reader.c"
	{
	cs = ws_tok_start;
	}

#line 37 "conll_reader.rl"

    
#line 85 "conll_reader.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
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
#line 8 "conll_reader.rl"
	{ ts = p;}
	break;
	case 1:
#line 9 "conll_reader.rl"
	{ ts = p;}
	break;
	case 2:
#line 10 "conll_reader.rl"
	{ NL_add_bspan(mgr, tokens, ts, p - ts, NULL, 0); }
	break;
	case 3:
#line 11 "conll_reader.rl"
	{ NL_add_bspan(mgr, pos, ts, p - ts, NULL, 0); }
	break;
	case 4:
#line 13 "conll_reader.rl"
	{ 
        NL_add_sspan(
            mgr, sents, sent_start, tokens->size - sent_start, NULL, 0);
        sent_start = tokens->size;
    }
	break;
#line 183 "conll_reader.c"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 39 "conll_reader.rl"

    // If the last line is not newline terminated we have to grab the last
    // pos tag.
    if (tokens->size - 1 == pos->size) {
        NL_add_bspan(mgr, pos, ts, pe - ts, NULL, 0);
    }

    if (sent_start != tokens->size) {
        NL_add_sspan(
            mgr, sents, sent_start, tokens->size - sent_start, NULL, 0);
    }
    
    NL_doc *doc = NL_allocate_mem_size(mgr, sizeof(NL_doc));
    doc->buffer = buffer;
    doc->tokens = tokens;
    doc->pos_tags = pos;
    doc->ner_tags = NULL;
    doc->sentences = sents;

    return doc;

}
