#include <include/cpr/cpr.h>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

    auto r = cpr::Get(cpr::Url("https://imgs.xkcd.com/comics/how_old.png"));
    std::ofstream OutFile("comic.jpeg", std::ios::binary);
    OutFile << r.text;
    OutFile.close();

    return 0;
}