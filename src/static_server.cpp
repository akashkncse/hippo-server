#include <string>
#include <fstream>
#define ROOT_PATH "./static"

std::string static_server(std::string path)
{
    if (path == "/")
        path += "index.html";
}