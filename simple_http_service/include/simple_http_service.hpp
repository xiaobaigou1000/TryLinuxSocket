#ifndef SIMPLE_HTTP_SERVICE_HPP
#define SIMPLE_HTTP_SERVICE_HPP

#include "simple_server_socket.hpp"

class SimpleHttpService
{
public:
    SimpleHttpService(const char *address, int port);

private:
    SimpleServerSocket server_socket;
    static const char *content_type(const std::string &filePath);
    static void send_data(FILE *fp, const char *content_type, const char *file_name);
};

#endif