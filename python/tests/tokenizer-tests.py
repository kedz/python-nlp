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
