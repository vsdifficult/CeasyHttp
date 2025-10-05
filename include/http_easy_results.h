#ifndef HTTP_EASY_RESULTS_H
#define HTTP_EASY_RESULTS_H

#include <string>

struct EasyHttpResult
{
    int HttpCode = 0;
    std::string Message;
    std::string ErrorMessage;
    std::string Data;
};


#endif // HTTP_EASY_RESULTS_H