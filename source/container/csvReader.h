// * Contains the implementation for class "CSVFileHandle", two #define statements,
// * and an auxilliary function 'CopyContents'

#include <string>
#include <fstream>
#include <iostream>
#include <list>

#ifndef CSV_READER
#define CSV_READER

#define SUCCESS 0
#define FAILURE -1

template<typename T>
class CSVFileHandle {

public:

    // Basic constructors
    CSVFileHandle(const std::string & toRead, const std::string & toWrite);
    CSVFileHandle(const CSVFileHandle& other);
    CSVFileHandle(CSVFileHandle&& other);
    CSVFileHandle& operator=(CSVFileHandle other);

    // Helper functions
    int changeRead(const std::string & toRead);
    int changeWrite(const std::string & toWrite);
    std::list<T> Read(void);
    void Write(const std::list<T> & listToWrite);
    int dumpInput(const std::string & fileName);

    // friend function
    template<typename P>
    friend void swap(CSVFileHandle<P>& first, CSVFileHandle<P>& second);

    // Destructor
    ~CSVFileHandle();

private:

    // Attributes
    std::string toRead;
    std::string toWrite;

    std::ofstream OutFile;
    std::ifstream InFile;

    std::list<T> Input;
};  

int copyContents(const std::string & from, const std::string & to);

#endif 