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
    string = u"Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
    gold = [u"Ma", u"\u0092m", u"you", u"\u2019re", u"I", u"&apos;ll", u"Chris", u"'s", u"I",
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

def word_redaux_test_LATEX_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"latex"
    string = u"Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
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

def word_redaux_test_ASCII_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"ascii"
    string = u"Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
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

def word_sredaux_test_ASCII_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"ascii"
    string = u"this shouldn't work"
    gold = [u"this", u"should", u"n't", u"work"]
    tokens = nlp.tokenize(string)
    print tokens
    for token in tokens:
        print token.decode("utf-8")
    print
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def soft_hyphen_remove_test():

    string = u"ya\u00AD'll should\u00ADn't de\u00ADstroy\u00ADed " + \
             u"bro\u00ADken \u00AD \u00AD'll"
    gold = [u"ya", u"'ll", u"should", u"n't", u"destroyed", u"broken", u"-", 
            u"-", u"'ll"]
    tokens = nlp.tokenize(string)
    for token in tokens:
        print token.decode("utf-8"),
    print
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

  
def apoword_test_NO_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = None
    string = u"'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
             u" A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
             u"nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
             u"O\u0091o o\u2018o o\u201BO" 
    gold = [u"'n'", u"'n", u"D'", u"d\u0092", u"j\u2019", u"dunkin\u0092",
            u"ol\u2019", u"'em", u"A`vast", u"'20s", u"'90s", u"'till", 
            u"'til", u"'cause", u"cont'd.", u"cont'd", u"nor'easter",
            u"c'mon", u"e'er", u"s'mores", u"ev'ry", u"li'l", u"nat'l",
            u"O\u0091o", u"o\u2018o", u"o\u201BO"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token.encode("utf-8")
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def apoword_test_UNICODE_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"unicode"
    string = u"'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
             u" A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
             u"nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
             u"O\u0091o o\u2018o o\u201BO" 
    gold = [u"\u2019n\u2019", u"\u2019n", u"D\u2019", u"d\u2019", u"j\u2019",
            u"dunkin\u2019", u"ol\u2019", u"\u2019em", u"A`vast", 
            u"\u201920s", u"\u201990s", u"\u2019till", u"\u2019til", 
            u"\u2019cause", u"cont\u2019d.", u"cont\u2019d", 
            u"nor\u2019easter", u"c\u2019mon", u"e\u2019er", u"s\u2019mores",
            u"ev\u2019ry", u"li\u2019l", u"nat\u2019l",
            u"O\u2018o", u"o\u2018o", u"o\u201BO"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token.encode("utf-8")
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def apoword_test_ASCII_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"ascii"
    string = u"'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
             u" A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
             u"nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
             u"O\u0091o o\u2018o o\u201BO" 
    gold = [u"'n'", u"'n", u"D'", u"d'", u"j'",
            u"dunkin'", u"ol'", u"'em", u"A`vast", 
            u"'20s", u"'90s", u"'till", u"'til", 
            u"'cause", u"cont'd.", u"cont'd", 
            u"nor'easter", u"c'mon", u"e'er", u"s'mores",
            u"ev'ry", u"li'l", u"nat'l",
            u"O'o", u"o'o", u"o'O"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token.encode("utf-8")
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def apoword_test_LATEX_normalize_quotes():
    nlp.get_global_PTB_config().normalize_quotes = u"latex"
    string = u"'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
             u" A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
             u"nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
             u"O\u0091o o\u2018o o\u201BO" 
    gold = [u"'n'", u"'n", u"D'", u"d'", u"j'",
            u"dunkin'", u"ol'", u"'em", u"A`vast", 
            u"'20s", u"'90s", u"'till", u"'til", 
            u"'cause", u"cont'd.", u"cont'd", 
            u"nor'easter", u"c'mon", u"e'er", u"s'mores",
            u"ev'ry", u"li'l", u"nat'l",
            u"O`o", u"o`o", u"o`O"]

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token.encode("utf-8")
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)


def apoword2_test():
    string = u"y'all are nice y' "
    gold = [u"y'", u"all", u"are", u"nice", u"y", u"'"]    

    tokens = nlp.tokenize(string)
    for token, gold_token in zip(tokens, gold):
        print token, gold_token.encode("utf-8")
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)


