#include "http_easy_requests.h"
#include <iostream>

HttpEasyRequests::HttpEasyRequests()
{
    curl = curl_easy_init();
}

HttpEasyRequests::~HttpEasyRequests()
{
    if (curl)
        curl_easy_cleanup(curl);
}

size_t HttpEasyRequests::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

EasyHttpResult HttpEasyRequests::GETrequest(const std::string &url)
{
    EasyHttpResult result;

    if (!curl)
    {
        result.ErrorMessage = "Curl not found";
        return result;
    }

    if (url.empty())
    {
        result.ErrorMessage = "URL is empty";
        return result;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.Data);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        result.ErrorMessage = curl_easy_strerror(res);
    }
    else
    {
        result.Message = "OK";
    }

    return result;
}
