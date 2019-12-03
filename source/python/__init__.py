import spacy
from spacy import displacy

nlp = spacy.load("en_core_web_sm")
corpus = '''
The literature on e-commerce empirically reveals that e-commerce adoption brings potentially benefits to SMEs 
(Tran et al., 2013). E-commerce in general bridges the physical and time-dependent distance between 
suppliers and customers, enhances the efficiency and flexibility of production and operation, reduces market 
entry barriers, and increases the competitiveness of markets. However, its adoption by SMEs remains limited. 
For example, a previous survey found that 36% of small businesses established web sites primarily to advertise 
and promote their business, compared to 9% who established one to sell or market online. Similarly, a survey 
of 444 SMEs found that many SMEs were reluctant to conduct transactions on line; more than 80% were only using 
the Internet to communicate (via e-mail) and gather business information (Zhu, 2008). Al-Qirim (2008) found 
that the main barriers or concerns inhibiting SMEs from adopting e-commerce are: non-adopted customers/suppliers, 
violated privacy and security issues, lack of expertise or personnel, lack of belief that online marketing 
would be effective, high costs, and technical limitations of hardware or software.

Therefore, the purpose of the study is to investigate institutional factors affecting decisions of e-commerce 
adoption in Saudi SMEs from the temporal view. To address this objective, a conceptual model was developed 
based on the institutional perspective. This study has been conducted in Saudi Arabia in two phases. Phase I 
was in 2013 with a full survey and phase II was in 2016 with the follow-up targeted interviews. Data collected 
was analyzed to investigate whether determinants of e-commerce adoption in SEMs are different at maturity levels 
and change over time.
'''
doc = nlp(corpus)
noun_list = []
adj_list = []

for token in doc:
    if ( token.pos_ == "NOUN" ):
        noun_list.append(token.text)
    if ( token.pos_ == "ADJ" ):
        adj_list.append(token.text)

print(noun_list)
print(adj_list)