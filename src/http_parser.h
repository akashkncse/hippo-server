#pragma once
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

class HttpParser
{
public:
    enum State
    {
        HTTP_REQUEST_LINE,
        HTTP_HEADERS,
        HTTP_COMPLETE
    };
    State status;
    std::string temp;
    void feed(HttpRequest &req, const char *b, size_t len)
    {
        temp.append(b, len);
        for (;;)
        {
            if (status == HTTP_REQUEST_LINE)
            {
                int pos = temp.find("\r\n");
                if (pos == std::string::npos)
                    break;
                std::string line = temp.substr(0, pos);
                std::stringstream ss(line);
                ss >> req.method >> req.path >> req.version;
                temp.erase(0, pos + 2);
                status = HTTP_HEADERS;
            }
            else if (status == HTTP_HEADERS)
            {
                int pos = temp.find("\r\n");
                if (pos == std::string::npos)
                    break;
                if (pos == 0)
                {
                    status = HTTP_COMPLETE;
                }
                std::string line = temp.substr(0, pos);
                std::stringstream liness(line);
                temp.erase(0, pos + 2);
                std::vector<std::string> x;
                std::string y;
                while (std::getline(liness, y, ':'))
                {
                    x.push_back(y);
                }
                req.headers[x[0]] = x[1];
            }
        }
    }
};