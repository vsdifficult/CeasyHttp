
#include <http_easy_reports.h> 
#include <http_easy_resources.h>
#include <iostream> 
#include <fstream>


HttpEasyReportsOperations::HttpEasyReportsOperations() { }
HttpEasyReportsOperations::~HttpEasyReportsOperations() { } 

bool HttpEasyReportsOperations::SaveReport(const std::string &path, std::string data) 
{ 
    std::ofstream ReportFile(path); 
    
    if (!ReportFile.is_open()) {
        std::cerr << "Error: Could not open file at path: " << path << std::endl;
        return false;
    }

    ReportFile << reportHeader;

    ReportFile << data;
    
    if (ReportFile.fail()) {
        std::cerr << "Error: Failed to write data to file at path: " << path << std::endl;
        ReportFile.close(); 
        return false;
    }
    
    ReportFile.close();
    
    return true;
}

bool HttpEasyReportsOperations::DeleteReport(const std::string &path) 
{ 
    if (path.empty()) 
        throw "Error: empty file path"; 
        return false; 

    std::remove(path.c_str()); 

    return true;
} 

std::string HttpEasyReportsOperations::ReadReport(const std::string &path)
{ 
    if (path.empty()) 
        throw "Error: empty file path"; 

    std::string data;
    std::ifstream ReportFile(path);

    if (!ReportFile.is_open()) {
        std::cerr << "Error: Could not open file at path: " << path << std::endl;
        return ""; // Or throw an exception
    }

    std::string line;
    while (std::getline(ReportFile, line)) {
        data += line + "\n";
    }

    ReportFile.close();

    return data; 
    
}