//Natural Language Processing (NLP)
#ifndef BAG_OF_WORDS
#define BAG_OF_WORDS

#include "algorithmFileHandle.h"

void textFromFile(string & fileName);
size_t dataSize(std::string & fileName);
bool checker(string str);
bool commonCountChecker(string str);
void count(void);
int findMax();
void print_all(void);

// * Main function
std::tuple<string, int, int, vector<string>, vector<string> >   
    BagOfWords(const string & fileName_1, const string & fileName_2);				

#endif