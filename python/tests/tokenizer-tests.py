import nlp

def plangs_test():

    string = u"C++ c++ C# c# F# f#"
    gold = [u"C++", u"c++", u"C#", u"c#", u"F#", u"f#"]

    tokens = nlp.tokenize(string)

    for token, gold_token in zip(tokens, gold):
        print token, gold_token
        assert token == gold_token.encode("utf-8")

    assert len(tokens) == len(gold)

def assims3_NO_normalize_test():
    nlp.get_global_PTB_config().split_assimilations = False
    string = u"cannot gonna gotta lemme gimme wanna"
    gold = [u"cannot", u"gonna", u"gotta", u"lemme", u"gimme", u"wanna"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token
        assert token == gold_token.encode("utf-8")

    assert len(tokens) == len(gold)

def assims3_normalize_test():
    nlp.get_global_PTB_config().split_assimilations = True
    string = u"cannot gonna gotta lemme gimme wanna"
    gold = [u"can", u"not", u"gon", u"na", u"got", u"ta", u"lem", u"me",
            u"gim", u"me", u"wan", u"na"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token
        assert token == gold_token.encode("utf-8")

    assert len(tokens) == len(gold)



def assims2_normalize_test():
    nlp.get_global_PTB_config().split_assimilations = True
    string = u"'twas 'tis"
    gold = [u"'t", u"was", u"'t", u"is"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token
        assert token == gold_token.encode("utf-8")

    assert len(tokens) == len(gold)

def assims2_NO_normalize_test():

    string = u"'twas 'tis"
    gold = [u"'twas", u"'tis"]

    nlp.get_global_PTB_config().split_assimilations = False

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token
        assert token == gold_token.encode("utf-8")

    assert len(tokens) == len(gold)
                
def spmdash_normalize_test():

    nlp.get_global_PTB_config().normalize_dashes = True
    string = u"&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
    gold = [u"--", u"--", u"--", u"--", u"--", u"--",
            u"--", u"--"]
    tokens = nlp.tokenize(string)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def spmdash_NO_normalize_test():

    nlp.get_global_PTB_config().normalize_dashes = False
    string = u"&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
    gold = [u"&MD;", u"&mdash;", u"&ndash;", u"\u0096", u"\u0097", u"\u2013",
            u"\u2014", u"\u2015"]
    tokens = nlp.tokenize(string)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def spamp_normalize_test():

    nlp.get_global_PTB_config().normalize_amp = True
    string = u"&amp; is not normed yet";
    gold = [u"&", u"is", u"not", u"normed", u"yet"]
    tokens = nlp.tokenize(string)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)
 
def spamp_NO_normalize_test():

    nlp.get_global_PTB_config().normalize_amp = False
    string = u"&amp; is not normed yet";
    gold = [u"&amp;", u"is", u"not", u"normed", u"yet"]
    tokens = nlp.tokenize(string)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def sppunc_test():
    string = u"&HT; &TL; &UR; &LR; &QC; &QL; &QR; &odq; &cdq; &#0123;" 
    gold = [u"&HT;", u"&TL;", u"&UR;", u"&LR;", u"&QC;", u"&QL;", u"&QR;",
            u"&odq;", u"&cdq;", u"&#0123;"] 
    tokens = nlp.tokenize(string)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def word_redaux_test_NO_normalize_quotes():

    nlp.get_global_PTB_config().normalize_quotes = None
    string = u"Ma'm you're I'll Chris's I'd you're"
    gold = [u"Ma", u"'m", u"you", u"'re", u"I", u"'ll", u"Chris", u"'s", u"I",
            u"'d", u"you", u"'re"]
    tokens = nlp.tokenize(string)
    print tokens
    for token in tokens:
        print token.decode("utf-8"),
    print
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def word_redaux_test_UNICODE_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"unicode"
    string = u"Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
    gold = [u"Ma", u"\u2019m", u"you", u"\u2019re", u"I", u"\u2019ll", u"Chris", u"\u2019s", u"I",
            u"\u2019d", u"you", u"\u2019re"]
    tokens = nlp.tokenize(string)
    print tokens
    for token in tokens:
        print token.decode("utf-8"),
    print
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)
