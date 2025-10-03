
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

private:
    CURL *curl;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif
