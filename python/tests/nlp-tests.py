# coding=utf-8
from __future__ import (absolute_import, division, print_function,
    unicode_literals)

import nlp

class PTB_Tokenizer_Test:

    def setUp(self): 
        nlp.get_global_PTB_config().default()

    def ptb_inputs_test1(self):
        string = "This is a sentence."
        gold = ["This", "is", "a", "sentence", "."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test2(self):
        string = "U.S. insurance: Conseco acquires Kemper Corp. \n" \
                 "</HEADLINE>\n<P>\nU.S insurance"
        gold = ["U.S.", "insurance", ":", "Conseco", "acquires", 
                "Kemper", "Corp.", ".", "</HEADLINE>", "<P>", "U.S", 
                "insurance"]        
        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)
        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test3(self):
        string = "Based in Eugene,Ore., PakTech needs a new distributor " \
                 "after Sydney-based Creative Pack Pty. Ltd. went into " \
                 "voluntary administration."
        gold = ["Based", "in", "Eugene", ",", "Ore.", ",", "PakTech", 
                "needs", "a", "new", "distributor", "after",
                "Sydney-based", "Creative", "Pack", "Pty.", "Ltd.",
                "went", "into", "voluntary", "administration", "."]

        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)
    def ptb_inputs_test4(self):
        string = "The Iron Age (ca. 1300 – ca. 300 BC)."
        gold = ["The", "Iron", "Age", "-LRB-", "ca.", "1300", "--", 
                "ca.", "300", "BC", "-RRB-", "."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test5(self):
        string = "Indo\u00ADnesian ship\u00ADping \u00AD"
        gold = ["Indonesian", "shipping", "-"]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test6(self):
        string = "Gimme a phone, I'm gonna call."
        gold = ["Gim", "me", "a", "phone", ",", "I", "'m", "gon", 
                "na", "call", "."]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test7(self):
        string = "\"John & Mary's dog,\" Jane thought (to herself).\n\"" \
                 "What a #$%!\na- ``I like AT&T''.\""
        gold = ["``", "John", "&", "Mary", "'s", "dog", ",", "''", 
                "Jane", "thought", "-LRB-", "to", "herself", "-RRB-",
                ".", "``", "What", "a", "#", "$", "%", "!", "a", 
                "-", "``", "I", "like", "AT&T", "''", ".", "''" ]     
        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)


        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def ptb_inputs_test8(self):
        string = "I said at 4:45pm."
        gold = ["I", "said", "at", "4:45", "pm", "."]        
        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)


    def ptb_inputs_test9(self):
        string = "I can't believe they wanna keep 40% of that.\"\n``" \
                 "Whatcha think?''\n\"I don't --- think so...,\""
        gold = ["I", "ca", "n't", "believe", "they", "wan", "na", 
                "keep", "40", "%", "of", "that", ".", "''",
                "``", "Whatcha", "think", "?", "''", "``", "I", "do",
                "n't", "--", "think", "so", "...", ",", "''" ]        
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test10(self):
        string = "You `paid' US$170,000?!\nYou should've paid only$16.75."
        gold = ["You", "`", "paid", "'", "US$", "170,000", "?!", "You",
                "should", "'ve", "paid", "only", "$", "16.75", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test11(self):
        string = "1. Buy a new Chevrolet (37%-owned in the U.S..) . 15%"
        gold = ["1", ".", "Buy", "a", "new", "Chevrolet", "-LRB-",
                "37", "%", "-", "owned", "in", "the", "U.S.", ".",
                "-RRB-", ".", "15", "%"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test12(self):
        string = "I like you ;-) but do you care :(. I'm happy ^_^ but " \
                 "shy (x.x)!"
        gold = ["I", "like", "you", ";--RRB-", "but", "do", "you",
                "care",  ":-LRB-", ".", "I", "'m", "happy", "^_^", 
                "but", "shy", "-LRB-x.x-RRB-", "!"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test13(self):
        string = "Diamond (``Not even the chair'') lives near Udaipur " \
                 "(84km). {1. A potential Palmer trade:}"
        gold = ["Diamond", "-LRB-", "``", "Not", "even", "the", "chair",
                "''", "-RRB-", "lives", "near", "Udaipur", "-LRB-", 
                "84km", "-RRB-", ".", "-LCB-", "1", ".", "A", 
                "potential", "Palmer", "trade", ":", "-RCB-"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test14(self):
        string = "No. I like No. 24 and no.47."
        gold = ["No", ".", "I", "like", "No.", "24", "and", "no.", 
                "47", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test15(self):
        string = "You can get a B.S. or a B. A. or a Ph.D (sometimes a " \
                 "Ph. D) from Stanford."
        gold = ["You", "can", "get", "a", "B.S.", "or", "a", "B.", 
                "A.", "or", "a", "Ph.D", "-LRB-", "sometimes", "a", 
                "Ph.", "D", "-RRB-", "from", "Stanford", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test16(self):
        string = "@Harry_Styles didn`t like Mu`ammar al-Qaddafi"
        gold = ["@Harry_Styles", "did", "n`t", "like", "Mu`ammar", 
                "al-Qaddafi"]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test17(self):
        string = "Kenneth liked Windows 3.1, Windows 3.x, and Mesa A.B " \
                 "as I remember things."
        gold = ["Kenneth", "liked", "Windows", "3.1", ",", "Windows",
                "3.x", ",", "and", "Mesa", "A.B", "as", "I", 
                "remember", "things", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test18(self):
        string = "I like programming in F# more than C#."
        gold = ["I", "like", "programming", "in", "F#", "more", "than",
                "C#", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test19(self):
        string = "NBC Live will be available free through the Yahoo! Chat " \
                 "Web site. E! Entertainment said ``Jeopardy!'' is a game " \
                 "show."
        gold = ["NBC", "Live", "will", "be", "available", "free", 
                "through", "the", "Yahoo!", "Chat", "Web", "site", ".",
                "E!", "Entertainment", "said", "``", "Jeopardy!", "''",
                "is", "a", "game", "show", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test20(self):
        string = "I lived in O\u2019Malley and read OK! Magazine."
        gold = ["I", "lived", "in", "O'Malley", "and", "read", "OK!",
                "Magazine", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test21(self):
        string = "I lived in O\u0092Malley and read OK! Magazine."
        # /* invalid unicode codepoint, but inherit from cp1252 */
        gold = ["I", "lived", "in", "O'Malley", "and", "read", "OK!",
                "Magazine", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test22(self):
        string = "I like: \u2022wine, \u0095cheese, \u2023salami, & " \
                 "\u2043speck."
        gold = ["I", "like", ":", "\u2022", "wine", ",", "\u2022",
                "cheese", ",", "\u2023", "salami", ",", "&", "\u2043",
                "speck", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test23(self):
        string = "I don't give a f**k about your sh*tty life."
        gold = ["I", "do", "n't", "give", "a", "f", "**", "k", 
                "about", "your", "sh", "*", "tty", "life", "."]
        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test24(self):
        string = "First sentence.... Second sentence."
        # The tests that come with corenlp state that ". . . . Second" should
        # be "...", ".", "Second". However, the actual CoreNLP tokenizer
        # and our tokenizer produce "...", "Second" so I am going with that.
        gold = ["First", "sentence", "...", "Second", "sentence", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test25(self):
        string = "First sentence . . . . Second sentence."
        # The tests that come with corenlp state that ". . . . Second" should
        # be "...", ".", "Second". However, the actual CoreNLP tokenizer
        # and our tokenizer produce "...", "Second" so I am going with that.
        gold = ["First", "sentence", "...", "Second", "sentence", "."]
        tokens = nlp.tokenize(string)
        print("SYSTEM:", tokens)
        print("GOLD  :", gold)
        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

    def ptb_inputs_test26(self):
        string = "I wasn’t really ... well, what I mean...see . . . " \
                 "what I'm saying, the thing is . . . I didn’t mean it."
        gold = ["I", "was", "n't", "really", "...", "well", ",", 
                "what", "I", "mean", "...", "see", "...", "what", "I",
                "'m", "saying", ",", "the", "thing", "is", "...", "I",
                "did", "n't", "mean", "it", "."]
        tokens = nlp.tokenize(string)

        for token, gold_token in zip(tokens, gold):        
            assert bytes(token) == gold_token.encode("utf-8")
        assert len(tokens) == len(gold)

#


def tokenize_simple_test_1():
    string = "test"
    tokens = nlp.tokenize(string)
    assert len(tokens) == 1
    assert bytes(tokens[0]) == "test".encode("utf-8")

def tokenize_simple_test_2():
    string = "this is a simple test"
    gold = ["this", "is", "a", "simple", "test"]
    tokens = nlp.tokenize(string)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_1_no_normalize():
    nlp.get_global_PTB_config().normalize_parentheses = False
    nlp.get_global_PTB_config().normalize_brackets = False
    sent1 = "Significant improvements in peak FEV1 were demonstrated " \
            "with tiotropium/olodaterol 5/2 \u03BCg (p = 0.008), 5/5 \u03BCg " \
            "(p = 0.012), and 5/10 \u03BCg (p < 0.0001) versus tiotropium " \
            "monotherapy [51]."
    gold = ["Significant", "improvements", "in", "peak", "FEV1", "were",
            "demonstrated", "with", "tiotropium/olodaterol", "5/2", "\u03BCg",
            "(", "p", "=", "0.008", ")", ",", "5/5", "\u03BCg", 
            "(", "p", "=", "0.012", ")", ",", "and", "5/10", 
            "\u03BCg", "(", "p", "<", "0.0001", ")", "versus", 
            "tiotropium", "monotherapy", "[", "51", "]", "."]

    tokens = nlp.tokenize(sent1)
    #assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        print(token, gold_token.encode("utf-8"))
        assert bytes(token) == gold_token.encode("utf-8")


def tokenize_sgml_test_2_no_normalize():
    nlp.get_global_PTB_config().strict_ptb3 = False
    sent2 = "Panasonic brand products are produced by Samsung Electronics " \
            "Co. Ltd. Sanyo products aren't."
    gold = ["Panasonic", "brand", "products", "are", "produced", "by", 
            "Samsung", "Electronics", "Co.", "Ltd.", ".", "Sanyo", 
            "products", "are", "n't", "."]

    tokens = nlp.tokenize(sent2)
    print(tokens)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def tokenize_sgml_test_3_no_normalize():
    nlp.get_global_PTB_config().normalize_parentheses = False
    sent3 = "Oesophageal acid exposure (% time <pH 4) was similar in " \
            "patients with or without complications (19.2% v 19.3% p>0.05)."

    gold = ["Oesophageal", "acid", "exposure", "(", "%", "time", 
            "<", "pH", "4", ")", "was", "similar", "in",
            "patients", "with", "or", "without", "complications", 
            "(", "19.2", "%", "v", "19.3", "%",
            "p", ">", "0.05", ")", "."]

    tokens = nlp.tokenize(sent3)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_4_normalize():
    nlp.get_global_PTB_config().normalize_spaces = True
    sent4 = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
            "\"http://www.w3.org/TR/html4/strict.dtd\">"

    gold = [
        "<!DOCTYPE\u00A0html\u00A0PUBLIC\u00A0\"-//W3C//DTD\u00A0HTML" \
        "\u00A04.01\u00A0Strict//EN\"\u00A0" \
        "\"http://www.w3.org/TR/html4/strict.dtd\">"] 
        # spaces go to &nbsp; \u00A0

    tokens = nlp.tokenize(sent4)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")



def tokenize_sgml_test_4_no_normalize():
    nlp.get_global_PTB_config().normalize_spaces = False
    sent4 = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
            "\"http://www.w3.org/TR/html4/strict.dtd\">"

    gold = [
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Strict//EN\" " \
        "\"http://www.w3.org/TR/html4/strict.dtd\">"] 
        # spaces go to &nbsp; \u00A0

    tokens = nlp.tokenize(sent4)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_5_no_normalize():
    sent5 = "Hi! <foo bar=\"baz xy = foo !$*) 422\" > <?PITarget " \
            "PIContent?> <?PITarget PIContent> Hi!" 

    gold = ["Hi", "!", "<foo bar=\"baz xy = foo !$*) 422\" >", 
            "<?PITarget PIContent?>", "<?PITarget PIContent>", "Hi", "!"]
    tokens = nlp.tokenize(sent5)
    print(tokens)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)
    
def tokenize_sgml_test_6_no_space_normalize():
    sent6 = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n<?xml-stylesheet " \
            "type=\"text/xsl\" href=\"style.xsl\"?>\n<book " \
            "xml:id=\"simple_book\" " \
            "xmlns=\"http://docbook.org/ns/docbook\" version=\"5.0\">\n"

    gold = ["<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", 
            "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>",
            "<book xml:id=\"simple_book\" " \
            "xmlns=\"http://docbook.org/ns/docbook\" version=\"5.0\">"]
                                         
    tokens = nlp.tokenize(sent6)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_7_no_normalize():
    sent7 = "<chapter xml:id=\"chapter_1\"><?php echo $a; ?>\n<!-- This " \
            "is an SGML/XML comment \"Hi!\" -->\n<p> </p> <p-fix / >"

    gold = ["<chapter xml:id=\"chapter_1\">", "<?php echo $a; ?>", 
            "<!-- This is an SGML/XML comment \"Hi!\" -->",
            "<p>", "</p>", "<p-fix / >"]
                            
    tokens = nlp.tokenize(sent7)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_8_no_normalize():
    nlp.get_global_PTB_config().escape_forward_slash_asterisk = False
    sent8 = "<a href=\"http:\\\\it's\\here\"> <quote orig_author='some " \
            "\"dude'/> <not sgmltag"
      
    gold = ["<a href=\"http:\\\\it's\\here\">", 
            "<quote orig_author='some \"dude'/>", "<", "not", "sgmltag"]
          
    tokens = nlp.tokenize(sent8)
    print(tokens)
    print(gold)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_9_no_normalize():
    sent9 = "<quote previouspost=\"\n" \
            "&gt; &gt; I really don't want to process this junk.\n" \
            "&gt; No one said you did, runny.  What's got you so scared, " \
            "anyway?-\n\">"

    gold = ["<quote previouspost=\"\n" \
            "&gt; &gt; I really don't want to process this junk.\n" \
            "&gt; No one said you did, runny.  What's got you so " \
            "scared, anyway?-\n\">"]

    tokens = nlp.tokenize(sent9)
    print(tokens)
    print(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")
    assert len(tokens) == len(gold)

def tokenize_sgml_test_10_no_normalize():
    sent10 = "&lt;b...@canada.com&gt; funky@thedismalscience.net " \
             "<myemail@where.com>"

    gold = ["&lt;b...@canada.com&gt;", "funky@thedismalscience.net", 
            "<myemail@where.com>"]

    tokens = nlp.tokenize(sent10)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")

def tokenize_sgml_test_11_no_normalize():
    sent11 = "<DOC> <DOCID> nyt960102.0516 </DOCID><STORYID cat=w " \
             "pri=u> A0264 </STORYID> <SLUG fv=ttj-z> " 
             # this is a MUC7 document 

    gold = ["<DOC>", "<DOCID>", "nyt960102", ".0516", "</DOCID>", 
            "<STORYID cat=w pri=u>", "A0264", "</STORYID>", 
            "<SLUG fv=ttj-z>"]

    tokens = nlp.tokenize(sent11)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert bytes(token) == gold_token.encode("utf-8")
