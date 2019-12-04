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

        // Look at already present data will show the contents of the
        // folder of database, then it will ask the user what file they
        // wish to preview

        break;

    case 2:        

        // Ask for data from the server, by asking the user to input
        // the name of the author to find for

        /*

            Firstly, get back the search result for authors, as if through searching
            after that, get back the name to look up on the server.

            Then, send a request to the server for the relevant author

            Repeat the same process for venues and publications

            Getting back a thesis, make two files for it. One would contain
            the raw text, the other will contain a processed version of that 
            which will contain only the relevant data.

        */

        break;
    
    case 3:        

        /*

        Ask the user what kind of data they want to preview. For that, if the 
        user chooses to look at the publications, show them the content from 
        publications, and output the contents locally.

        Here, if the user asks for a match with, or wants to look up, say,
        a publication, apply a searching alogrithm for strings.

        First take all the names as input, and search through that

        */

        // String Searching Algorithm

        // Bag Of Words

        break;
    
    case 4:        

        /*

        Ask the user for the name of the publication, or the thesis that
        they want to the program to process, 

        Here, the user can decide and comapre among any number of thesis,
        and find out what the most common trends are.

        Let the user search through the publications list, and select from that.

        For this, get back data from the publications.csv file and output the
        contents to show to the user

        */

        break;

    case 5:        

        /*

        Take as input the name of a publication, and search through the relevant 
        publication through the above process.

        Apply different string searching algorithms, and compare their performances

        */

        break;

    case 6:        

        /*

        Show to the user the list of all the authors currently present and stored
        in the database, and let the user decide if they wish to look at their thesis
        as well

        */

       // Thesis, pre-processing, python

        break;

    case 7:        

        // See if two topics related 
    
        break;

    default:
        break;
    }
}

#endif