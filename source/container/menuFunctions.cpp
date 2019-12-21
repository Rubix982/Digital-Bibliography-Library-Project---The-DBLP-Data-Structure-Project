#include "menuFunctions.h"
using namespace std;

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

std::tuple<std::vector<string>, std::vector<string>> list_dir(std::string path) {
    struct dirent * entry;
    std::vector<string> vect1, vect2;
    DIR * dir = opendir(path.c_str());

    if ( dir == nullptr ) return make_tuple(vect1, vect2);
    while ( ( entry = readdir(dir) ) != nullptr ) {
        string buffer = entry->d_name;

        if ( buffer != string(".") && buffer != string("..") && buffer != string("README.md") ) {
            if ( buffer.substr(buffer.size() - 4, buffer.size() - 1) == string(".csv") ) vect1.push_back(buffer);
            else vect2.push_back(buffer);
        }
    }

    closedir(dir);

    return std::make_tuple(vect1, vect2);
}

void selectOption(unsigned & option) {
    
    if ( option == 1 ) {

        string folderLocation = "database";

        int choice = 0 ;
        
        do {        
        
            auto[vect1, vect2] = list_dir(folderLocation + "/");

            std::cout << "Current csv files in the " << folderLocation << " folder: \n";
            for ( const auto & val : vect1 ) std::cout << val << "\n";

            std::cout << "\nCurrent folders in the " << folderLocation << " folder: \n";
            for ( const auto & val : vect2 ) std::cout << val << "\n";

            std::cout << "1): Open and display contents of file?\n"
                        << "2): Open new folder?\n"
                        << "3): exit.\n";
            
            std::cin >> choice;

            if ( choice == 1 ) {

                string temp_buffer;
                std::cout << "Enter file name - without the file extension: ";
                std::cin >> temp_buffer;
                temp_buffer += ".csv";

                bool flag = false;
                for ( const auto & name : vect1 ) if ( name == temp_buffer ) { flag = true; break; }

                if ( flag ) {

                    readAndOutputFile(temp_buffer);

                } else 
                    std::cout << "File does not exist. Please check the name properly.\n";

            } else if ( choice == 2 ) {

                string temp_buffer;
                std::cout << "Enter folder name: ";
                std::cin >> temp_buffer;

                bool flag = false;
                for ( const auto & name : vect2 ) if ( name == temp_buffer ) { flag = true; break; }

                if ( flag ) {
                    folderLocation = folderLocation + "/" + temp_buffer; 
                } else {
                    std::cout << "Folder does not exist. Please check the name properly.\n";
                }
            } 

            cout << "\033[2J\033[1;1H";
        
        } while ( choice != 3);

        std::cout << "Exiting.\n";

        // Look at already present data will show the contents of the
        // folder of database, then it will ask the user what file they
        // wish to preview

    } else if ( option == 2 ) {        

        // Ask for data from the server, by asking the user to input
        // the name of the author to find for

        while ( true ) {

            // Clearing the terminal everytime the menu is to be seen
            cout << "\033[2J\033[1;1H";

            // show the menu for the list of options
            cout << "1): Search for authors\n"
                <<  "2): Search for publications\n"
                <<  "3): Search for venues\n"
                <<  "4): Exit";

            // Choose the option
            int choose = 0 ;
            std::cin >> choose;

            if ( choose == 1 ) {            // If 1, go for authors

            } else if ( choose == 2 ) {     // If 2, go for publications
            
            } else if ( choose == 3 ) {     // If 3, go for venues

                // Get the name of the venue
                string venue_name;
                cout << "Enter the name of the venue: ";
                cin >> venue_name;

                // Check if the file already locally exists

                if ( checkForFileExistence(venue_name) ) {

                    cout << "Given venue's data \"" << venue_name 
                        << "\" already exists in the database.\n"
                        << "Display contents? (Y/N): ";
                    
                    std::string toCheck;
                    std::cin >> toCheck;
                    
                    // convert string to upper case
                    std::for_each(toCheck.begin(), toCheck.end(), [](char & c){
	                    c = ::toupper(c);
                    });

                    if ( toCheck == "Y" || toCheck == "YES" ) {

                        std::ifstream InFile("database/VenueList/" + venue_name + ".csv");

                        cout << "\033[2J\033[1;1H";

                        string getContentsFromFile;

                        while ( std::getline(InFile, getContentsFromFile) )
                            std::cout << getContentsFromFile;
                    
                    }

                } else {
                    string change = "";
                    for ( int i = 0, j = 0; i < venue_name.size() ; ++i ) {
                        if ( venue_name[i] != ' ' ) {

                            change = change + venue_name.substr( j, i - j );
                            j = i + 1;

                        } else if ( venue_name[i] == ' ' ) {
                            change = change + "%20";
                        }
                    }

                    auto r = cpr::Get(cpr::Url{"https://dblp.org/search/venue/api?q=" + change + "&format=json&h=100#"});

                    if ( r.status_code >= 400 ) {

                        std::ofstream OutFile("../logs/dataFetch.log", ios::app);

                        time_t _tm = time(NULL);

                        struct tm * curTime = localtime( &_tm );
                                            
                        OutFile << asctime(curTime) << ": Error [" << r.status_code << "] while making request on line "
                            << __LINE__ << " in file " << __FILE__ << "\n\n";

                        OutFile.close();

                        std::cout << "Error thrown from server, writing to dataFetch.log. Terminating.\n";

                    } else {

                        std::ofstream OutFile("database/VenueList/" + venue_name + ".csv");
                        nlohmann::json json_obj = nlohmann::json::parse(string(r.text));

                        if ( json_obj["result"]["hits"]["@total"] == 1 ) {

                            string venue = json_obj["result"]["hits"]["hit"][0]["info"]["venue"], 
                                acronym = json_obj["result"]["hits"]["hit"][0]["info"]["acronym"], 
                                type = json_obj["result"]["hits"]["hit"][0]["info"]["type"], 
                                url = json_obj["result"]["hits"]["hit"][0]["info"]["url"];

                            cout << "Venue found with the following information" 
                                << "\nVenue: " << venue << "\nAcronym: " << acronym << "\nType: " << type
                                << "\nURL: " << url << "\n\n";
                        
                            

                        } else {

                            

                        }                         

                        OutFile.close();
                    }
                }

            } else if ( choose == 4 ) {     

                break;

            } else {
            
            }
        
        }

        /*

            Firstly, get back the search result for authors, as if through searching
            after that, get back the name to look up on the server.

            Then, send a request to the server for the relevant author

            Repeat the same process for venues and publications

            Getting back a thesis, make two files for it. One would contain
            the raw text, the other will contain a processed version of that 
            which will contain only the relevant data.

        */

    } if ( option == 3 ) {        

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
    
    } else if ( option == 4 ) {        

        // Clear the terminal
        cout << "\033[2J\033[1;1H";

        

        /*

        Ask the user for the name of the publication, or the thesis that
        they want to the program to process, 

        Here, the user can decide and comapre among any number of thesis,
        and find out what the most common trends are.

        Let the user search through the publications list, and select from that.

        For this, get back data from the publications.csv file and output the
        contents to show to the user

        */

    } else if ( option == 5 ) {        

        cout << "\033[2J\033[1;1H";
        vector<string> fileNames;
        struct dirent * entry;

        DIR * dir = opendir("database/Thesis/");

        std::cout << "Current thesis present locally: \n\n";

        int i = 1;
        while ( ( entry = readdir(dir) ) != nullptr ) {
            string buffer = entry->d_name;
            buffer = buffer.substr(0, buffer.size() - 4);
            cout << i << "): " <<  "\"" << buffer << "\"\n";
            fileNames.push_back(buffer);
            ++i;
        } 

        string thesisName, patternToSearch;
        std::cout << "\nEnter the thesis that you want to search a phrase in: ";
        std::cin >> thesisName;

        std::vector<string>::iterator it = find( fileNames.begin(), fileNames.end(), thesisName);       

        if ( it != fileNames.end() ) {
            std::cout << "File \"" << thesisName << "\" found. Enter the phrase to search for: ";
            std::cin >> patternToSearch;
            
            // Start the timer for KMP
            clock_t tStart = clock();

            // end the timer for KMP
            std::this_thread::sleep_for(std::chrono::nanoseconds(100));
            clock_t tEnd_KMP = (double) ( (clock() - tStart) / CLOCKS_PER_SEC ) ;
            std::cout << "Using KMP, we get our results in " << tEnd_KMP << " seconds.\n";
                
            // Start the timer for Rabin Karp
            tStart = clock();

            // end the timer for Rabin Karp
            std::this_thread::sleep_for(std::chrono::nanoseconds(100));
            clock_t tEnd_RabinKarp = (double) ( (clock() - tStart) / CLOCKS_PER_SEC );
            std::cout << "Using Rabin Karp, we get our results in " << tEnd_RabinKarp << " seconds.\n";
            
            // std::cout << "The two algorithms show a time difference of " 
            //             << std::abs(tEnd_KMP - tEnd_RabinKarp) <<  

            

        }

        /*

        Take as input the name of a publication, and search through the relevant 
        publication through the above process.

        Apply different string searching algorithms, and compare their performances

        */

    } else if ( option == 6 ) {        

        /*

        Show to the user the list of all the authors currently present and stored
        in the database, and let the user decide if they wish to look at their thesis
        as well

        */

       // Thesis, pre-processing, python

    } else if ( option == 7 ) {        

        // See if two topics related 

        /*

        Get back the bag of words for each othe thesis provided. Check if the frequences of the two match up

        */

    }

}

void readAndOutputFile(std::string fileName) {

    ifstream InFile(fileName);    
    int comma = 0;
    char hold;
    string stringBuffer;

    while ( std::getline(InFile, stringBuffer) ) {
        stringstream buffer(stringBuffer);

        for ( int i = 0 ; i < stringBuffer.size() ; ++i ) if ( stringBuffer[i] == ',' ) comma++;

        while ( comma-- ) {
            buffer >> stringBuffer >> hold;
            std::cout << stringBuffer << ", ";
        }
        std::cout << "\n";
    }

}

bool checkForFileExistence(std::string venue_name) {

    // Can we apply any searching algorithm here?

    venue_name += ".csv";
    struct dirent * entry;
    string fileAddress = "database/VenueList/";

    DIR * dir = opendir(fileAddress.c_str());

    if ( dir == nullptr ) return false;

    while ( ( entry = readdir(dir) ) != nullptr ) {
        string buffer = entry->d_name;
        if ( buffer == venue_name ) return true;
    }

    return false;
}