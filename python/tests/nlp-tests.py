# coding=utf-8

import nlp



class PTB_Tokenizer_Test:

    def setUp(self): 
        nlp.get_global_PTB_config().default()

    def ptb_inputs_test1(self):
        string = u"This is a sentence."
        gold = [u"This", u"is", u"a", u"sentence", u"."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test2(self):
        string = u"U.S. insurance: Conseco acquires Kemper Corp. \n" \
                 u"</HEADLINE>\n<P>\nU.S insurance"
        gold = [u"U.S.", u"insurance", u":", u"Conseco", u"acquires", 
                u"Kemper", u"Corp.", u".", u"</HEADLINE>", u"<P>", u"U.S", 
                u"insurance"]        
        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold
        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test3(self):
        string = u"Based in Eugene,Ore., PakTech needs a new distributor " \
                 u"after Sydney-based Creative Pack Pty. Ltd. went into " \
                 u"voluntary administration."
        gold = [u"Based", u"in", u"Eugene", u",", u"Ore.", u",", u"PakTech", 
                u"needs", u"a", u"new", u"distributor", u"after",
                u"Sydney-based", u"Creative", u"Pack", u"Pty.", u"Ltd.",
                u"went", u"into", u"voluntary", u"administration", u"."]

        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
    def ptb_inputs_test4(self):
        string = u"The Iron Age (ca. 1300 – ca. 300 BC)."
        gold = [u"The", u"Iron", u"Age", u"-LRB-", u"ca.", u"1300", u"--", 
                u"ca.", u"300", u"BC", u"-RRB-", u"."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test5(self):
        string = u"Indo\u00ADnesian ship\u00ADping \u00AD"
        gold = [u"Indonesian", u"shipping", u"-"]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test6(self):
        string = u"Gimme a phone, I'm gonna call."
        gold = [u"Gim", u"me", u"a", u"phone", u",", u"I", u"'m", u"gon", 
                u"na", u"call", u"."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test7(self):
        string = u"\"John & Mary's dog,\" Jane thought (to herself).\n\"" \
                 u"What a #$%!\na- ``I like AT&T''.\""
        gold = [u"``", u"John", u"&", u"Mary", u"'s", u"dog", u",", u"''", 
                u"Jane", u"thought", u"-LRB-", u"to", u"herself", u"-RRB-",
                u".", u"``", u"What", u"a", u"#", u"$", u"%", u"!", u"a", 
                u"-", u"``", u"I", u"like", u"AT&T", u"''", u".", u"''" ]     
        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold


        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def ptb_inputs_test8(self):
        string = u"I said at 4:45pm."
        gold = [u"I", u"said", u"at", u"4:45", u"pm", u"."]        
        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def ptb_inputs_test9(self):
        string = u"I can't believe they wanna keep 40% of that.\"\n``" \
                 u"Whatcha think?''\n\"I don't --- think so...,\""
        gold = [u"I", u"ca", u"n't", u"believe", u"they", u"wan", u"na", 
                u"keep", u"40", u"%", u"of", u"that", u".", u"''",
                u"``", u"Whatcha", u"think", u"?", u"''", u"``", u"I", u"do",
                u"n't", u"--", u"think", u"so", u"...", u",", u"''" ]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test10(self):
        string = u"You `paid' US$170,000?!\nYou should've paid only$16.75."
        gold = [u"You", u"`", u"paid", u"'", u"US$", u"170,000", u"?!", u"You",
                u"should", u"'ve", u"paid", u"only", u"$", u"16.75", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test11(self):
        string = u"1. Buy a new Chevrolet (37%-owned in the U.S..) . 15%"
        gold = [u"1", u".", u"Buy", u"a", u"new", u"Chevrolet", u"-LRB-",
                u"37", u"%", u"-", u"owned", u"in", u"the", u"U.S.", u".",
                u"-RRB-", u".", u"15", u"%"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test12(self):
        string = u"I like you ;-) but do you care :(. I'm happy ^_^ but " \
                 u"shy (x.x)!"
        gold = [u"I", u"like", u"you", u";--RRB-", u"but", u"do", u"you",
                u"care",  u":-LRB-", u".", u"I", u"'m", u"happy", u"^_^", 
                u"but", u"shy", u"-LRB-x.x-RRB-", u"!"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test13(self):
        string = u"Diamond (``Not even the chair'') lives near Udaipur " \
                 u"(84km). {1. A potential Palmer trade:}"
        gold = [u"Diamond", u"-LRB-", u"``", u"Not", u"even", u"the", u"chair",
                u"''", u"-RRB-", u"lives", u"near", u"Udaipur", u"-LRB-", 
                u"84km", u"-RRB-", u".", u"-LCB-", u"1", u".", u"A", 
                u"potential", u"Palmer", u"trade", u":", u"-RCB-"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test14(self):
        string = u"No. I like No. 24 and no.47."
        gold = [u"No", u".", u"I", u"like", u"No.", u"24", u"and", u"no.", 
                u"47", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test15(self):
        string = u"You can get a B.S. or a B. A. or a Ph.D (sometimes a " \
                 u"Ph. D) from Stanford."
        gold = [u"You", u"can", u"get", u"a", u"B.S.", u"or", u"a", u"B.", 
                u"A.", u"or", u"a", u"Ph.D", u"-LRB-", u"sometimes", u"a", 
                u"Ph.", u"D", u"-RRB-", u"from", u"Stanford", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test16(self):
        string = u"@Harry_Styles didn`t like Mu`ammar al-Qaddafi"
        gold = [u"@Harry_Styles", u"did", u"n`t", u"like", u"Mu`ammar", 
                u"al-Qaddafi"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test17(self):
        string = u"Kenneth liked Windows 3.1, Windows 3.x, and Mesa A.B " \
                 u"as I remember things."
        gold = [u"Kenneth", u"liked", u"Windows", u"3.1", u",", u"Windows",
                u"3.x", u",", u"and", u"Mesa", u"A.B", u"as", u"I", 
                u"remember", u"things", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test18(self):
        string = u"I like programming in F# more than C#."
        gold = [u"I", u"like", u"programming", u"in", u"F#", u"more", u"than",
                u"C#", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test19(self):
        string = u"NBC Live will be available free through the Yahoo! Chat " \
                 u"Web site. E! Entertainment said ``Jeopardy!'' is a game " \
                 u"show."
        gold = [u"NBC", u"Live", u"will", u"be", u"available", u"free", 
                u"through", u"the", u"Yahoo!", u"Chat", u"Web", u"site", u".",
                u"E!", u"Entertainment", u"said", u"``", u"Jeopardy!", u"''",
                u"is", u"a", u"game", u"show", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test20(self):
        string = u"I lived in O\u2019Malley and read OK! Magazine."
        gold = [u"I", u"lived", u"in", u"O'Malley", u"and", u"read", u"OK!",
                u"Magazine", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test21(self):
        string = u"I lived in O\u0092Malley and read OK! Magazine."
        # /* invalid unicode codepoint, but inherit from cp1252 */
        gold = [u"I", u"lived", u"in", u"O'Malley", u"and", u"read", u"OK!",
                u"Magazine", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test22(self):
        string = u"I like: \u2022wine, \u0095cheese, \u2023salami, & " \
                 u"\u2043speck."
        gold = [u"I", u"like", u":", u"\u2022", u"wine", u",", u"\u2022",
                u"cheese", u",", u"\u2023", u"salami", u",", u"&", u"\u2043",
                u"speck", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test23(self):
        string = u"I don't give a f**k about your sh*tty life."
        gold = [u"I", u"do", u"n't", u"give", u"a", u"f**k", u"about", u"your",
                u"sh*tty", u"life", u"."]
        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test24(self):
        string = u"First sentence.... Second sentence."
        # The tests that come with corenlp state that ". . . . Second" should
        # be "...", ".", "Second". However, the actual CoreNLP tokenizer
        # and our tokenizer produce "...", "Second" so I am going with that.
        gold = [u"First", u"sentence", u"...", u"Second", u"sentence", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test25(self):
        string = u"First sentence . . . . Second sentence."
        # The tests that come with corenlp state that ". . . . Second" should
        # be "...", ".", "Second". However, the actual CoreNLP tokenizer
        # and our tokenizer produce "...", "Second" so I am going with that.
        gold = [u"First", u"sentence", u"...", u"Second", u"sentence", u"."]
        tokens = nlp.tokenize(string)
        print "SYSTEM:", tokens
        print "GOLD  :", gold
        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test26(self):
        string = u"I wasn’t really ... well, what I mean...see . . . " \
                 u"what I'm saying, the thing is . . . I didn’t mean it."
        gold = [u"I", u"was", u"n't", u"really", u"...", u"well", u",", 
                u"what", u"I", u"mean", u"...", u"see", u"...", u"what", u"I",
                u"'m", u"saying", u",", u"the", u"thing", u"is", u"...", u"I",
                u"did", u"n't", u"mean", u"it", u"."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert token == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

#


def tokenize_simple_test_1():
    string = u"test"
    tokens = nlp.tokenize(string)
    assert len(tokens) == 1
    assert tokens[0] == u"test"

def tokenize_simple_test_2():
    string = u"this is a simple test"
    gold = [u"this", u"is", u"a", u"simple", u"test"]
    tokens = nlp.tokenize(string)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

#def tokenize_sgml_test_1_no_normalize():
#    sent1 = u"Significant improvements in peak FEV1 were demonstrated " \
#            u"with tiotropium/olodaterol 5/2 μg (p = 0.008), 5/5 μg " \
#            u"(p = 0.012), and 5/10 μg (p < 0.0001) versus tiotropium " \
#            u"monotherapy [51]."
#    gold = [u"Significant", u"improvements", u"in", u"peak", u"FEV1", u"were",
#            u"demonstrated", u"with", u"tiotropium/olodaterol", u"5/2", u"μg",
#            u"(", u"p", u"=", u"0.008", u")", u",", u"5/5", u"μg", 
#            u"(", u"p", u"=", u"0.012", u")", u",", u"and", u"5/10", 
#            u"μg", u"(", u"p", u"<", u"0.0001", u")", u"versus", 
#            u"tiotropium", u"monotherapy", u"[", u"51", u"]", u"."]
#
#    tokens = nlp.tokenize(sent1)
#    #assert len(tokens) == len(gold)
#    for token, gold_token in zip(tokens, gold):
#        print token, gold_token
#        assert token == gold_token.encode("utf-8")


def tokenize_sgml_test_2_no_normalize():
    nlp.get_global_PTB_config().strict_ptb3 = False
    sent2 = "Panasonic brand products are produced by Samsung Electronics " \
            "Co. Ltd. Sanyo products aren't."
    gold = [u"Panasonic", u"brand", u"products", u"are", u"produced", u"by", 
            u"Samsung", u"Electronics", u"Co.", u"Ltd.", u".", u"Sanyo", 
            u"products", u"are", u"n't", u"."]

    tokens = nlp.tokenize(sent2)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token
    assert len(tokens) == len(gold)

def tokenize_sgml_test_3_no_normalize():
    nlp.get_global_PTB_config().normalize_parentheses = False
    sent3 = "Oesophageal acid exposure (% time <pH 4) was similar in " \
            "patients with or without complications (19.2% v 19.3% p>0.05)."

    gold = [u"Oesophageal", u"acid", u"exposure", u"(", u"%", u"time", 
            u"<", u"pH", u"4", u")", u"was", u"similar", u"in",
            u"patients", u"with", u"or", u"without", u"complications", 
            u"(", u"19.2", u"%", u"v", u"19.3", u"%",
            u"p", u">", u"0.05", u")", u"."]

    tokens = nlp.tokenize(sent3)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_4_normalize():
    nlp.get_global_PTB_config().normalize_spaces = True
    sent4 = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
            "\"http://www.w3.org/TR/html4/strict.dtd\">"

    gold = [
        u"<!DOCTYPE\u00A0html\u00A0PUBLIC\u00A0\"-//W3C//DTD\u00A0HTML" \
        u"\u00A04.01\u00A0Strict//EN\"\u00A0" \
        u"\"http://www.w3.org/TR/html4/strict.dtd\">"] 
        # spaces go to &nbsp; \u00A0

    tokens = nlp.tokenize(sent4)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")



def tokenize_sgml_test_4_no_normalize():
    nlp.get_global_PTB_config().normalize_spaces = False
    sent4 = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
            "\"http://www.w3.org/TR/html4/strict.dtd\">"

    gold = [
        u"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
        u"\"http://www.w3.org/TR/html4/strict.dtd\">"] 
        # spaces go to &nbsp; \u00A0

    tokens = nlp.tokenize(sent4)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_5_no_normalize():
    sent5 = "Hi! <foo bar=\"baz xy = foo !$*) 422\" > <?PITarget " \
            "PIContent?> <?PITarget PIContent> Hi!" 

    gold = [u"Hi", u"!", u"<foo bar=\"baz xy = foo !$*) 422\" >", 
            u"<?PITarget PIContent?>", u"<?PITarget PIContent>", u"Hi", u"!"]
    tokens = nlp.tokenize(sent5)
    print tokens
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token
    assert len(tokens) == len(gold)
    
def tokenize_sgml_test_6_no_space_normalize():
    sent6 = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<?xml-stylesheet " \
            "type=\"text/xsl\" href=\"style.xsl\"?>\n<book " \
            "xml:id=\"simple_book\" " \
            "xmlns=\"http://docbook.org/ns/docbook\" version=\"5.0\">\n"

    gold = [u"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", 
            u"<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>",
            u"<book xml:id=\"simple_book\" " \
            u"xmlns=\"http://docbook.org/ns/docbook\" version=\"5.0\">"]
                                         
    tokens = nlp.tokenize(sent6)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_7_no_normalize():
    sent7 = "<chapter xml:id=\"chapter_1\"><?php echo $a; ?>\n<!-- This " \
            "is an SGML/XML comment \"Hi!\" -->\n<p> </p> <p-fix / >"

    gold = [u"<chapter xml:id=\"chapter_1\">", u"<?php echo $a; ?>", 
            u"<!-- This is an SGML/XML comment \"Hi!\" -->",
            u"<p>", u"</p>", u"<p-fix / >"]
                            
    tokens = nlp.tokenize(sent7)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_8_no_normalize():
    nlp.get_global_PTB_config().escape_forward_slash_asterisk = False
    sent8 = "<a href=\"http:\\\\it's\\here\"> <quote orig_author='some " \
            "\"dude'/> <not sgmltag"
      
    gold = [u"<a href=\"http:\\\\it's\\here\">", 
            u"<quote orig_author='some \"dude'/>", u"<", u"not", u"sgmltag"]
          
    tokens = nlp.tokenize(sent8)
    print tokens
    print gold
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")

def tokenize_sgml_test_9_no_normalize():
    sent9 = "<quote previouspost=\"\n" \
            "&gt; &gt; I really don't want to process this junk.\n" \
            "&gt; No one said you did, runny.  What's got you so scared, " \
            "anyway?-\n\">"

    gold = [u"<quote previouspost=\"\n" \
            u"&gt; &gt; I really don't want to process this junk.\n" \
            u"&gt; No one said you did, runny.  What's got you so " \
            u"scared, anyway?-\n\">"]

    tokens = nlp.tokenize(sent9)
    print tokens
    print gold
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def tokenize_sgml_test_10_no_normalize():
    sent10 = "&lt;b...@canada.com&gt; funky@thedismalscience.net " \
             "<myemail@where.com>"

    gold = [u"&lt;b...@canada.com&gt;", u"funky@thedismalscience.net", 
            u"<myemail@where.com>"]

    tokens = nlp.tokenize(sent10)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_11_no_normalize():
    sent11 = "<DOC> <DOCID> nyt960102.0516 </DOCID><STORYID cat=w " \
             "pri=u> A0264 </STORYID> <SLUG fv=ttj-z> " 
             # this is a MUC7 document 

    gold = [u"<DOC>", u"<DOCID>", u"nyt960102", u".0516", u"</DOCID>", 
            u"<STORYID cat=w pri=u>", u"A0264", u"</STORYID>", 
            u"<SLUG fv=ttj-z>"]

    tokens = nlp.tokenize(sent11)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token
