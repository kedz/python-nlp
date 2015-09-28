import nlp


def no_split_test():
    string = "This should only be one sentence."
    gold = ["This should only be one sentence."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def two_per_test():
    string = "This should be two sentences.  There is a split."
    gold = ["This should be two sentences.", "There is a split."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def two_exc_test():
    string = "This should be two sentences!  There is a split."
    gold = ["This should be two sentences!", "There is a split."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def two_ques_test():
    string = "This should be two sentences?  There is a split."
    gold = ["This should be two sentences?", "There is a split."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def two_long_test():
    string = "This should be two sentences!!!?!!  There is a split."
    gold = ["This should be two sentences!!!?!!", "There is a split."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def two_incomplete_test():
    string = "This should be two sentences.  Second one incomplete"
    gold = ["This should be two sentences.", "Second one incomplete"]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def one_incomplete_test():
    string = "One incomplete sentence"
    gold = ["One incomplete sentence"]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def parens_quotes_test():
    string = "(Break after a parenthesis.)  (Or after \"quoted stuff!\")"
    gold = ["(Break after a parenthesis.)", "(Or after \"quoted stuff!\")"]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        print(sent)
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)
    
def nothing_test():
    string = "  "
    gold = []

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def newline_test():
    string = "This should be\n one sentence."
    gold = ["This should be\n one sentence."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def funny_test():
    string = "'') Funny stuff joined on."
    gold = ["'') Funny stuff joined on."]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

def mr_test():
    string = "Mr. White got a loaf of bread"
    gold = ["Mr. White got a loaf of bread"]

    doc = nlp.sent_tokenize(string)
    sents = [s for s in doc.sents()]

    for sent, gold_sent in zip(sents, gold):
        assert str(sent) == str(gold_sent)
    assert len(sents) == len(gold)

if __name__ == "__main__":
    test_1()
