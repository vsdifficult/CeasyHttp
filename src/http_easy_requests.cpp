#include "http_easy_requests.h"
#include <iostream>

HttpEasyRequests::HttpEasyRequests()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    // Secure by default
    sslVerificationEnabled = true;
    caBundlePath = "";
    connectTimeout = 30L;
    readTimeout = 30L;
}

HttpEasyRequests::~HttpEasyRequests()
{
    if (curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();
}

void HttpEasyRequests::setSslVerification(bool enabled, const std::string &caPath)
{
    sslVerificationEnabled = enabled;
    caBundlePath = caPath;
}

void HttpEasyRequests::setTimeouts(long connect, long read)
{
    connectTimeout = connect;
    readTimeout = read;
}

size_t HttpEasyRequests::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Requests without headers
EasyHttpResult HttpEasyRequests::GETrequest(const std::string &url)
{
    return performRequest(url, "GET", "", {});
}

EasyHttpResult HttpEasyRequests::POSTrequest(const std::string &url, const std::string &data)
{
    return performRequest(url, "POST", data, {});
}

EasyHttpResult HttpEasyRequests::PUTrequest(const std::string &url, const std::string &data)
{
    return performRequest(url, "PUT", data, {});
}

EasyHttpResult HttpEasyRequests::DELETErequest(const std::string &url)
{
    return performRequest(url, "DELETE", "", {});
}

EasyHttpResult HttpEasyRequests::HEADrequest(const std::string &url)
{
    return performRequest(url, "HEAD", "", {});
}

EasyHttpResult HttpEasyRequests::PATCHrequest(const std::string &url, const std::string &data)
{
    return performRequest(url, "PATCH", data, {});
}

EasyHttpResult HttpEasyRequests::OPTIONSrequest(const std::string &url)
{
    return performRequest(url, "OPTIONS", "", {});
}

// Overloads with headers
EasyHttpResult HttpEasyRequests::GETrequest(const std::string &url, const std::vector<std::string> &headers)
{
    return performRequest(url, "GET", "", headers);
}

EasyHttpResult HttpEasyRequests::POSTrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers)
{
    return performRequest(url, "POST", data, headers);
}

EasyHttpResult HttpEasyRequests::PUTrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers)
{
    return performRequest(url, "PUT", data, headers);
}

EasyHttpResult HttpEasyRequests::DELETErequest(const std::string &url, const std::vector<std::string> &headers)
{
    return performRequest(url, "DELETE", "", headers);
}

EasyHttpResult HttpEasyRequests::HEADrequest(const std::string &url, const std::vector<std::string> &headers)
{
    return performRequest(url, "HEAD", "", headers);
}

EasyHttpResult HttpEasyRequests::PATCHrequest(const std::string &url, const std::string &data, const std::vector<std::string> &headers)
{
    return performRequest(url, "PATCH", data, headers);
}

EasyHttpResult HttpEasyRequests::OPTIONSrequest(const std::string &url, const std::vector<std::string> &headers)
{
    return performRequest(url, "OPTIONS", "", headers);
}

EasyHttpResult HttpEasyRequests::performRequest(const std::string &url, const std::string &method, const std::string &data, const std::vector<std::string> &headers)
{
    EasyHttpResult result;
    struct curl_slist *header_list = NULL;

    if (!curl)
    {
        result.ErrorMessage = "curl_easy_init() failed";
        return result;
    }

    curl_easy_reset(curl);

    if (!headers.empty())
    {
        for (const auto& header : headers)
        {
            header_list = curl_slist_append(header_list, header.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result.Data);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, connectTimeout);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, readTimeout);
    
    // SSL Verification settings
    if (sslVerificationEnabled) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        if (!caBundlePath.empty()) {
            curl_easy_setopt(curl, CURLOPT_CAINFO, caBundlePath.c_str());
        }
    } else {
        // This is insecure and should be used with caution
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    }

    if (method == "GET")
    {
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    }
    else if (method == "POST")
    {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        if (!data.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        }
    }
    else if (method == "PUT")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (!data.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        }
    }
    else if (method == "PATCH")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
        if (!data.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        }
    }
    else if (method == "DELETE")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }
    else if (method == "HEAD")
    {
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    }
    else if (method == "OPTIONS")
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    }

    CURLcode res = curl_easy_perform(curl);

    if (header_list)
    {
        curl_slist_free_all(header_list);
    }

    if (res != CURLE_OK)
    {
        result.ErrorMessage = curl_easy_strerror(res);
    }
    else
    {
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        result.HttpCode = static_cast<int>(http_code);
        result.Message = "OK";
    }

    return result;
}