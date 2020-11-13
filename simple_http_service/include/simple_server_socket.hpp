#ifndef SIMPLE_SERVER_SOCKET_HPP
#define SIMPLE_SERVER_SOCKET_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <tuple>

class SimpleServerSocket
{
public:
    SimpleServerSocket(const char *address, const int port);
    std::tuple<int, sockaddr_in> accept_socket();
    bool valid() { return _valid; }
    ~SimpleServerSocket();

private:
    bool _valid = false;
    int server_socket = -1;
    sockaddr_in server_address{};

    void init();
    bool create_server_socket();
    bool bind_address();
    bool listen_socket();
};

#endif