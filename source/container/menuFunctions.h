#ifndef MENU_FUNCTIONS
#define MENU_FUNCTIONS

#include "allHeadersForContainer.hpp"
using namespace std;

/*



*/

void displayOption(void);
std::tuple<std::vector<string>, std::vector<string>> list_dir(std::string path);
void selectOption(unsigned & option);
void readAndOutputFile(std::string fileName);
bool checkForFileExistence(std::string venue_name, std::string folder_location);

#endif
