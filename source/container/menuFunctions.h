#ifndef MENU_FUNCTIONS
#define MENU_FUNCTIONS

#include <iostream>

void displayOption(void) {
    std::cout << "1): Look at already present data\n";                          // Show friendly view of already present local database

    std::cout << "2): Request data from server\n";                              // Find relevant authors and publications by requesting data from the server
                                                                                // and data
        
    std::cout << "3): Search for author/venue/publ in local database.\n";       // Given a name, search if it already exists. If it does return the relevant filename, position,

    std::cout << "4): Find common trends among thesis\n";                       // This requires Advance String Searching Algorithms

    std::cout << "5): Search for a particular phrase in a thesis\n";            // Find if a particular phrase does exist. Allow the leniency 

    std::cout << "6): Request thesis for an author\n";                          // Request the thesis for a publication, by going to the link, and extracting it. Use Python 
                                                                                // here to extract nouns, verbs, adjectives from the thesis. Create two files, one that contains
                                                                                // the raw text, and one that contains the text preprocessed by Python, Spacy
                                                                                    
    std::cout << "7): Find if two others are related to each other.\n";         // Make a graph of authors, see if any two others are related to each other

    std::cout << "8): Exit\n";                                                  // Exit the menu
}

void selectOption(unsigned & option) {
    switch (option) {

    case 1:

        break;

    case 2:        
        break;
    
    case 3:        
        break;
    
    case 4:        
        break;

    case 5:        
        break;

    case 6:        
        break;

    case 7:        
        break;

    default:
        break;
    }
}

#endif