import spacy
import sys, getopt

nlp_eng = spacy.load('en_core_web_sm')

inputfile = ''
outputfile = ''

try:
    inputfile = sys.argv[1]
    outputfile = sys.argv[2]
except:
    print ('test.py <inputfile> <outputfile>')
    sys.exit(2)

with open(inputfile) as f_in:
    file_text = f_in.read()

file_doc = nlp_eng(file_text)
nouns = list()
for token in file_doc:
    if token.pos_ == 'PROPN':
        nouns.append(token)

for noun in nouns:
    print(noun.text)

with open(outputfile, "w") as f_out:
    count = 0
    for noun in nouns:
        f_out.write(noun.text + ' ')
        count += 1
        if(count == 5):
            f_out.write('\n')
            count = 0