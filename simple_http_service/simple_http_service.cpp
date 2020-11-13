#include "simple_http_service.hpp"
#include <string_view>

SimpleHttpService::SimpleHttpService(const char *address, int port)
    : server_socket(address, port)
{
}

const char *SimpleHttpService::content_type(const std::string &filePath)
{
    std::string::size_type pos = filePath.find_last_of(".");
    if (pos == std::string::npos)
    {
        return "text/plain";
    }

    std::string_view extension(filePath.data() + pos, filePath.size() - pos);
    if (extension == "html" || extension == "htm")
    {
        return "text/html";
    }
    else
    {
        return "text/plain";
    }
}

void SimpleHttpService::send_data(FILE *fp, const char *content_type, const char *file_name)
{
    
}