#include <string>
#include <fstream>
#define ROOT_PATH "./static"

std::string static_server(std::string path)
{
    std::string contents;
    std::string buf;
    if (path == "/")
        path += "index.html";
    std::ifstream file(ROOT_PATH + path);
    while (std::getline(file, buf))
    {
        contents += buf;
    }
    return contents;
}