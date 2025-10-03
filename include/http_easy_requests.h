
#ifndef HTTP_EASY_REQUESTS_H
#define HTTP_EASY_REQUESTS_H

#include <string>
#include <curl/curl.h>
#include "http_easy_results.h"

class HttpEasyRequests
{
public:
    HttpEasyRequests();
    ~HttpEasyRequests();

    EasyHttpResult GETrequest(const std::string &url);
    EasyHttpResult POSTrequest(const std::string &url, const std::string &data);
    EasyHttpResult PUTrequest(const std::string &url, const std::string &data);
    EasyHttpResult DELETErequest(const std::string &url);

private:
    CURL *curl;

    EasyHttpResult performRequest(const std::string &url, const std::string &method, const std::string &data);


    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif
