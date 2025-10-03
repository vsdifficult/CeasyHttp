#include <iostream>
#include "http_easy_requests.h"

int main()
{
    HttpEasyRequests http;

    // GET request example
    EasyHttpResult get_result = http.GETrequest("https://jsonplaceholder.typicode.com/posts/1");
    if (!get_result.ErrorMessage.empty())
    {
        std::cerr << "GET request failed: " << get_result.ErrorMessage << std::endl;
    }
    else
    {
        std::cout << "GET request successful!\nResponse:\n" << get_result.Data << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;

    // POST request example
    std::string post_data = "{\"title\":\"foo\",\"body\":\"bar\",\"userId\":1}";
    EasyHttpResult post_result = http.POSTrequest("https://jsonplaceholder.typicode.com/posts", post_data);
    if (!post_result.ErrorMessage.empty())
    {
        std::cerr << "POST request failed: " << post_result.ErrorMessage << std::endl;
    }
    else
    {
        std::cout << "POST request successful!\nResponse:\n" << post_result.Data << std::endl;
    }

    return 0;
}
