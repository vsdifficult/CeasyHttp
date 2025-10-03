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
    return performRequest(url, "GET", "");
}

EasyHttpResult HttpEasyRequests::POSTrequest(const std::string &url, const std::string &data)
{
    return performRequest(url, "POST", data);
}

EasyHttpResult HttpEasyRequests::PUTrequest(const std::string &url, const std::string &data)
{
    return performRequest(url, "PUT", data);
}

EasyHttpResult HttpEasyRequests::DELETErequest(const std::string &url)
{
    return performRequest(url, "DELETE", "");
}

EasyHttpResult HttpEasyRequests::performRequest(const std::string &url, const std::string &method, const std::string &data)
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

    if (method == "POST")
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }
    else if (method == "PUT")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }
    else if (method == "DELETE")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }

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
