#ifndef HTTP_Reports
#define HTTP_Reports

#include <string> 


class HttpEasyReportsOperations
{
public: 
    HttpEasyReportsOperations() ;
    ~HttpEasyReportsOperations() ; 

    bool SaveReport(const std::string &path, std::string data ); 
    bool DeleteReport(const std::string &path); 
    std::string ReadReport(const std::string &path); 
    
}; 

#endif HTTP_Reports 