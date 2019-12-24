//Natural Language Processing (NLP)
#include "BagofWords.h"

vector<int> word_freq;
vector<string> common, text;
int words = 0;
size_t common_count = 0;

void textFromFile(string & fileName) {

	ifstream text_fil(fileName);
	if (text_fil.is_open() ){
		string x;
		while ( std::getline(text_fil, x, ',') )
			text.push_back(x);
	} else {

		std::ofstream OutFile("/logs/bagOfWords.log", ios::app);

		time_t _tm = time(NULL);

		struct tm * curTime = localtime( &_tm );

		OutFile << asctime(curTime) << ": Error [" << "FILENAME_NOT_FOUND" << "] while trying to compare texts in BagOfWords.\n"
			<< __LINE__ << " in file " << __FILE__ << "\n\n";

		OutFile.close();

		std::cout << "Error thrown from BagOfWords.cpp, writing to bagOfWords.log. Terminating.\n";

	}
}

size_t dataSize(std::string & fileName) {	

	// Common words file
	ifstream com_fil(fileName);
	if ( com_fil.is_open() ) {
		string x;
		while ( std::getline( com_fil, x, ',' ) ) common.push_back(x);
	} else {

		std::ofstream OutFile("/logs/bagOfWords.log", ios::app);

		time_t _tm = time(NULL);

		struct tm * curTime = localtime( &_tm );

		OutFile << asctime(curTime) << ": Error [" << "FILENAME_NOT_FOUND" << "] while trying to compare texts in BagOfWords.\n"
			<< __LINE__ << " in file " << __FILE__ << "\n\n";

		OutFile.close();

		std::cout << "Error thrown from BagOfWords.cpp, writing to bagOfWords.log. Terminating.\n";

		return 0u;
	}

	return common.size();

}

bool checker(string str) {
	for (int i = 0; i < common.size(); i++)
		if (common[i] != str) continue;
		else return true;
	return false;
}

bool commonCountChecker(string str) {
	for (int i = common_count; i < common.size(); i++)
		if (common[i] != str) continue;
		else return true;
	return false;
}

void count(void) {

	for (int i = 0; i < text.size(); i++) word_freq.push_back(1);

	for (int i = 0; i < text.size(); i++) {
		if (checker(text[i])) {
			word_freq[i] = -1;
			continue;
		}

		for (int j = i + 1; j < text.size(); j++) 
			if (text[j] != text[i]) continue;
			else ++word_freq[i];

		words++;
		common.push_back(text[i]);
	}

	cout << words << endl;
	return ;
}

int findMax(void) {

	int max = -1, index = 0;

	for (int i = 0; i < text.size(); i++) {
		if (max < word_freq[i]) {
			index = i;
			max = word_freq[i];
		}
	}

	return index;
}

void print_all(void) {
	
	for (int i = 0; i < text.size(); i++)
		if (commonCountChecker(text[i]))
			cout << text[i] << "  :  " << word_freq[i] << "\n";
}

std::tuple<string, int, int, vector<string>, vector<string> >  
BagOfWords(string & fileName_1, string & fileName_2) {
	
	common_count = dataSize(fileName_2);
		textFromFile(fileName_1);
	count();

	int i = findMax();
	cout << "\n\n\nWord : " << text[i] << "  appeared the most.  " << word_freq[i] << "  times.";

	return std::make_tuple(string(text[i]), word_freq[i], i, common, text);
}
