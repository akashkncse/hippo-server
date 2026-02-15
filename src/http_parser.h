#pragma once
#include <ostream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
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
enum State
{
    HTTP_REQUEST_LINE,
    HTTP_HEADERS,
    HTTP_COMPLETE
};
class HttpParser
{
public:
    State status = HTTP_REQUEST_LINE;
    std::string temp;
    void feed(HttpRequest &, const char *, size_t);
};

std::ostream &operator<<(std::ostream &, HttpRequest &);
