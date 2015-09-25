# encoding=utf-8
from __future__ import (absolute_import, division, print_function,
    unicode_literals)
import sys

import nlp

class Tok_Test:
    def setUp(self): 
        nlp.get_global_PTB_config().default()

        if sys.version_info[0] == 3:
            unichr = chr

    def test_plangs(self):

        string = "C++ c++ C# c# F# f#"
        gold = ["C++", "c++", "C#", "c#", "F#", "f#"]

        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):
            print(token, gold_token)
            assert bytes(token) == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims3_NO_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = False
        string = "cannot gonna gotta lemme gimme wanna"
        gold = ["cannot", "gonna", "gotta", "lemme", "gimme", "wanna"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token)
            assert bytes(token) == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims3_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = True
        string = "cannot gonna gotta lemme gimme wanna"
        gold = ["can", "not", "gon", "na", "got", "ta", "lem", "me",
                "gim", "me", "wan", "na"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token)
            assert bytes(token) == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)



    def assims2_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = True
        string = "'twas 'tis"
        gold = ["'t", "was", "'t", "is"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token)
            assert bytes(token) == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims2_NO_normalize_test(self):

        string = "'twas 'tis"
        gold = ["'twas", "'tis"]

        nlp.get_global_PTB_config().split_assimilations = False

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token)
            assert bytes(token) == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)
                    
    def spmdash_normalize_test(self):

        nlp.get_global_PTB_config().normalize_dashes = True
        string = "&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
        gold = ["--", "--", "--", "--", "--", "--",
                "--", "--"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def spmdash_NO_normalize_test(self):

        nlp.get_global_PTB_config().normalize_dashes = False
        string = "&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
        gold = ["&MD;", "&mdash;", "&ndash;", "\u0096", "\u0097", "\u2013",
                "\u2014", "\u2015"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def spamp_normalize_test(self):

        nlp.get_global_PTB_config().normalize_amp = True
        string = "&amp; is not normed yet";
        gold = ["&", "is", "not", "normed", "yet"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
     
    def spamp_NO_normalize_test(self):

        nlp.get_global_PTB_config().normalize_amp = False
        string = "&amp; is not normed yet";
        gold = ["&amp;", "is", "not", "normed", "yet"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def sppunc_test(self):
        string = "&HT; &TL; &UR; &LR; &QC; &QL; &QR; &odq; &cdq; &#0123;" 
        gold = ["&HT;", "&TL;", "&UR;", "&LR;", "&QC;", "&QL;", "&QR;",
                "&odq;", "&cdq;", "&#0123;"] 
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def word_redaux_test_NO_normalize_quotes(self):

        nlp.get_global_PTB_config().normalize_quotes = None
        string = "Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
        gold = ["Ma", "\u0092m", "you", "\u2019re", "I", "&apos;ll", "Chris", "'s", "I",
                "'d", "you", "'re"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token in tokens:
            print(bytes(token).decode("utf-8"),)
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_redaux_test_UNICODE_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "unicode"
        string = "Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
        gold = ["Ma", "\u2019m", "you", "\u2019re", "I", "\u2019ll", "Chris", "\u2019s", "I",
                "\u2019d", "you", "\u2019re"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token in tokens:
            print(bytes(token).decode("utf-8"),)
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_redaux_test_LATEX_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "latex"
        string = "Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
        gold = ["Ma", "'m", "you", "'re", "I", "'ll", "Chris", "'s", "I",
                "'d", "you", "'re"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token in tokens:
            print(bytes(token).decode("utf-8"),)
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_redaux_test_ASCII_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "ascii"
        string = "Ma\u0092m you\u2019re I&apos;ll Chris's I'd you're"
        gold = ["Ma", "'m", "you", "'re", "I", "'ll", "Chris", "'s", "I",
                "'d", "you", "'re"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token in tokens:
            print(bytes(token).decode("utf-8"),)
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_sredaux_test_ASCII_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "ascii"
        string = "this shouldn't work"
        gold = ["this", "should", "n't", "work"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token in tokens:
            print(bytes(token).decode("utf-8"))
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def soft_hyphen_remove_test(self):

        string = "ya\u00AD'll should\u00ADn't de\u00ADstroy\u00ADed " + \
                 "bro\u00ADken \u00AD \u00AD'll"
        gold = ["ya", "'ll", "should", "n't", "destroyed", "broken", "-", 
                "-", "'ll"]
        tokens = nlp.tokenize(string)
        for token in tokens:
            print(bytes(token).decode("utf-8"),)
        print
        for token, gold_token in zip(tokens, gold):
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

      
    def apoword_test_NO_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = None
        string = "'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
                 " A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
                 "nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
                 "O\u0091o o\u2018o o\u201BO" 
        gold = ["'n'", "'n", "D'", "d\u0092", "j\u2019", "dunkin\u0092",
                "ol\u2019", "'em", "A`vast", "'20s", "'90s", "'till", 
                "'til", "'cause", "cont'd.", "cont'd", "nor'easter",
                "c'mon", "e'er", "s'mores", "ev'ry", "li'l", "nat'l",
                "O\u0091o", "o\u2018o", "o\u201BO"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def apoword_test_UNICODE_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "unicode"
        string = "'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
                 " A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
                 "nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
                 "O\u0091o o\u2018o o\u201BO" 
        gold = ["\u2019n\u2019", "\u2019n", "D\u2019", "d\u2019", "j\u2019",
                "dunkin\u2019", "ol\u2019", "\u2019em", "A`vast", 
                "\u201920s", "\u201990s", "\u2019till", "\u2019til", 
                "\u2019cause", "cont\u2019d.", "cont\u2019d", 
                "nor\u2019easter", "c\u2019mon", "e\u2019er", "s\u2019mores",
                "ev\u2019ry", "li\u2019l", "nat\u2019l",
                "O\u2018o", "o\u2018o", "o\u201BO"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def apoword_test_ASCII_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "ascii"
        string = "'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
                 " A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
                 "nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
                 "O\u0091o o\u2018o o\u201BO" 
        gold = ["'n'", "'n", "D'", "d'", "j'",
                "dunkin'", "ol'", "'em", "A`vast", 
                "'20s", "'90s", "'till", "'til", 
                "'cause", "cont'd.", "cont'd", 
                "nor'easter", "c'mon", "e'er", "s'mores",
                "ev'ry", "li'l", "nat'l",
                "O'o", "o'o", "o'O"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def apoword_test_LATEX_normalize_quotes(self):
        nlp.get_global_PTB_config().normalize_quotes = "latex"
        string = "'n' 'n D' d\u0092 j\u2019 dunkin\u0092 ol\u2019 'em" + \
                 " A`vast '20s '90s 'till 'til 'cause cont'd. cont'd " + \
                 "nor'easter c'mon e'er s'mores ev'ry li'l nat'l " + \
                 "O\u0091o o\u2018o o\u201BO" 
        gold = ["'n'", "'n", "D'", "d'", "j'",
                "dunkin'", "ol'", "'em", "A`vast", 
                "'20s", "'90s", "'till", "'til", 
                "'cause", "cont'd.", "cont'd", 
                "nor'easter", "c'mon", "e'er", "s'mores",
                "ev'ry", "li'l", "nat'l",
                "O`o", "o`o", "o`O"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def apoword2_test(self):
        string = "y'all are nice y' "
        gold = ["y'", "all", "are", "nice", "y", "'"]    

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    #def full_or_likely_url_NO_escape_test(self):
    #    string = "https://cs.columbia.edu http://www.google.com " + \
    #             "www.nytimes.com/world.html nytimes.com nytimes.com/americas"
    #    gold = ["https://cs.columbia.edu", 
    #            "http://www.google.com",
    #            "www.nytimes.com/world.html",
    #            "nytimes.com", 
    #            "nytimes.com/americas",]
    #
    #    tokens = nlp.tokenize(string)
    #    for token, gold_token in zip(tokens, gold):
    #        print(token, gold_token.encode("utf-8"))
    #        assert bytes(token) == gold_token.encode("utf-8")
    #    assert len(tokens) == len(gold)

    #def email_test(self):
    #    string = "<crk2130@columbia.edu> thekedz@gmail.com " + \
    #             "christopher.r.kedzie@gmail.com &lt;chris.kedzie@outlook.com&gt;"
    #    gold = ["<crk2130@columbia.edu>", "thekedz@gmail.com", 
    #            "christopher.r.kedzie@gmail.com", 
    #            "&lt;chris.kedzie@outlook.com&gt;"]
    #
    #    tokens = nlp.tokenize(string)
    #    print(tokens)
    #    for token, gold_token in zip(tokens, gold):
    #        print(token, gold_token.encode("utf-8"))
    #        assert bytes(token) == gold_token.encode("utf-8")
    #    assert len(tokens) == len(gold)
    #    print(nlp.tokenize("ked zie@gmail.com"))
    #    print(nlp.tokenize(u"ked\u00A0zie@gmail.com".encode("utf-8")))

    def twiiter_test(self):
        string = "@the_real_kedzie1 #nlp #cs"
        gold = ["@the_real_kedzie1",  "#nlp", "#cs"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def date_test_NO_escapeing(self):
        string = "01/29/1986 04-11-1995"
        gold = ["01/29/1986", "04-11-1995"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def number_test(self):
        string = "-1234 +1\u00AD200.4 +12.98 -.33 +.02 +0.2"
        gold = ["-1234", "+1200.4", "+12.98", "-.33", "+.02", "+0.2"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def subsupnum_test(self):
        string = "note\u207A\u2070\u00B9\u00B2\u00B3 \u2074 \u2075 \u2076" \
            + " \u2080\u2081 \u2082 \u2083"
        gold = ["note", "\u207A\u2070\u00B9\u00B2\u00B3", "\u2074", "\u2075",
                "\u2076", "\u2080\u2081", "\u2082", "\u2083"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    # do fracs

    def frac_NO_normalize_NO_escape_test(self):
        cfg = nlp.get_global_PTB_config()
        cfg.normalize_spaces = False
        cfg.escape_forward_slash_asterisk = False
        cfg.strict_ptb3 = False
        string = "1234 1234/1234 1234-1234/1234 1234\u00A01234/1234 " \
            "1234 1234\\/1234 1234-1234\\/1234 1234\u00A01234\\/1234 " \
            "1234 1234\u20441234 1234-1234\u20441234 " \
            "1234\u00A01234\u20441234"
        gold = ["1234 1234/1234", "1234-1234/1234", "1234\u00A01234/1234",
                "1234 1234\\/1234", "1234-1234\\/1234", 
                "1234\u00A01234\\/1234", "1234 1234\u20441234", 
                "1234-1234\u20441234", "1234\u00A01234\u20441234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       


    def frac_normalize_NO_escape_test(self):
        cfg = nlp.get_global_PTB_config()
        cfg.normalize_spaces = True
        cfg.escape_forward_slash_asterisk = False
        cfg.strict_ptb3 = False
        string = "1234 1234/1234 1234-1234/1234 1234\u00A01234/1234 " \
            "1234 1234\\/1234 1234-1234\\/1234 1234\u00A01234\\/1234 " \
            "1234 1234\u20441234 1234-1234\u20441234 " \
            "1234\u00A01234\u20441234"
        gold = ["1234\u00A01234/1234", "1234-1234/1234", 
                "1234\u00A01234/1234", "1234\u00A01234\\/1234", 
                "1234-1234\\/1234", "1234\u00A01234\\/1234", 
                "1234\u00A01234\u20441234", "1234-1234\u20441234", 
                "1234\u00A01234\u20441234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       

    def frac_NO_normalize_escape_test(self):
        cfg = nlp.get_global_PTB_config()
        cfg.normalize_spaces = False
        cfg.escape_forward_slash_asterisk = True
        cfg.strict_ptb3 = False
        string = "1234 1234/1234 1234-1234/1234 1234\u00A01234/1234 " \
            "1234 1234\\/1234 1234-1234\\/1234 1234\u00A01234\\/1234 " \
            "1234 1234\u20441234 1234-1234\u20441234 " \
            "1234\u00A01234\u20441234"
        gold = ["1234 1234\\/1234", "1234-1234\\/1234", 
                "1234\u00A01234\\/1234",
                "1234 1234\\/1234", "1234-1234\\/1234", 
                "1234\u00A01234\\/1234", "1234 1234\u20441234", 
                "1234-1234\u20441234", "1234\u00A01234\u20441234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       

    def frac_normalize_escape_test(self):
        cfg = nlp.get_global_PTB_config()
        cfg.normalize_spaces = True
        cfg.escape_forward_slash_asterisk = True
        cfg.strict_ptb3 = False
        string = "1234 1234/1234 1234-1234/1234 1234\u00A01234/1234 " \
            "1234 1234\\/1234 1234-1234\\/1234 1234\u00A01234\\/1234 " \
            "1234 1234\u20441234 1234-1234\u20441234 " \
            "1234\u00A01234\u20441234"
        gold = ["1234\u00A01234\\/1234", "1234-1234\\/1234", 
                "1234\u00A01234\\/1234", "1234\u00A01234\\/1234", 
                "1234-1234\\/1234", "1234\u00A01234\\/1234", 
                "1234\u00A01234\u20441234", "1234-1234\u20441234", 
                "1234\u00A01234\u20441234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       


    def frac2_NO_normalize_NO_escape_test(self):
        nlp.get_global_PTB_config().normalize_fractions = False
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = False
        string = "\u00BC \u00BD \u00BE \u2153 \u2154 \u2155 \u2156 \u2157" \
                " \u2158 \u2159 \u215A \u215B \u215C \u215D \u215E"
        gold = ["\u00BC", "\u00BD", "\u00BE", "\u2153", "\u2154",
                "\u2155", "\u2156", "\u2157", "\u2158", "\u2159",
                "\u215A", "\u215B", "\u215C", "\u215D", "\u215E"]
        tokens = nlp.tokenize(string)
        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       

    def frac2_normalize_NO_escape_test(self):
        nlp.get_global_PTB_config().normalize_fractions = True
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = False
        string = "\u00BC \u00BD \u00BE \u2153 \u2154 \u2155 \u2156 \u2157" \
                " \u2158 \u2159 \u215A \u215B \u215C \u215D \u215E"
        gold = ["1/4", "1/2", "3/4", "1/3", "2/3",
                "1/5", "2/5", "3/5", "4/5", "1/6",
                "5/6", "1/8", "3/8", "5/8", "7/8"]
        tokens = nlp.tokenize(string)

        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       

    def frac2_normalize_escape_test(self):
        nlp.get_global_PTB_config().normalize_fractions = True
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = True
        string = "\u00BC \u00BD \u00BE \u2153 \u2154 \u2155 \u2156 \u2157" \
                " \u2158 \u2159 \u215A \u215B \u215C \u215D \u215E"
        gold = ["1\\/4", "1\\/2", "3\\/4", "1\\/3", "2\\/3",
                "1\\/5", "2\\/5", "3\\/5", "4\\/5", "1\\/6",
                "5\\/6", "1\\/8", "3\\/8", "5\\/8", "7\\/8"]
        tokens = nlp.tokenize(string)

        print(tokens)
        print(gold)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)       




    def tbspec_test(self):
        string = "-RRB- -LRB- -RCB- -lcb- -lsb- C.D.s PRO-nouns anti-con " + \
            "s&p-500  S&amp;p-500  S&amp;Ls  cap'n C'est" #
        gold = ["-RRB-", "-LRB-", "-RCB-", "-lcb-", "-lsb-", "C.D.s", 
                "PRO-nouns", "anti-con", "s&p-500", "S&p-500", 
                "S&Ls", "cap'n", "C'est"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def bangwords_test(self):
        string = "E! yahoo! Jeopardy! ok!\nmagazine"
        gold = ["E!", "yahoo!", "Jeopardy!", "ok!", "magazine"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def thing3_test_NO_escaping(self):
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = False
        string = "Aa0-Ab-Ab/Aa0/Aa0-Aa1 ab\\/zzz"
        gold = ["Aa0-Ab-Ab/Aa0/Aa0-Aa", "1", "ab\\/zzz"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def thing3_test_escaping(self):
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = True
        string = "Aa0-Ab-Ab/Aa0/Aa0-Aa1 ab\\/zzz"
        gold = ["Aa0-Ab-Ab\\/Aa0\\/Aa0-Aa", "1", "ab\\/zzz"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def dolsign_test(self):
        string = "US$ $ # UK$"
        gold = ["US$", "$", "#", "UK$"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def dolsign2_test_NO_normalize(self):
        string = "\u00A2 \u00A3 \u00A4 \u00A5 \u0080 \u20A0 \u20AC " + \
            "\u060B \u0E3F \u20A4 \uFFE0 \uFFE1 \uFFE5 \uFFE6"
        gold = ["\u00A2", "\u00A3", "\u00A4", "\u00A5", "\u0080", "\u20A0",
                "\u20AC", "\u060B", "\u0E3F", "\u20A4", "\uFFE0", "\uFFE1",
                "\uFFE5", "\uFFE6"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def dolsign2_test_normalize(self):
        nlp.get_global_PTB_config().normalize_currency = True
        string = "\u00A2 \u00A3 \u00A4 \u00A5 \u0080 \u20A0 \u20AC " + \
            "\u060B \u0E3F \u20A4 \uFFE0 \uFFE1 \uFFE5 \uFFE6"
        gold = ["cents", "#", "\\$", "\u00A5", "\\$", "\\$", "\\$", 
                "\u060B", "\u0E3F", "\u20A4", "\uFFE0", "\uFFE1", "\uFFE5",
                "\uFFE6"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def acronym_space_special_word_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = False
        string = "I. About A.B.C. After "
        gold = ["I", ".", "About", "A.B.C.", ".", "After"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def pty_ltd_test(self):
        string = "pte. ltd. co. lim."
        gold = ["pte.", "ltd.", "co.", "lim", "."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev1_sentend_STRICT_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = True
        string = "Mass.  et al.  " 
        gold = ["Mass", ".", "et", "al", "."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev1_sentend_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = False
        string = "Mass.  et al.  " 
        gold = ["Mass.", ".", "et", "al.", "."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev1_any_any_test(self):
        string = "Mass. ave  " 
        gold = ["Mass.", "ave"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev1_STRICT_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = True
        string = "Mass." 
        gold = ["Mass", "."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def abbrev1_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = False
        string = "Mass." 
        gold = ["Mass.", "."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev2_test(self):
        string = "U.S. a.k.a." 
        gold = ["U.S.", "a.k.a."]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def abbrev4_space_test(self):
        string = "Dept Ph " 
        gold = ["Dept", "Ph"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def acro_space_test(self):
        string = "U.S U.K " 
        gold = ["U.S", "U.K"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def tbspec_space_test(self):
        string = "'99 '86" 
        gold = ["'99", "'", "86"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def filename_spacepunc_test(self):
        string = "test1.gif. test2.gif!" 
        gold = ["test1.gif", ".", "test2.gif", "!"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_per_insentp_test(self):
        string = "PP\u00ADL.; for one"
        gold = ["PPL.", ";", "for", "one"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def phone_NO_normalize_space_NO_normalize_par_test(self):
        nlp.get_global_PTB_config().normalize_spaces = False
        nlp.get_global_PTB_config().normalize_parentheses = False
        string = "++012.12.123.12345 (123) 123-1234"
        gold = ["++012.12.123.12345", "(123) 123-1234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def phone_normalize_space_NO_normalize_par_test(self):
        nlp.get_global_PTB_config().normalize_spaces = True
        nlp.get_global_PTB_config().normalize_parentheses = False
        string = "++012.12.123.12345 (123) 123-1234"
        gold = ["++012.12.123.12345", "(123)\u00A0123-1234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def phone_NO_normalize_space_normalize_par_test(self):
        nlp.get_global_PTB_config().normalize_spaces = False
        nlp.get_global_PTB_config().normalize_parentheses = True
        string = "++012.12.123.12345 (123) 123-1234"
        gold = ["++012.12.123.12345", "-LRB-123-RRB- 123-1234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def phone_normalize_space_normalize_par_test(self):
        string = "++012.12.123.12345 (123) 123-1234"
        gold = ["++012.12.123.12345", "-LRB-123-RRB-\u00A0123-1234"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def double_quotes_NO_normalize_test(self):
        nlp.get_global_PTB_config().normalize_quotes = None
        string = u'"This is a test"'
        gold = [u'"', "This", "is", "a", "test", u'"']
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def double_quotes_LATEX_normalize_test(self):
        nlp.get_global_PTB_config().normalize_quotes = "latex"
        string = u'"This is a test"'
        gold = [u'``', "This", "is", "a", "test", "''"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def double_quotes_unicode_normalize_test(self):
        nlp.get_global_PTB_config().normalize_quotes = "unicode"
        string = u'"This is a test"'
        gold = [u'\u201C', "This", "is", "a", "test", "\u201D"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def double_quotes_ASCII_normalize_test(self):
        nlp.get_global_PTB_config().normalize_quotes = "ascii"
        string = u'&quot;This is a test&quot;'
        gold = [u'"', "This", "is", "a", "test", u'"']
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def gt_lt_test(self):
        string = "< > &gt; &lt;"
        gold = ["<", ">", ">", "<"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)   

    def smiley_NO_normalize_test(self):
        nlp.get_global_PTB_config().normalize_parentheses = False
        string = "<:-(   >;o)   =\\ "
        gold = ["<:-(", ">;o)", "=\\"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def smiley_normalize_test(self):
        nlp.get_global_PTB_config().normalize_parentheses = True
        string = "<:-(   >;o)   ={ "
        gold = ["<:--LRB-", ">;o-RRB-", "={"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def acronym3_space_digit_test(self):
        string = "fig. 2 figs.3 prop.4 no.5 nos.6 art.7 bldg.8 pp.9 op.1"
        gold = ["fig.", "2", "figs.", "3", "prop.", "4",
                "no.", "5", "nos.", "6", "art.", "7", "bldg.", "8",
                "pp.", "9", "op.", "1"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def acronym_STRICT_ptb3_space_special_word_test(self):
        nlp.get_global_PTB_config().strict_ptb3 = True
        string = "I. About A.B.C. After "
        gold = ["I", ".", "About", "A.B.C", ".", "After"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def test_brackets_NO_normalize(self):
        nlp.get_global_PTB_config().normalize_parentheses = False
        nlp.get_global_PTB_config().normalize_brackets = False
        string = "(){}[]"
        gold = ["(", ")", "{", "}", "[", "]"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def test_brackets_normalize(self):
        nlp.get_global_PTB_config().normalize_parentheses = True
        nlp.get_global_PTB_config().normalize_brackets = True
        string = "(){}[]"
        gold = ["-LRB-", "-RRB-", "-LCB-", "-RCB-", "-LSB-", "-RSB-"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def hyphens_NO_normalize_test(self):
        nlp.get_global_PTB_config().normalize_dashes = False
        string = "--- - -- --- -----"
        gold = ["---", "-", "--", "---", "-----"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def hyphens_normalize_test(self):
        nlp.get_global_PTB_config().normalize_dashes = True
        string = "--- - -- ---- -----"
        gold = ["--", "-", "--", "--", "-----"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)




    def ldots_NO_normalize_test(self):
        nlp.get_global_PTB_config().normalize_ellipsis = None
        string = "... .... ..... . .\u00A0. \u2026"
        gold = ["...", "....", ".....", ". .\u00A0.", "\u2026"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ldots_ptb3_normalize_test(self):
        nlp.get_global_PTB_config().normalize_ellipsis = "ptb3"
        string = "... .... ..... . .\u00A0. \u2026"
        gold = ["...", "...", "...", "...", "..."]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ldots_unicode_normalize_test(self):
        nlp.get_global_PTB_config().normalize_ellipsis = "unicode"
        string = "... .... ..... . .\u00A0.   \u2026"
        gold = ["\u2026", "\u2026", "\u2026", "\u2026", "\u2026"]
        tokens = nlp.tokenize(string)
        print(tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def ldots_ptb3_normalize_test(self):
        nlp.get_global_PTB_config().normalize_ellipsis = "ptb3"
        string = "... .... ..... . .\u00A0."
        gold = ["...", "...", "...", "..."]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def fnmarks_test(self):
        string = "____@@@@@@##### ### @@@ _"
        gold = ["____", "@@@@@@", "#####", "###", "@@@", "_"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def asts_NO_escape_test(self):
        string = "* ** *** **** \\*\\*\\*\\*\\*"
        gold = ["*", "**", "***", "****", "\\*\\*\\*", "\\*\\*"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def asts_escape_test(self):
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = True
        string = "* ** *** **** \\*\\*\\*\\*\\*"
        gold = ["\\*", "\\*\\*", "\\*\\*\\*", "\\*\\*\\*\\*", 
                "\\*\\*\\*", "\\*\\*"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)





    def insentp_test(self):
        string = "word, word2; word3:word4\u3001word5"
        gold = ["word", ",", "word2", ";", "word3", ":", "word4",
                "\u3001", "word5"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def qmark_exclam_test(self):
        string = "huh?!? ? weirdness! !!! ??"
        gold = ["huh", "?!?", "?", "weirdness", "!", "!!!", "??"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def punc_test(self):
        string = ".¡¿\u037E\u0589\u061F\u06D4\u0700\u0701\u0702\u07FA\u3002"
        gold = [".", "¡", "¿", "\u037E", "\u0589", "\u061F", "\u06D4",
                "\u0700", "\u0701", "\u0702", "\u07FA", "\u3002"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def equals_test(self):
        string = "= == === x==y 1=x"
        gold = ["=", "==", "===", "x", "==", "y", "1", "=", "x"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def slash_NO_escape_test(self):
        string = "/ \\/"
        gold = ["/", "\\/"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def slash_escape_test(self):
        nlp.get_global_PTB_config().escape_forward_slash_asterisk = True
        string = "/ \\/"
        gold = ["\\/", "\\/"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def hthing_per_insentp_test(self):
        string = "US-UK U.S.-U.K.;"
        gold = ["US-UK", "U.S.-U.K.", ";"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)




    def hthing_test(self):
        string = "US-UK U.S.\u00AD-USSR\u00AD"
        gold = ["US-UK", "U.S.-USSR"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def thing_per_insentp_test(self):
        string = "O'doole-o'mally.: 1-o'mally.;"
        gold = ["O'doole-o'mally.", ":", "1-o'mally.", ";"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def thing_test(self):
        string = "O'doole-o'mally 1-o'mally"
        gold = ["O'doole-o'mally", "1-o'mally"]
        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def thinga_NO_normalize_amp_test(self):
        nlp.get_global_PTB_config().normalize_amp = False
        string = "ABC+NBC+CBS ABC&NBC+CBS A&amp;P"
        gold = ["ABC+NBC+CBS", "ABC&NBC+CBS", "A&amp;P"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def thinga_normalize_amp_test(self):
        nlp.get_global_PTB_config().normalize_amp = True
        string = "ABC&amp;NBC&CBS ABC&amp;NBC+CBS A&amp;P"
        gold = ["ABC&NBC&CBS", "ABC&NBC+CBS", "A&P"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


       

    def right_quote_weirdness_NO_normalize_test(self):
        """Should match this pattern: '/[A-Za-z][^ \t\n\r\u00A0] but there is 
        difficulty expressing the intersection of single and double character
        negation."""

        nlp.get_global_PTB_config().normalize_quotes = None    
        string = "'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = ["'", "At", "last", "'", "a", "\u00A2", 
                "'", "a", "'", "a", "'", "a"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def right_quote_weirdness_LATEX_normalize_test(self):

        nlp.get_global_PTB_config().normalize_quotes = "latex"
        string = "'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = ["`", "At", "last", "`", "a", "\u00A2", 
                "'", "a", "'", "a", "'", "a"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def right_quote_weirdness_UNICODE_normalize_test(self):

        nlp.get_global_PTB_config().normalize_quotes = "unicode"
        string = "'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = ["\u2018", "At", "last", "\u2018", "a", "\u00A2", 
                "\u2019", "a", "\u2019", "a", "\u2019", "a"]

        tokens = nlp.tokenize(string)
        print("GOLD  ", gold)
        print("ACTUAL", tokens)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def terminal_redaux_test(self):
        nlp.get_global_PTB_config().normalize_quotes = None
        string = "test ends with you're"
        gold = ["test", "ends", "with", "you", "'re"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def terminal_sredaux_test(self):
        string = "test ends with wouldn't"
        gold = ["test", "ends", "with", "would", "n't"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def test_fake_duckfeet(self):
        string = "duck<<feet >>"
        gold = ["duck", "<<", "feet", ">>"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def test_misc_symbols(self):
        def rngstr(uni1, uni2):
            return " ".join(unichr(i) for i in range(ord(uni1), ord(uni2) + 1))
        string = " ".join(
            [
                "+ % & ~ ^ | \\ \u00A6 \u00A7 \u00A8 \u00A9 \u00AC \u00AE \u00AF",
                rngstr(u"\u00B0", "\u00B3"),
                rngstr(u"\u00B4", "\u00BA"),
                "\u00D7 \u00F7 \u0387 \u05BE \u05C0 \u05C3 \u05C6 \u05F3 \u05F4",
                rngstr(u"\u0600", "\u0603"),
                rngstr(u"\u0606", "\u060A"),
                "\u060C \u0614 \u061B \u061E \u066A \u066D",
                rngstr(u"\u0703", "\u070D"),
                "\u07F6 \u07F7 \u07F8 \u0964 \u0965 \u0E4F \u1FBD \u2016 \u2017",
                rngstr(u"\u2020", "\u2023"),
                rngstr(u"\u2030", "\u2038"),
                "\u203B \u2043",
                rngstr(u"\u203E", "\u2042"),
                "\u2044",
                rngstr(u"\u207A", "\u207F"),
                rngstr(u"\u208A", "\u208E"),
                rngstr(u"\u2100", "\u214F"),
                rngstr(u"\u2190", "\u21FF"),
                rngstr(u"\u2200", "\u2BFF"),
                "\u3012 \u30FB",
                rngstr(u"\uFF01", "\uFF0F"),
                rngstr(u"\uFF1A", "\uFF20"),
                rngstr(u"\uFF3B", "\uFF40"),
                rngstr(u"\uFF5B", "\uFF65"),
                "\uFF65"
            ])
        gold = string.split(u" ")

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def cp1252_bullet_tm_test(self):
        string = "\x99\x95"
        gold = ["\u2122", "\u2022"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def test_spaces(self):
        string = "\u200Bthis\u200Eis\u200Fa\uFEFFtest\tfor&nbsp;\u00A0" + \
            "\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008" + \
            "\u2009\u200A\u3000sure"
        gold = ["this", "is", "a", "test", "for", "sure"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def tokenize_nl_test(self):
        nlp.get_global_PTB_config().tokenize_newlines = True
        string = "\n word \r\n \r \u2028 \u2029 \u000B \u000C \u0085"
        gold = ["*NL*", "word", "*NL*", "*NL*", "*NL*", "*NL*", "*NL*",
                "*NL*", "*NL*"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print(token, gold_token.encode("utf-8"))
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
