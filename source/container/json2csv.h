#ifndef JSON_2_CSV
#define JSON_2_CSV

#include "allHeadersForContainer.h"
using namespace std;
using json=nlohmann::json;

class json2csv{
    json j;
    ofstream csvFile;
    std::vector<string> v;
    public:
    json2csv(const char *a){
    csvFile.open("CSV_file.csv",ios::trunc);

        ifstream jfile(a);
        if(!jfile)
        cout<<"error";
        jfile>>j;
        jfile.close();
        json element=j[0];
        get_keys(element,"\0");

        csvFile<<endl;
        for (auto& el : j.items()) 
         { 
             if(el.value().is_object())
                insert_values(el.value());
                csvFile<<endl;
         }
       
    }
    void get_keys(json tmp,string p)
    {
      
        for (auto& el : tmp.items()) 
        {
            string t=p;
            p.append(el.key());
            if(el.value().is_object())
            {
                p.append(".");
              json tmp=el.value();
              get_keys(tmp,p);
              
              
            }
           else
           {
               if(!csvFile)
               cout<<"error";
           csvFile<<p<<",";
           v.push_back(p);
           }
           
            p=t;
        }

    }
    void insert_values(json tmp)
    {
        
        
         for (auto& el : tmp.items()) 
         {   
             if(el.value().is_object())
             {
                 insert_values(el.value());
             }
             else if(el.value().is_array())
             {
                 string app;
                 int size=el.value().size();
                 cout<<size;

             }
             else
             {
                 csvFile<<el.value()<<",";
             }
             
         }
      
        
    }
    ~json2csv()
    {
      
        csvFile.close();
    }


};

#endif