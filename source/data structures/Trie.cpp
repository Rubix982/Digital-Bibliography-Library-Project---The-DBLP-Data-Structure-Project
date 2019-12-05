#include "Trie.h"

Trie * Trie::getNewNode() {
    Trie * node = new Trie;
    node->isLeaf = false;

    return node;
}

// Iterative function to insert a string in trie
void Trie::insert(Trie *& head, char * str) {
    if ( head == nullptr ) 
        head = this->getNewNode();
    
    Trie * curr = head;
    while ( *str ) {
        // create a new node if path doesn't exists
        if ( curr->map.find(*str) == curr->map.end() )
            curr->map[*str] = this->getNewNode();
    
        // go to next node
        curr = curr->map[*str];

        // move to next character
        str++;
    }
    
    // mark current node as leaf
    curr->isLeaf = true;
}

bool Trie::haveChildren(Trie const * curr) {
    // don't use (curr->map).size() to check for children

    for ( auto it : curr->map ) 
        if (it.second != nullptr )
            return true;
    
    return false;
}

// Recursive function to delete a string in trie
bool Trie::deletion(Trie *& curr, char * str) {
	// return if Trie is empty
	if (curr == nullptr)
		return false;

	// if we have not reached the end of the string
	if (*str)
	{
		// recur for the node corresponding to next character in
		// the string and if it returns true, delete current node
		// (if it is non-leaf)
		if (curr != nullptr &&  curr->map.find(*str) != curr->map.end() &&
			this->deletion(curr->map[*str], str + 1) && curr->isLeaf == false)
		{
			if (!this->haveChildren(curr))
			{
				delete curr;;
				curr = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && curr->isLeaf)
	{
		// if current node is a leaf node and don't have any children
		if (!this->haveChildren(curr))
		{
			delete curr;; // delete current node
			curr = nullptr;
			return true; // delete non-leaf parent nodes
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			curr->isLeaf = false;
			return false;	   // don't delete its parent nodes
		}
	}

	return false;
}

// Iterative function to search a string in Trie. It returns true
// if the string is found in the Trie, else it returns false
bool Trie::search(Trie* head, char* str)
{
	// return false if Trie is empty
	if (head == nullptr)
		return false;

	Trie* curr = head;
	while (*str)
	{
		// go to next node
		curr = curr->map[*str];

		// if string is invalid (reached end of path in Trie)
		if (curr == nullptr)
			return false;

		// move to next character
		str++;
	}

	// if current node is a leaf and we have reached the
	// end of the string, return true
	return curr->isLeaf;
}