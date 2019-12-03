#include "csvReader.h"

template <class T>
CSVFileHandle<T>::CSVFileHandle(const std::string & toRead, const std::string & toWrite)
    :   toRead(toRead), toWrite(toWrite)  {

    if ( this->toRead == "" && this->toWrite == "" ) {
        std::cout << "Both filenames cannot be empty. Please provide paths.\n";
    }
    
    if ( this->toRead != "" ) {
        InFile.open(this->toRead);

        if (!InFile.is_open()) {
            std::ofstream errorLog("logs/csvReader.log", std::ios::app);

            errorLog << "In file: " << __FILE__ << " at " << __LINE__ << " at time " << __TIME__ << ": \n"
                    << "\t\tfile " << this->toRead << " could not be opened.\n";

            errorLog.close();

            std::cout << "File could not be opened.\n";
        }
    }

    if ( this->toWrite != "" ) 
        OutFile.open(this->toWrite, std::ios::app);
}

template<typename T>
CSVFileHandle<T>::CSVFileHandle(const CSVFileHandle& other) { 
    this->toWrite = other.toWrite;
    this->toRead = other.toRead;
}

template<typename T>
CSVFileHandle<T>::CSVFileHandle(CSVFileHandle&& other) {
    this->toRead = other.toRead;
    this->toWrite = other.toWrite;
    
    other.toWrite = nullptr;
    other.toRead = nullptr;
}

template<typename T>
CSVFileHandle<T>& CSVFileHandle<T>::operator=(CSVFileHandle other) {
    swap(*this, other);
    return *this;
}

template<typename T>
int CSVFileHandle<T>::changeRead(const std::string & toRead) {

    if ( toRead == "" ) {
        std::cout << "File name given for new file cannot be empty.\n";
        return FAILURE;
    }
    
    InFile.close();
    this->toRead = toRead;
    InFile.open(toRead);

    if (!InFile.is_open()) {
        std::ofstream errorLog("logs/csvReader.log", std::ios::app);

        errorLog << "In file: " << __FILE__ << " at " << __LINE__ << " at time " << __TIME__ << ": \n"
                << "\t\tfile " << toRead << " could not be opened.\n";

        errorLog.close();

        std::cout << "File could not be opened.\n";

        return FAILURE;
    } else {
        std::cout << "Filename changed successfully to " << this->toRead << "\n";
        return SUCCESS;
    }
}   

template<typename T>
int CSVFileHandle<T>::changeWrite(const std::string & toWrite) {
    if ( toWrite == "" ) {
        std::cout << "File name given for new file cannot be empty.\n";
        return FAILURE;
    }
    
    OutFile.close();
    this->toWrite = toWrite;
    OutFile.open(toWrite, std::ios::app);
        
    std::cout << "Filename changed successfully to " << this->toRead << "\n";
    return SUCCESS;
}    

template<typename T>
std::list<T> CSVFileHandle<T>::Read(void) {

    if (toRead== "") {
        std::cout << "Filename to read is not given. Cannot read.\n";
        std::list<T> newObj{};
        return newObj;
    }

    std::string buffer;
    Input.clear();

    while ( std::getline(InFile, buffer, ',') ) {
        Input.push_back(buffer);
    }

    return Input;
}

template<typename T>
void CSVFileHandle<T>::Write(const std::list<T> & listToWrite) {
    
    if (toWrite == "") {
        std::cout << "Filename to write is not given. Cannot write.\n";
        return ;
    }

    for ( const auto & item : listToWrite )
        OutFile << item << ",";
    std::cout << "\n";
}

template<typename T>
int CSVFileHandle<T>::dumpInput(const std::string & fileName) {
    if ( fileName == "" ) {
        std::cout << "Filename given cannot be empty.\n";
        return FAILURE; 
    }

    std::ofstream temp(fileName);

    temp << "[ ";
    int counter = 0;
    for( const auto & item : Input ) {
        temp << "\"" << item << "\", ";
        if ( counter % 5 == 0 ) 
            temp << "\n";
        counter++;
    }
    temp << " ]";

    temp.close();
}

template<typename T>
CSVFileHandle<T>::~CSVFileHandle() {
    InFile.close();
    OutFile.close();
}

int copyContents(const std::string & from, const std::string & to) {

    std::ifstream InFile(from);
    std::ofstream OutFile(to);

    if ( !InFile.is_open() ) {
        std::cout << "Input file could not be opened.\n";

        std::ofstream errorLog("logs/csvReader.log", std::ios::app);

        errorLog << "In file: " << __FILE__ << " at " << __LINE__ << " at time " << __TIME__ << ": \n"
            << "\t\tfile " << from << " could not be opened.\n";

        errorLog.close();
        InFile.close();

        std::cout << "File could not be opened.\n\n";
        
        return FAILURE;
    }

    std::string buffer;

    while ( std::getline(InFile, buffer, ',') ) 
        OutFile << buffer << ",";
    OutFile << "\n";

    InFile.close();
    OutFile.close();
}

template<typename T>
void swap(CSVFileHandle<T>& first, CSVFileHandle<T>& second) {
      using std::swap;
      swap(first.toRead, second.toRead);
      swap(first.toWrite, second.toWrite);
      swap(first.InFile, second.InFile);
      swap(first.OutFile, second.OutFile);
}