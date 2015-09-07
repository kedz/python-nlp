import nlp

class Tok_Test:
    def setUp(self): 
        nlp.get_global_PTB_config().default()

    def test_plangs(self):

        string = u"C++ c++ C# c# F# f#"
        gold = [u"C++", u"c++", u"C#", u"c#", u"F#", u"f#"]

        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):
            print token, gold_token
            assert token == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims3_NO_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = False
        string = u"cannot gonna gotta lemme gimme wanna"
        gold = [u"cannot", u"gonna", u"gotta", u"lemme", u"gimme", u"wanna"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token
            assert token == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims3_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = True
        string = u"cannot gonna gotta lemme gimme wanna"
        gold = [u"can", u"not", u"gon", u"na", u"got", u"ta", u"lem", u"me",
                u"gim", u"me", u"wan", u"na"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token
            assert token == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)



    def assims2_normalize_test(self):
        nlp.get_global_PTB_config().split_assimilations = True
        string = u"'twas 'tis"
        gold = [u"'t", u"was", u"'t", u"is"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token
            assert token == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)

    def assims2_NO_normalize_test(self):

        string = u"'twas 'tis"
        gold = [u"'twas", u"'tis"]

        nlp.get_global_PTB_config().split_assimilations = False

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token
            assert token == gold_token.encode("utf-8")

        assert len(tokens) == len(gold)
                    
    def spmdash_normalize_test(self):

        nlp.get_global_PTB_config().normalize_dashes = True
        string = u"&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
        gold = [u"--", u"--", u"--", u"--", u"--", u"--",
                u"--", u"--"]
        tokens = nlp.tokenize(string)
        print tokens
        for token, gold_token in zip(tokens, gold):
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def spmdash_NO_normalize_test(self):

        nlp.get_global_PTB_config().normalize_dashes = False
        string = u"&MD; &mdash; &ndash; \u0096 \u0097 \u2013 \u2014 \u2015"
        gold = [u"&MD;", u"&mdash;", u"&ndash;", u"\u0096", u"\u0097", u"\u2013",
                u"\u2014", u"\u2015"]
        tokens = nlp.tokenize(string)
        print tokens
        for token, gold_token in zip(tokens, gold):
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def spamp_normalize_test(self):

        nlp.get_global_PTB_config().normalize_amp = True
        string = u"&amp; is not normed yet";
        gold = [u"&", u"is", u"not", u"normed", u"yet"]
        tokens = nlp.tokenize(string)
        print tokens
        for token, gold_token in zip(tokens, gold):
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
     
    def spamp_NO_normalize_test(self):

        nlp.get_global_PTB_config().normalize_amp = False
        string = u"&amp; is not normed yet";
        gold = [u"&amp;", u"is", u"not", u"normed", u"yet"]
        tokens = nlp.tokenize(string)
        print tokens
        for token, gold_token in zip(tokens, gold):
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def sppunc_test(self):
        string = u"&HT; &TL; &UR; &LR; &QC; &QL; &QR; &odq; &cdq; &#0123;" 
        gold = [u"&HT;", u"&TL;", u"&UR;", u"&LR;", u"&QC;", u"&QL;", u"&QR;",
                u"&odq;", u"&cdq;", u"&#0123;"] 
        tokens = nlp.tokenize(string)
        print tokens
        for token, gold_token in zip(tokens, gold):
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def word_redaux_test_NO_normalize_quotes(self):

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

    def word_redaux_test_UNICODE_normalize_quotes(self):
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

    def word_redaux_test_LATEX_normalize_quotes(self):
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

    def word_redaux_test_ASCII_normalize_quotes(self):
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

    def word_sredaux_test_ASCII_normalize_quotes(self):
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

    def soft_hyphen_remove_test(self):

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

      
    def apoword_test_NO_normalize_quotes(self):
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

    def apoword_test_UNICODE_normalize_quotes(self):
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

    def apoword_test_ASCII_normalize_quotes(self):
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

    def apoword_test_LATEX_normalize_quotes(self):
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

    def apoword2_test(self):
        string = u"y'all are nice y' "
        gold = [u"y'", u"all", u"are", u"nice", u"y", u"'"]    

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    #def full_or_likely_url_NO_escape_test(self):
    #    string = u"https://cs.columbia.edu http://www.google.com " + \
    #             u"www.nytimes.com/world.html nytimes.com nytimes.com/americas"
    #    gold = [u"https://cs.columbia.edu", 
    #            u"http://www.google.com",
    #            u"www.nytimes.com/world.html",
    #            u"nytimes.com", 
    #            u"nytimes.com/americas",]
    #
    #    tokens = nlp.tokenize(string)
    #    for token, gold_token in zip(tokens, gold):
    #        print token, gold_token.encode("utf-8")
    #        assert token == gold_token.encode("utf-8")
    #    assert len(tokens) == len(gold)

    #def email_test(self):
    #    string = u"<crk2130@columbia.edu> thekedz@gmail.com " + \
    #             u"christopher.r.kedzie@gmail.com &lt;chris.kedzie@outlook.com&gt;"
    #    gold = [u"<crk2130@columbia.edu>", u"thekedz@gmail.com", 
    #            u"christopher.r.kedzie@gmail.com", 
    #            u"&lt;chris.kedzie@outlook.com&gt;"]
    #
    #    tokens = nlp.tokenize(string)
    #    print tokens
    #    for token, gold_token in zip(tokens, gold):
    #        print token, gold_token.encode("utf-8")
    #        assert token == gold_token.encode("utf-8")
    #    assert len(tokens) == len(gold)
    #    print nlp.tokenize("ked zie@gmail.com")
    #    print nlp.tokenize(u"ked\u00A0zie@gmail.com".encode("utf-8"))

    def twiiter_test(self):
        string = u"@the_real_kedzie1 #nlp #cs"
        gold = [u"@the_real_kedzie1",  u"#nlp", u"#cs"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def date_test_NO_escapeing(self):
        string = u"01/29/1986 04-11-1995"
        gold = [u"01/29/1986", u"04-11-1995"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def number_test(self):
        string = u"-1234 +1\u00AD200.4 +12.98 -.33 +.02 +0.2"
        gold = [u"-1234", u"+1200.4", u"+12.98", u"-.33", u"+.02", u"+0.2"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def subsupnum_test(self):
        string = u"note\u207A\u2070\u00B9\u00B2\u00B3 \u2074 \u2075 \u2076" \
            + u" \u2080\u2081 \u2082 \u2083"
        gold = [u"note", u"\u207A\u2070\u00B9\u00B2\u00B3", u"\u2074", u"\u2075",
                u"\u2076", u"\u2080\u2081", u"\u2082", u"\u2083"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    # do fracs


    def tbspec_test(self):
        string = u"-RRB- -LRB- -RCB- -lcb- -lsb- C.D.s PRO-nouns anti-con " + \
            u"s&p-500  S&amp;p-500  S&amp;Ls  cap'n C'est" #
        gold = [u"-RRB-", u"-LRB-", u"-RCB-", u"-lcb-", u"-lsb-", u"C.D.s", 
                u"PRO-", u"nouns", u"anti-", u"con", u"s&p-500", u"S&p-500", 
                u"S&Ls", u"cap'n", u"C'est"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def bangwords_test(self):
        string = u"E! yahoo! Jeopardy! ok!\nmagazine"
        gold = [u"E!", u"yahoo!", u"Jeopardy!", u"ok!", u"magazine"]
        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    # do thing3 here
    def thing3_test_NO_escaping(self):
        assert 0

    def dolsign_test(self):
        string = u"US$ $ # UK$"
        gold = [u"US$", u"$", u"#", u"UK$"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def dolsign2_test_NO_normalize(self):
        string = u"\u00A2 \u00A3 \u00A4 \u00A5 \u0080 \u20A0 \u20AC " + \
            u"\u060B \u0E3F \u20A4 \uFFE0 \uFFE1 \uFFE5 \uFFE6"
        gold = [u"\u00A2", u"\u00A3", u"\u00A4", u"\u00A5", u"\u0080", u"\u20A0",
                u"\u20AC", u"\u060B", u"\u0E3F", u"\u20A4", u"\uFFE0", u"\uFFE1",
                u"\uFFE5", u"\uFFE6"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    def dolsign2_test_normalize(self):
        nlp.get_global_PTB_config().normalize_currency = True
        string = u"\u00A2 \u00A3 \u00A4 \u00A5 \u0080 \u20A0 \u20AC " + \
            u"\u060B \u0E3F \u20A4 \uFFE0 \uFFE1 \uFFE5 \uFFE6"
        gold = [u"cents", u"#", u"\\$", u"\u00A5", u"\\$", u"\\$", u"\\$", 
                u"\u060B", u"\u0E3F", u"\u20A4", u"\uFFE0", u"\uFFE1", u"\uFFE5",
                u"\uFFE6"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)



    #  private static final Pattern CENTS_PATTERN = Pattern.compile("\u00A2");
    #  private static final Pattern POUND_PATTERN = Pattern.compile("\u00A3");
    #  private static final Pattern GENERIC_CURRENCY_PATTERN = Pattern.compile("[\u0080\u00A4\u20A0\u20AC]");

    #  private static String normalizeCurrency(String in) {
    #    String s1 = in;
    #    s1 = CENTS_PATTERN.matcher(s1).replaceAll("cents");
    #    s1 = POUND_PATTERN.matcher(s1).replaceAll("#");  // historically used for pound in PTB3
    #    s1 = GENERIC_CURRENCY_PATTERN.matcher(s1).replaceAll("\\$");  // Euro (ECU, generic currency)  -- no good translation!
    #    return s1;
    #  }

    def thinga_NO_normalize_amp_test(self):
        nlp.get_global_PTB_config().normalize_amp = False
        string = u"ABC+NBC+CBS ABC&NBC+CBS A&amp;P"
        gold = [u"ABC+NBC+CBS", u"ABC&NBC+CBS", u"A&amp;P"]

        tokens = nlp.tokenize(string)
        print "GOLD  ", gold
        print "ACTUAL", tokens
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def thinga_normalize_amp_test(self):
        nlp.get_global_PTB_config().normalize_amp = True
        string = u"ABC&amp;NBC&CBS ABC&amp;NBC+CBS A&amp;P"
        gold = [u"ABC&NBC&CBS", u"ABC&NBC+CBS", u"A&P"]

        tokens = nlp.tokenize(string)
        print "GOLD  ", gold
        print "ACTUAL", tokens
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


       

    def right_quote_weirdness_NO_normalize_test(self):
        """Should match this pattern: '/[A-Za-z][^ \t\n\r\u00A0] but there is 
        difficulty expressing the intersection of single and double character
        negation."""

        nlp.get_global_PTB_config().normalize_quotes = None    
        string = u"'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = [u"'", u"At", u"last", u"'", u"a", u"\u00A2", 
                u"'", u"a", u"'", u"a", u"'", u"a"]

        tokens = nlp.tokenize(string)
        print "GOLD  ", gold
        print "ACTUAL", tokens
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def right_quote_weirdness_LATEX_normalize_test(self):

        nlp.get_global_PTB_config().normalize_quotes = u"latex"
        string = u"'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = [u"`", u"At", u"last", u"`", u"a", u"\u00A2", 
                u"'", u"a", u"'", u"a", u"'", u"a"]

        tokens = nlp.tokenize(string)
        print "GOLD  ", gold
        print "ACTUAL", tokens
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def right_quote_weirdness_UNICODE_normalize_test(self):

        nlp.get_global_PTB_config().normalize_quotes = u"unicode"
        string = u"'At last 'a\u00A2 'a\n 'a 'a\u00A0"
        gold = [u"\u2018", u"At", u"last", u"\u2018", u"a", u"\u00A2", 
                u"\u2019", u"a", u"\u2019", u"a", u"\u2019", u"a"]

        tokens = nlp.tokenize(string)
        print "GOLD  ", gold
        print "ACTUAL", tokens
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def terminal_redaux_test(self):
        nlp.get_global_PTB_config().normalize_quotes = None
        string = u"test ends with you're"
        gold = [u"test", u"ends", u"with", u"you", u"'re"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def terminal_sredaux_test(self):
        string = u"test ends with wouldn't"
        gold = [u"test", u"ends", u"with", u"would", u"n't"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def quotes_test(self):
        raise Exception("IMPLEMENT ME!!!")

    def test_fake_duckfeet(self):
        string = u"duck<<feet >>"
        gold = [u"duck", u"<<", u"feet", u">>"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def test_misc_symbols(self):
        def rngstr(uni1, uni2):
            return u" ".join(unichr(i) for i in xrange(ord(uni1), ord(uni2) + 1))
        string = u" ".join(
            [
                u"+ % & ~ ^ | \\ \u00A6 \u00A7 \u00A8 \u00A9 \u00AC \u00AE \u00AF",
                rngstr(u"\u00B0", u"\u00B3"),
                rngstr(u"\u00B4", u"\u00BA"),
                u"\u00D7 \u00F7 \u0387 \u05BE \u05C0 \u05C3 \u05C6 \u05F3 \u05F4",
                rngstr(u"\u0600", u"\u0603"),
                rngstr(u"\u0606", u"\u060A"),
                u"\u060C \u0614 \u061B \u061E \u066A \u066D",
                rngstr(u"\u0703", u"\u070D"),
                u"\u07F6 \u07F7 \u07F8 \u0964 \u0965 \u0E4F \u1FBD \u2016 \u2017",
                rngstr(u"\u2020", u"\u2023"),
                rngstr(u"\u2030", u"\u2038"),
                u"\u203B \u2043",
                rngstr(u"\u203E", u"\u2042"),
                u"\u2044",
                rngstr(u"\u207A", u"\u207F"),
                rngstr(u"\u208A", u"\u208E"),
                rngstr(u"\u2100", u"\u214F"),
                rngstr(u"\u2190", u"\u21FF"),
                rngstr(u"\u2200", u"\u2BFF"),
                u"\u3012 \u30FB",
                rngstr(u"\uFF01", u"\uFF0F"),
                rngstr(u"\uFF1A", u"\uFF20"),
                rngstr(u"\uFF3B", u"\uFF40"),
                rngstr(u"\uFF5B", u"\uFF65"),
                u"\uFF65"
            ])
        gold = string.split(u" ")

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def cp1252_bullet_tm_test(self):
        string = u"\x99\x95"
        gold = [u"\u2122", u"\u2022"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def test_spaces(self):
        string = u"\u200Bthis\u200Eis\u200Fa\uFEFFtest\tfor&nbsp;\u00A0" + \
            u"\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008" + \
            u"\u2009\u200A\u3000sure"
        gold = [u"this", u"is", u"a", u"test", u"for", u"sure"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def tokenize_nl_test(self):
        nlp.get_global_PTB_config().tokenize_newlines = True
        string = u"\n word \r\n \r \u2028 \u2029 \u000B \u000C \u0085"
        gold = [u"*NL*", u"word", u"*NL*", u"*NL*", u"*NL*", u"*NL*", u"*NL*",
                u"*NL*", u"*NL*"]

        tokens = nlp.tokenize(string)
        for token, gold_token in zip(tokens, gold):
            print token, gold_token.encode("utf-8")
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
