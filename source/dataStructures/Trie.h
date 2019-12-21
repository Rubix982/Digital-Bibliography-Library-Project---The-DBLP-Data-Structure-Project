#ifndef TRIE_WITH_MAP
#define TRIE_WITH_MAP

#include <iostream>
#include <unordered_map>
using namespace std;

struct Trie {
    bool isLeaf;
    unordered_map<char, Trie*> map;

    Trie * getNewNode();
    void insert(Trie *& head, char * str);
    bool haveChildren(Trie const * curr);
    bool deletion(Trie *& curr, char * str);
    bool search(Trie* head, char* str);
};

#endif