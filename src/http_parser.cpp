#include "http_parser.h"
#include <iomanip>
void HttpParser::feed(HttpRequest &req, const char *b, size_t len) {
  temp.append(b, len);
  for (;;) {
    if (status == HTTP_REQUEST_LINE) {
      int pos = temp.find("\r\n");
      if (pos == std::string::npos)
        break;
      std::string line = temp.substr(0, pos);
      std::stringstream ss(line);
      ss >> req.method >> req.path >> req.version;
      temp.erase(0, pos + 2);
      status = HTTP_HEADERS;
    } else if (status == HTTP_HEADERS) {
      int pos = temp.find("\r\n");
      if (pos == std::string::npos)
        break;
      if (pos == 0) {
        status = HTTP_COMPLETE;
        break;
      }
      std::string line = temp.substr(0, pos);
      std::stringstream liness(line);
      temp.erase(0, pos + 2);
      std::vector<std::string> x;
      std::string y;
      while (std::getline(liness, y, ':')) {
        x.push_back(y);
      }
      std::string value = x[1];
      if (!value.empty() && value[0] == ' ') {
        value.erase(0, 1);
      }
      req.headers[x[0]] = x[1];
    }
  }
}

std::ostream &operator<<(std::ostream &o, HttpRequest &req) {
  o << "--- HTTP Request ---\n"
    << std::left << std::setw(30) << "Method" << " : " << req.method << "\n"
    << std::left << std::setw(30) << "Path" << " : " << req.path << "\n"
    << std::left << std::setw(30) << "Version" << " : " << req.version << "\n"
    << "--- Headers ---\n";
  for (const auto &[key, value] : req.headers) {
    o << std::left << std::setw(30) << key << " : " << value << "\n";
  }
  o << "--------------------";
  return o;
}
