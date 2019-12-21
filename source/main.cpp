#include "misc/allHeaders.hpp"
    
int main(int argc, char* argv[]) {

    std::cout << "\n\n" << std::setw(40) << " " << std::right << 
        "Digital Bibliography & Library Project - The DBLP Computer Science Bibliography" 
        << std::setw(20) << " " << "\n";

    for ( unsigned option = 0 ; option != 8 ; ) {

        displayOption();

        std::cin >> option;

        if ( option != 8 ) selectOption(option);
        else break;
        }    


    


















































    // auto r = cpr::Get(cpr::Url{"https://dblp.org/search/author/api?q=a&format=json&h=100#"});
    // nlohmann::json json_obj;
    
    // if (r.status_code >= 400) {
    //     std::cerr << "Error [" << r.status_code << "] making request" << std::endl;
    // } else {
    //     std::ofstream OutFile("Test_Search.json");
    //     json_obj = nlohmann::json::parse(std::string(r.text));
    //     OutFile << json_obj << "\n";
    //     OutFile.close();   
    // }

    // std::cout << json_obj["result"]["completions"] << "\n";

    // std::ifstream Infile("Test_Search.json");
    // std::ofstream OutFile("database/AuthorsUnique.csv");
    // Infile >> json_obj;

    // for ( int i = 0; i < 100 ; ++i ) {
    //     OutFile << json_obj["result"]["hits"]["hit"][i]["info"]["author"] << ",\n";
    // }

    // std::string hold = "", temp = "";

    // while ( std::getline(Infile, hold) ) {
    //     temp += hold + "\n";
    // }

    // nlohmann::json j = temp.substr(1, temp.length() - 1);
    // nlohmann::json j = nlohmann::json::parse(temp);
    // std::cout << j["result"] << "\n" << temp << "\n";

    // nlohmann::json j2;
    // j2["result"] = 123;
    // std::cout << j2 << "\n";


    // nlohmann::json j = json_obj["result"]["query"];
    // std::cout << j.front() << "\n";

    return 0;
}