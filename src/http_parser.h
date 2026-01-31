#pragma once
#include <string>
#include <unordered_map>

struct HttpRequest
{
    std::string method;
    std::string path;
    std::string version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

struct HttpResponse
{
    int status;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
};

class HttpParser
{
public:
    enum State
    {
        HTTP_REQUEST_LINE = 0, HTTP_HEADERS, HTTP_COMPLETE;
    }
};