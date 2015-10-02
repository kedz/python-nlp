import os
import re
import nlp
import nltk
import nltk.tree
nlp.get_global_PTB_config().normalize_quotes = None
nlp.get_global_PTB_config().normalize_brackets = False
nlp.get_global_PTB_config().normalize_dashes = False
nlp.get_global_PTB_config().strict_ptb3 = True


def collect_paths(ontonotes_base_dir, language="english"):
    on_bdir_lang = os.path.join(
        ontonotes_base_dir, "data", "files", "data", language, "annotations")
    onf_paths = []
    for path, dirs, files in os.walk(on_bdir_lang):
        for file in files:
            if file.endswith(".onf"):
                onf_paths.append(os.path.join(path, file))
    return onf_paths 

def traverse(tree):
    tokens = []
    for index, subtree in enumerate(tree):
        if subtree.height() == 2:
            tok = subtree[0]
            pos = subtree._label
            if pos != "-NONE-":
                tokens.append([tok, pos])
                
        elif type(subtree) == nltk.tree.Tree:
            tokens.extend(traverse(subtree))
    return tokens

def main(ontonotes_base_dir, language="english"):
    onf_paths = collect_paths(ontonotes_base_dir, language=language)
    

    for onf_path in onf_paths:
        with open(onf_path, "rb") as f:

            onf_text = f.read()
            for tree_match in re.findall(r"Tree:\n[-]+\n(.*?)\n\n", 
                        onf_text, flags=re.DOTALL):

                tree_str = tree_match #.groups(1)[0]
                tree = nltk.tree.Tree.fromstring(tree_str)
                tokens = traverse(tree)
                has_parse = True
                for token in tokens:
                    if token[1] == "XX":
                        has_parse = False
                        break
                if has_parse is False:
                    continue
                for token in tokens:
                    print "\t".join(token)
                print

#            plain_match = re.search(
#                r"Plain sentence:\n[-]+\n(.*?)\n\n", 
#                onf_text, flags=re.DOTALL)
#            plain_text = plain_match.groups(1)[0]
#            plain_text = plain_text.replace("-LRB-", " -LRB- ")
#            plain_text = plain_text.replace("-RRB-", " -RRB- ")
#            #print plain_text
#            plain_tokens = [] 
#            for token in nlp.tokenize(plain_text):
#                token_str = bytes(token)
#
#                if "-" in token_str and \
#                        token_str not in set(["-LRB-","-RRB-"]):
#
#                    if re.match(
#                        r"(sub|post|pro|re|anti|non|co|re|e|pre)-[^\-]+",
#                        token_str, flags=re.I):
#                        plain_tokens.append(token_str)
#                    else:
#
#                        token_str = token_str.replace("-", " - ")
#                        plain_tokens.extend(
#                            [tok for tok in token_str.split(" ")
#                             if tok != ""])
#                else:
#                    plain_tokens.append(token_str)
#            
#
#            match = re.search(
#                r"Treebanked sentence:\n[-]+\n(.*?)\n\n", 
#                onf_text, flags=re.DOTALL)
#
#            pat = r'^0$|\*|\*PRO\*|\*PRO\*-\d+'
#            tb_text = match.groups(1)[0]
#            tb_tokens = [tok.strip() for tok in tb_text.strip().split(" ")]
#            tb_tokens = [tok for tok in tb_tokens if tok != ""]
#            tb_tokens = [tok for tok in tb_tokens
#                         if not re.match(pat, tok)]
#            for plain_tok, tb_tok in zip(plain_tokens, tb_tokens):
#                if bytes(plain_tok) != bytes(tb_tok):
#                    print(bytes(plain_tok), tb_tok)
#                    break
                    
            #print tb_text            
            #if "& quot ;" in plain_text:
            #    print onf_path
            #    print onf_text
            #    print

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument(u"--ontonotes-dir", 
            help=u"base directory of Ontonotes 5.0", required=True)
    args = parser.parse_args()
    main(args.ontonotes_dir)


