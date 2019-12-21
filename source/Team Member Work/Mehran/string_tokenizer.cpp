#include <bits/stdc++.h>
using namespace std;

// String tokenizer class.
class StringTokenizer {

public:

    StringTokenizer(const string& s, const char* delim = NULL) :
    str_(s), count_(-1), begin_(0), end_(0)
    {
        if (!delim)
            delim_ = " \f\n\r\t\v";  //default to whitespace
        else
            delim_ = delim;

      // Point to the first token
        begin_ = str_.find_first_not_of(delim_);
        end_ = str_.find_first_of(delim_, begin_);
   }

    size_t countTokens()
    {
        if (count_ >= 0) // return if we've already counted
            return(count_);

        string::size_type n = 0;
        string::size_type i = 0;

        for (;;)
        {
            if ((i = str_.find_first_not_of(delim_, i)) == string::npos)
                break;
            i = str_.find_first_of(delim_, i+1);
            n++;
            if (i == string::npos)
                break;
        }
        return (count_ = n);
    }
    bool hasMoreTokens() {return(begin_ != end_);}
    string nextToken()
    {
        string s = "";
        if (begin_ != string::npos && end_ != string::npos)
        {
            s = str_.substr(begin_, end_-begin_);
            begin_ = str_.find_first_not_of(delim_, end_);
            end_ = str_.find_first_of(delim_, begin_);
        }
        else if (begin_ != string::npos && end_ == string::npos)
        {
            s = str_.substr(begin_, str_.length()-begin_);
            begin_ = str_.find_first_not_of(delim_, end_);
        }
        return s;
    }

    private:
        StringTokenizer() {};
        string delim_;
        string str_;
        int count_;
        int begin_;
        int end_;
};