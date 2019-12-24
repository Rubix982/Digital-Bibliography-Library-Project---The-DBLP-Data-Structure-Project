//Natural Language Processing (NLP)
#ifndef BAG_OF_WORDS
#define BAG_OF_WORDS

#include "allHeadersForAlgorithms.h"
using namespace std;

// namespace BAGOFWORDS {

void textFromFile(string & fileName);
size_t dataSize(std::string & fileName);
bool checker(string str);
bool commonCountChecker(string str);
void count(void);
int findMax();
void print_all(void);

// * Main function
std::tuple<string, int, int, vector<string>, vector<string> >   
	BagOfWords(string & fileName_1, string & fileName_2);				

#endif