import nlp
from nose.tools import raises

def test_ptb_tok_config1():
    cfg = nlp.get_global_PTB_config()
    cfg.normalize_quotes = u"unicode"
    assert cfg.normalize_quotes == u"unicode"

def test_ptb_tok_config2():
    cfg = nlp.get_global_PTB_config()
    cfg.normalize_quotes = u"latex"
    assert cfg.normalize_quotes == u"latex"

def test_ptb_tok_config3():
    cfg = nlp.get_global_PTB_config()
    cfg.normalize_quotes = u"ascii"
    assert cfg.normalize_quotes == u"ascii"

def test_ptb_tok_config4():
    cfg = nlp.get_global_PTB_config()
    cfg.normalize_quotes = None
    assert cfg.normalize_quotes == None


@raises(ValueError)
def test_ptb_tok_config_exception():
    cfg = nlp.get_global_PTB_config()
    cfg.normalize_quotes = u"not a valid option"
