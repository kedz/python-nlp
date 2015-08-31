# coding=utf-8

import nlp


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


def tokenize_sgml_test_4_no_normalize():
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
    sent8 = "<a href=\"http:\\\\it's\\here\"> <quote orig_author='some " \
            "\"dude'/> <not sgmltag"
      
    gold = [u"<a href=\"http:\\\\it's\\here\">", 
            u"<quote orig_author='some \"dude'/>", u"<", u"not", u"sgmltag"]
          
    tokens = nlp.tokenize(sent8)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

def tokenize_sgml_test_9_no_normalize():
    sent9 = "<quote previouspost=\"\n" \
            "&gt; &gt; I really don't want to process this junk.\n" \
            "&gt; No one said you did, runny.  What's got you so scared, " \
            "anyway?-\n\">"

    gold = [u"<quote previouspost=\"\n" \
            u"&gt; &gt; I really don't want to process this junk.\n" \
            u"&gt; No one said you did, runny.  What's got you so " \
            u"scared, anyway?-\n\">"]

    tokens = nlp.tokenize(sent9)
    assert len(tokens) == len(gold)
    for token, gold_token in zip(tokens, gold):
        assert token == gold_token

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
