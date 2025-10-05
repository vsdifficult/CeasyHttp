#ifndef HTTP_EASY_REQUESTS_H
#define HTTP_EASY_REQUESTS_H

#include <string>
#include <vector>
#include <curl/curl.h> // This header is typically found in the curl development package
#include "http_easy_results.h"

class HttpEasyRequests
{
public:
    HttpEasyRequests();
    ~HttpEasyRequests();

    // Configuration
    void setSslVerification(bool enabled, const std::string &caBundlePath = "");
    void setTimeouts(long connectTimeout, long readTimeout);
    void setRedirects(bool enabled, long maxRedirects = -1L);

    // Requests without headers
    EasyHttpResult GETrequest(const std::string &url);
    EasyHttpResult POSTrequest(const std::string &url, const std::string &data);
    EasyHttpResult PUTrequest(const std::string &url, const std::string &data);
    EasyHttpResult DELETErequest(const std::string &url);
    EasyHttpResult HEADrequest(const std::string &url);
    EasyHttpResult PATCHrequest(const std::string &url, const std::string &data);
    EasyHttpResult OPTIONSrequest(const std::string &url);

    // Overloads with headers
    EasyHttpResult GETrequest(const std::string &url, const std::vector<std::string> &headers);
    EasyHttpResult POSTrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers);
    EasyHttpResult PUTrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers);
    EasyHttpResult DELETErequest(const std::string &url, const std::vector<std::string> &headers);
    EasyHttpResult HEADrequest(const std::string &url, const std::vector<std::string> &headers);
    EasyHttpResult PATCHrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers);
    EasyHttpResult OPTIONSrequest(const std::string &url, const std::vector<std::string> &headers);

private:
    CURL *curl;
    bool sslVerificationEnabled;
    std::string caBundlePath;
    long connectTimeout;
    long readTimeout;
    bool followRedirects;
    long maxRedirects;

    EasyHttpResult performRequest(const std::string &url, const std::string &method, const std::string &data, const std::vector<std::string> &headers);

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // HTTP_EASY_REQUESTS_H