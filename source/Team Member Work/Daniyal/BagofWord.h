//Natural Language Processing (NLP)
#include <bits/stdc++.h>
using namespace std;

vector<int> word_freq;
fstream com_fil;  //common words file
fstream text_fil; // to read text from file
vector<string> common, text;
int words = 0, index = 0, common_count = 0;

void txt_from_fil() {

	text_fil.open("Text.txt", ios::in);
	if (text_fil.is_open() ){
		string x;
		while (text_fil >> x)
			text.push_back(x);
	}
}

int data_1() {	
	com_fil.open("ComWords.txt", ios::in);
	if (com_fil.is_open()) {
		string x;
		while (com_fil >> x) common.push_back(x);
	}
	return common.size();
}

bool checker(string st) {
	for (int i = 0; i < common.size(); i++)
		if (common[i] != st) continue;
		else return true;
	return false;
}

bool com_count_checker(string s1) {
	for (int i = common_count; i < common.size(); i++)
		if (common[i] != s1) continue;
		else return true;

	return false;
}

void count(void) {
	
	for (int i = 0; i < text.size(); i++) word_freq.push_back(1);
	
	for (int i = 0; i < text.size(); i++) {
		if (checker(text[i]))
		{
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
}

int find_max() {

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
		if (com_count_checker(text[i]))
			cout << text[i] << "  :  " << word_freq[i] << "\n";
}

void BagOfWords(void) {
	
	common_count = data_1();
	txt_from_fil();
	count();

	int i = find_max();
	cout << "\n\n\nWord : " << text[i] << "  appeared the most.  " << word_freq[i] << "  times.";
}
