#include "simple_server_socket.hpp"
#include <unistd.h>
#include <spdlog/spdlog.h>

SimpleServerSocket::SimpleServerSocket(const char *address, const int port)
{
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(address);
    server_address.sin_port = htons(port);
}

SimpleServerSocket::~SimpleServerSocket()
{
    close(server_socket);
}

std::tuple<int, sockaddr_in> SimpleServerSocket::accept_socket()
{
    int client_socket;
    sockaddr_in client_address;
    socklen_t client_socket_length = sizeof(sockaddr_in);
    client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_socket_length);
    return {client_socket, client_address};
}

void SimpleServerSocket::init()
{
    bool result = false;

    result = create_server_socket();
    if (!result)
    {
        spdlog::critical("create socket error.");
        return;
    }

    result = bind_address();
    if (!result)
    {
        spdlog::critical("bind address error.");
        return;
    }

    result = listen_socket();
    if (!result)
    {
        spdlog::critical("listen socket error.");
        return;
    }
    _valid = true;
}

bool SimpleServerSocket::create_server_socket()
{
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    return server_socket != -1;
}

bool SimpleServerSocket::bind_address()
{
    int result = bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(sockaddr_in));
    return result != -1;
}

bool SimpleServerSocket::listen_socket()
{
    int result = listen(server_socket, 5);
    return result != -1;
}