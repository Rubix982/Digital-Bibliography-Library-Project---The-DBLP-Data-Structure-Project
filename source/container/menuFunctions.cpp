#include "menuFunctions.h"
using namespace std;
typedef unsigned long long ull;

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
                                                                                    
    std::cout << "7): Find if two authors are related to each other.\n";         // Make a graph of authors, see if any two others are related to each other

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
        
        auto[fileNames, folderNames] = list_dir(folderLocation + "/");
        
        do {        
        
            std::cout << "Current csv files in the " << folderLocation << " folder: \n";
            for ( const auto & fileName : fileNames ) std::cout << fileName << "\n";

            std::cout << "\nCurrent folders in the " << folderLocation << " folder: \n";
            for ( const auto & folderName : folderNames ) std::cout << folderName << "\n";

            std::cout << "1): Open and display contents of file?\n"
                        << "2): Open new folder?\n"
                        << "3): exit.\n";
            
            string temp_buffer;
            std::cin >> choice;

            if ( choice == 1 ) {

                std::cout << "Enter file name - without the file extension: ";
                std::cin >> temp_buffer;
                temp_buffer += ".csv";

                bool flag = false;
                for ( const auto & name : fileNames ) if ( name == temp_buffer ) { flag = true; break; }

                if ( flag ) readAndOutputFile(temp_buffer);
                else std::cout << "File does not exist. Please check the name properly.\n";

            } else if ( choice == 2 ) {

                std::cout << "Enter folder name: ";
                std::cin >> temp_buffer;

                bool flag = false;
                for ( const auto & name : folderNames ) if ( name == temp_buffer ) { flag = true; break; }

                if ( flag ) folderLocation += "/" + temp_buffer; 
                else std::cout << "Folder does not exist. Please check the name properly.\n";

            } else std::cout << "Invalid option! Please choose again.\n";

            cout << "\033[2J\033[1;1H";
        
        } while ( choice != 3);

        std::cout << "Exiting.\n";

        // Look at already present data will show the contents of the
        // folder of database, then it will ask the user what file they
        // wish to preview

    } else if ( option == 2 ) {             // End option == 1, start option == 2                  

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

            // * --------------------------------------------- OPTION 1 STARTS HERE -------------------------------------------------------------

            if ( choose == 1 ) {            // If 1, go for authors

                string author_name, authorFileName;
                cout << "Enter the name of the author to search: ";

                getAuthorName:              // Label for a goto
                
                cin >> author_name;
                authorFileName = author_name;

                // Eliminate spaces
                for ( int i = 0 ; i < authorFileName.size() ; ++i ) 
                    if ( authorFileName[i] == ' ' ) 
                        authorFileName = authorFileName.substr(0, i) + authorFileName.substr(i + 1, authorFileName.size() - i);

                for ( int i = 0; i < authorFileName.size() ; ++i ) 
                    if ( authorFileName[i] == ' ' ) { authorFileName = authorFileName.substr(0, i); break; }

                // Check if the authors name already exists in the database

                if ( checkForFileExistence(authorFileName, "database/Authors" ) ) {

                    cout << "Given author's data \"" << author_name
                        << "\" already exists in the database.\n"
                        << "Display contents? (Y/N): ";
                    
                    std::string toCheck;
                    std::cin >> toCheck;

                    std::for_each(toCheck.begin(), toCheck.end(), [] ( char & c) { c = ::toupper(c); });

                    if ( toCheck == "Y" || toCheck == "YES" ) {

                        std::ifstream Infile("database/Authors/" + authorFileName + ".csv");
                    
                        cout << "\033[2J\033[1:1H";

                        string getContentsFromFile;

                        while ( std::getline(Infile, getContentsFromFile) ) 
                            std::cout << getContentsFromFile;
                
                        Infile.close();

                    } // * END toCheck if condition

                } else {                // * END checkForFileExistence / file does not exist, so do the following below
                    string change = "";

                    // * For loop to create a string from the original author name
                    // * such that each ' ' is replaced by %20, which is the required
                    // * conversion to make the request easier to interpret by the browser
                    for ( int i = 0, j = 0 ; i < author_name.size() ; ++i ) 
                        if ( author_name[i] != ' ' ) {
                            change = change + author_name.substr(j, i - j);
                            j =  i + 1;
                        } else if ( author_name[i] == ' ' ) change = change + "%20";

                    auto r = cpr::Get(cpr::Url("https://dblp.org/search/author/api?q=" + change + "&format=json&h=100#"));

                    if ( r.status_code >= 400 ) {

                        // * LOG the appropriate data

                        std::ofstream OutFile("/logs/authorsFetch.log", ios::app);

                        time_t _tm = time(NULL);

                        struct tm * curTime = localtime( &_tm );
                                            
                        OutFile << asctime(curTime) << ": Error [" << r.status_code << "] while making request on line "
                            << __LINE__ << " in file " << __FILE__ << "\n\n";

                        OutFile.close();

                        std::cout << "Error thrown from server, writing to dataFetch.log. Terminating.\n";

                    } else {

                        nlohmann::json json_obj = nlohmann::json::parse(string(r.text));

                        // * Do the if-condition, if the user entered the author's name perfectly
                        // * that is, we only get a single person's data back from the API
                        if ( json_obj["result"]["hits"]["@total"] == 1 ) {

                            string authorName = json_obj["result"]["hits"]["hit"][0]["info"]["author"],
                                authorURL = json_obj["result"]["hits"]["hit"][0]["info"]["url"];

                            // ! URL can be used to extract relevant data about the author
                            // ! but current project has no HTML parser to extract the data, it can
                            // ! only currently request for the data and not extract it - except
                            // ! for the JSON format

                            // ? Use a file handler to store the data received
                            std::ofstream OutFile("/database/Authors/" + authorFileName + ".csv");
                            OutFile << "Author," << authorName << ",\nURL," << authorURL << ",";

                            // Get the rest of the data from the url obtained by the request
                            cout << "Author found with the following information: " 
                                << "\nAuthor's Name: " << authorName << "\nURL: " << authorURL << "\n";

                            OutFile.close();

                        } else {        
                            
                            // * END the if condition / go here if the name entered by the user
                            // * was not an exact match, and then display all the targets that were
                            // * instead sent by the server or the API

                            std::cout << "Exact match could not be found. Did you mean any of the below authors? \n\n";
                            ull totalAuthors = json_obj["result"]["hits"]["@sent"];


                            for ( ull i = 0, j = 0 ; i < totalAuthors ; ++i, ++j) {
                                std::cout << "\"" << json_obj["result"]["hits"]["hit"][i]["info"]["author"] << "\", ";
                                if ( ( j + 1 ) % 5 == 0 ) std::cout << "\n";
                            }

                            // * After showing the user all the names, make the user go bacl, and enter a new name to search
                            // * for, from the database, or from the server
                            std::cout << "\nPlease enter any of the above names to retrieve the data for\n";
                            goto getAuthorName;

                        }
                    }
                }


            // * --------------------------------------------- OPTION 1 ENDS HERE ---------------------------------------------------------------

            // * --------------------------------------------- OPTION 2 STARTS HERE -------------------------------------------------------------

            } else if ( choose == 2 ) {     // * If 2, go for publications

                string Publications_name, PublicationsFileName;
                
                // Label for rentering the data
                getPublicationData:

                cout << "Enter the name of the publication to search: ";
                cin >> Publications_name;
                PublicationsFileName = Publications_name;

                // * Eliminate spaces
                for ( int i = 0 ; i < PublicationsFileName.size() ; ++i ) 
                    if ( PublicationsFileName[i] == ' ' ) 
                        PublicationsFileName = PublicationsFileName.substr(0, i) + PublicationsFileName.substr(i + 1, PublicationsFileName.size() - i);

                for ( int i = 0 ; i < PublicationsFileName.size() ; ++i )
                    if ( PublicationsFileName[i] == ' ' ) { PublicationsFileName = PublicationsFileName.substr(0, i); break; }

                // * Check if the publication already exists in the database
                if ( checkForFileExistence(PublicationsFileName, "/database/PublicationsList/" ) ) {

                    cout << "Given publications's data \"" << Publications_name
                        << "\" already exists in the database.\n"
                        << "Display contents? (Y/N): ";
                    
                    std::string toCheck;
                    std::cin >> toCheck;

                    std::for_each(toCheck.begin(), toCheck.end(), [] ( char & c) { c = ::toupper(c); });

                    if ( toCheck == "Y" || toCheck == "YES" ) {

                        std::ifstream Infile("database/PublicationsList/" + PublicationsFileName + ".csv");
                    
                        cout << "\033[2J\033[1:1H";

                        string getContentsFromFile;

                        while ( std::getline(Infile, getContentsFromFile) ) 
                            std::cout << getContentsFromFile;

                        Infile.close();
                
                    } // * END toCheck if condition

                } else {                // * END checkForFileExistence / file does not exist, so do the following below
                    string change = "";

                    // * For loop to create a string from the original Publications name
                    // * such that each ' ' is replaced by %20, which is the required
                    // * conversion to make the request easier to interpret by the browser
                    for ( int i = 0, j = 0 ; i < Publications_name.size() ; ++i ) 
                        if ( Publications_name[i] != ' ' ) {
                            change = change + Publications_name.substr(j, i - j);
                            j =  i + 1;
                        } else if ( Publications_name[i] == ' ' ) change = change + "%20";

                    auto r = cpr::Get(cpr::Url("https://dblp.org/search/publ/api?q=" + change + "&format=json&h=100#"));

                    // * LOG the appropriate data
                    if ( r.status_code >= 400 ) {

                        std::ofstream OutFile("/logs/publFetch.log", ios::app);

                        time_t _tm = time(NULL);

                        struct tm * curTime = localtime( &_tm );
                                            
                        OutFile << asctime(curTime) << ": Error [" << r.status_code << "] while making request on line "
                            << __LINE__ << " in file " << __FILE__ << "\n\n";

                        OutFile.close();

                        std::cout << "Error thrown from server, writing to dataFetch.log. Terminating.\n";

                    } else {

                        nlohmann::json json_obj = nlohmann::json::parse(string(r.text));

                        // * Do the if-condition, if the user entered the Publications's name perfectly
                        // * that is, we only get a single person's data back from the API
                        
                        if ( json_obj["result"]["hits"]["@total"] == 1 ) {

                            // Extract the object that contains the list of the authors for a certain publication
                            auto PublicationAuthors = json_obj["result"]["hits"]["hit"][0]["info"]["authors"];
                            
                            // ? USE a vector to store to store the relevant author names in a container
                            std::vector<std::string> PublicationAuthors_Values;
                            
                            // Insert the names as needed
                            for ( int i = 0; i < PublicationAuthors.size() ; ++i  ) 
                                PublicationAuthors_Values.push_back(PublicationAuthors["author"][i]);

                            string PublicationsTitle    =   json_obj["result"]["hits"]["hit"][0]["info"]["title"],
                                    PublicationsVenue   =   json_obj["result"]["hits"]["hit"][0]["info"]["venue"],
                                    PublicationsVolume  =   json_obj["result"]["hits"]["hit"][0]["info"]["volume"],
                                    PublicationsPages   =   json_obj["result"]["hits"]["hit"][0]["info"]["pages"],
                                    PublicationsYear    =   json_obj["result"]["hits"]["hit"][0]["info"]["year"],
                                    PublicationsType    =   json_obj["result"]["hits"]["hit"][0]["info"]["type"],
                                    PublicationsKey     =   json_obj["result"]["hits"]["hit"][0]["info"]["key"],
                                    PublicationsDOI     =   json_obj["result"]["hits"]["hit"][0]["info"]["doi"],
                                    PublicationsEE      =   json_obj["result"]["hits"]["hit"][0]["info"]["ee"],
                                    PublicationsURL     =   json_obj["result"]["hits"]["hit"][0]["info"]["url"];                    

                            // ! URL can be used to extract relevant data about the Publications
                            // ! but current project has no HTML parser to extract the data, it can
                            // ! only currently request for the data and not extract it - except
                            // ! for the JSON format

                            // ? Creating a file handle here to output the related file in the '/database/PublicationsList/'
                            std::ofstream OutFile("/database/PublicationsList/" + PublicationsFileName + ".csv");
                            OutFile << "Authors,";
                            
                            // Get the rest of the data from the url obtained by the request
                            std::cout << "Publication \"" << PublicationsTitle << "\" has the following authors: \n";
                            
                            // * DISPLAY the contents LOCALLY, and then ...

                            ull j = 0;
                            
                            for ( const auto & name : PublicationAuthors_Values ) { 
                                std::cout << name << ", ";
                                OutFile << name << ",";
                                if ( j + 1 % 5 == 0 ) std::cout << "\n";
                                ++j;
                            }

                            std::cout   << "\nTitle: "  << PublicationsTitle    << "\nVenue: "  << PublicationsVenue 
                                        << "\nVolume: " << PublicationsVolume   << "\nPages: "  << PublicationsPages
                                        << "\nYear: "   << PublicationsYear     << "\nType: "   << PublicationsType    
                                        << "\nType: "   << PublicationsKey      << "\nDOI: "    << PublicationsDOI      
                                        << "\nEE: "     << PublicationsEE       << "\nURL: "    << PublicationsURL;
                            std::cout   << "\n";

                            OutFile << "\nTitle,"   << PublicationsTitle    << ",\nVenue,"  << PublicationsVenue    << ","
                                    << "\nVolume,"  << PublicationsVolume   << ",\nPages,"  << PublicationsPages    << ","   
                                    << "\nYear,"    << PublicationsYear     << ",\nType,"   << PublicationsType     << ","
                                    << "\nKey,"     << PublicationsKey      << ",\nDOI,"    << PublicationsDOI      << "," 
                                    << "\nEE,"      << PublicationsEE       << ",\nURL,"    << PublicationsURL      << ",";

                            // * ... output the contents to the related files

                            OutFile.close();

                        } else {        

                            // TODO | The case were the user doesn't exactly enter the correct name, and more than one
                            // TODO | results are retrieved from the server, in this case, output all the possible names 
                            // TODO | of the publications that were retrieved 

                            // * END the if condition / go here if the name entered by the user
                            // * was not an exact match, and then display all the targets that were
                            // * instead sent by the server or the API

                            std::cout << "Exact match could not be found. Did you mean any of the below Publications? \n\n";
                            ull totalPublications = json_obj["result"]["hits"]["@sent"];

                            for ( ull i = 0, j = 0 ; i < totalPublications ; ++i, ++j) {
                                std::cout << "\"" << json_obj["result"]["hits"]["hit"][i]["info"]["title"] << "\", ";
                                if ( ( j + 1 ) % 5 == 0 ) std::cout << "\n";
                            }

                            // * After showing the user all the names, make the user go back, and enter a new name to search
                            // * for, from the database, or from the server
                            std::cout << "\nPlease enter any of the above names to retrieve the data for a publication\n";        
                            goto getPublicationData;

                        }
                    }
                }

            // * --------------------------------------------- OPTION 2 ENDS HERE ---------------------------------------------------------------

            // * --------------------------------------------- OPTION 3 STARTS HERE -------------------------------------------------------------

            } else if ( choose == 3 ) {     // If 3, go for venues

                // Get the name of the venue
                string venue_name, venueFileName;

                // Label for rentering the data
                getVenueData:

                cout << "Enter the name of the venue: ";
                cin >> venue_name;
                venueFileName = venue_name;

                // * Eliminate spaces
                for ( int i = 0 ; i < venueFileName.size() ; ++i ) 
                    if ( venueFileName[i] == ' ' ) 
                        venueFileName = venueFileName.substr(0, i) + venueFileName.substr(i + 1, venueFileName.size() - i);

                for ( int i = 0 ; i < venueFileName.size() ; ++i )
                    if ( venueFileName[i] == ' ' ) { venueFileName = venueFileName.substr(0, i); break; }

                // Check if the file already locally exists

                if ( checkForFileExistence(venueFileName, "/database/VenueList/") ) {

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

                        std::ifstream InFile("database/VenueList/" + venueFileName + ".csv");

                        cout << "\033[2J\033[1;1H";

                        string getContentsFromFile;

                        while ( std::getline(InFile, getContentsFromFile) )
                            std::cout << getContentsFromFile;
                    
                        InFile.close();
                    }   // * END toCheck if condition

                } else {            // * End checkForFileExistence / else branch for checkForfileExistence
                    string change = "";

                    // * For loop to create a string from the original Publications name
                    // * such that each ' ' is replaced by %20, which is the required
                    // * conversion to make the request easier to interpret by the browser
                    for ( int i = 0, j = 0; i < venue_name.size() ; ++i ) 
                        if ( venue_name[i] != ' ' ) {
                            change = change + venue_name.substr( j, i - j );
                            j = i + 1;
                        } else if ( venue_name[i] == ' ' ) change = change + "%20";

                    auto r = cpr::Get(cpr::Url{"https://dblp.org/search/venue/api?q=" + change + "&format=json&h=100#"});

                    // * LOG the appropriate data
                    if ( r.status_code >= 400 ) {

                        std::ofstream OutFile("/logs/venueFetch.log", ios::app);

                        time_t _tm = time(NULL);

                        struct tm * curTime = localtime( &_tm );
                                            
                        OutFile << asctime(curTime) << ": Error [" << r.status_code << "] while making request on line "
                            << __LINE__ << " in file " << __FILE__ << "\n\n";

                        OutFile.close();

                        std::cout << "Error thrown from server, writing to dataFetch.log. Terminating.\n";

                    } else {

                        nlohmann::json json_obj = nlohmann::json::parse(string(r.text));

                        // * Do the if-condition, if the user entered the Publications's name perfectly
                        // * that is, we only get a single person's data back from the API

                        if ( json_obj["result"]["hits"]["@total"] == 1 ) {

                            // ? Creating file handle for the venue file to output to
                            std::ofstream OutFile("database/VenueList/" + venueFileName + ".csv");
                            
                            string  venueName   = json_obj["result"]["hits"]["hit"][0]["info"]["venue"], 
                                    acronymName = json_obj["result"]["hits"]["hit"][0]["info"]["acronym"], 
                                    typeName    = json_obj["result"]["hits"]["hit"][0]["info"]["type"], 
                                    urlName     = json_obj["result"]["hits"]["hit"][0]["info"]["url"];

                            cout << "Venue \""   << venueName << "\" found with the following information";
                            cout    << "\nVenue Name: " << venueName    << "\nAcronym: "    << acronymName
                                    << "\nType: "       << typeName     << "\nURL: "        << urlName << "\n";
                        
                            OutFile << "Venue," << venueName    << ",\n" << "Acronym,"  << acronymName << ",\n"
                                    << "Type,"  << typeName     << ",\n" << "URL,"      << urlName     << ",\n";
                            
                            OutFile.close();

                        } else {

                            // * END the if condition / go here if the name entered by the user
                            // * was not an exact match, and then display all the targets that were
                            // * instead sent by the server or the API

                            std::cout << "Exact match could not be found. Did you mean any of the below venues? \n\n";
                            ull totalVenues = json_obj["result"]["hits"]["@sent"];

                            for ( ull i = 0, j = 0 ; i < totalVenues ; ++i, ++j) {
                                std::cout << "\"" << json_obj["result"]["hits"]["hit"][i]["info"]["venue"] << "\", ";
                                if ( ( j + 1 ) % 5 == 0 ) std::cout << "\n";
                            }

                            // * After showing the user all the names, make the user go back, and enter a new name to search
                            // * for, from the database, or from the server
                            std::cout << "\nPlease enter any of the above names to retrieve the data for a venue\n";        
                            goto getVenueData;
                            
                        }                                                 
                    }
                }

            } else if ( choose == 4 ) {         // End data fetch for venues, start 4th option    

                std::cout << "Goodbye!\n";

                break;

            } else  std::cout << "Invalid option chosen. Try again, maybe?\n";
        
        }

        
        //  TODO: Getting back a thesis, make two files for it. One would contain
        //  TODO: the raw text, the other will contain a processed version of that 
        //  TODO: which will contain only the relevant data.

    } if ( option == 3 ) {                          // End option == 2, 

        // ? OPTION 3, Search for the author/venue/publ 
        // ? is in local database

        // Clear the terminal

        startAgain:

        cout << "\033[2J\033[1;1H";

        std::cout   << "Please choose one of the below options.\n";
        std::cout   << "1): For publications\n"
                    << "2): For venues\n"
                    << "3): For authors\n";

        ull option_choice;
        cin >> option_choice;

        if ( option_choice == 1 ) {                 // ? Search throughout the publications dir

            auto[fileNames, folderNames] = list_dir("/database/PublicationsList/");

            ull i = 1;
            for ( const auto & fileName : fileNames ) {
                std::cout << i << "): \"" << fileName + ".csv" << "\"\n";
                ++i;
            } 

            string buffer;

            // Label for rentering the data
            getFileNameAgainForPublications:

            std::cout << "\nEnter the filename ( without the extension ) to output the contents for: ";
            cin >> buffer;

            bool flag = false;
            for ( const auto & fileName : fileNames ) if ( fileName == buffer ) { flag = true; break; }

            if ( flag ) {

                std::ifstream getFileContents("/database/PublicationsList/" + buffer + ".csv");
                std::string bufferForFileContents;

                while ( std::getline(getFileContents, bufferForFileContents) ) 
                    std::cout << bufferForFileContents << "\n";

                getFileContents.close();

            } else {

                std::cout << "file name entered did not match any results. Please enter again.\n";
                goto getFileNameAgainForPublications;

            }

        } else if ( option_choice == 2 ) {          // ? Search throughout the venue dir

            auto[fileNames, folderNames] = list_dir("/database/VenueList/");

            ull i = 1;
            for ( const auto & fileName : fileNames ) {
                std::cout << i << "): \"" << fileName + ".csv" << "\"\n";
                ++i;
            } 

            string buffer;

            // Label for rentering the data
            getFileNameAgainForVenue:

            std::cout << "\nEnter the filename ( without the extension ) to output the contents for: ";
            cin >> buffer;

            bool flag = false;
            for ( const auto & fileName : fileNames ) if ( fileName == buffer ) { flag = true; break; }
    
            if ( flag ) {

                std::ifstream getFileContents("/database/VenueList/" + buffer + ".csv");
                std::string bufferForFileContents;

                while ( std::getline(getFileContents, bufferForFileContents) ) 
                    std::cout << bufferForFileContents << "\n";

                getFileContents.close();

            } else {

                std::cout << "file name entered did not match any results. Please enter again.\n";
                goto getFileNameAgainForVenue;

            }


        } else if ( option_choice == 3 ) {          // ? Search through the author dir

            auto[fileNames, folderNames] = list_dir("/database/Authors/");

            ull i = 1;
            for ( const auto & fileName : fileNames ) {
                std::cout << i << "): \"" << fileName + ".csv" << "\"\n";
                ++i;
            } 

            string buffer;

            // Label for rentering the data
            getFileNameAgainForAuthor:

            std::cout << "\nEnter the filename ( without the extension ) to output the contents for: ";
            cin >> buffer;

            bool flag = false;
            for ( const auto & fileName : fileNames ) if ( fileName == buffer ) { flag = true; break; }
    
            if ( flag ) {

                std::ifstream getFileContents("/database/Authors/" + buffer + ".csv");
                std::string bufferForFileContents;

                while ( std::getline(getFileContents, bufferForFileContents) ) 
                    std::cout << bufferForFileContents << "\n";

                getFileContents.close();

            } else {

                std::cout << "file name entered did not match any results. Please enter again.\n";
                goto getFileNameAgainForAuthor;

            }

        } else {

            std::cout << "Option not recognized, please try again!\n";
            goto startAgain;

        }
    
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

bool checkForFileExistence(std::string file_name, std::string folder_location) {

    // Can we apply any searching algorithm here?

    file_name += ".csv";
    struct dirent * entry;

    DIR * dir = opendir(folder_location.c_str());

    if ( dir == nullptr ) return false;

    while ( ( entry = readdir(dir) ) != nullptr ) {
        string buffer = entry->d_name;
        if ( buffer == file_name ) return true;
    }

    return false;
}