#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int server_sock{};
    int client_sock{};

    sockaddr_in server_addr{};
    sockaddr_in client_addr{};

    std::string message = "hello world.";

    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (server_sock == -1)
    {
        std::cerr << "socket() error.\n";
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9160);
    if (bind(server_sock, reinterpret_cast<const sockaddr *>(&server_addr), sizeof(server_addr)) == -1)
    {
        std::cerr << "bind() error.\n";
    }

    if (listen(server_sock, 5) == -1)
    {
        std::cerr << "listen() error.\n";
    }

    socklen_t client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, reinterpret_cast<sockaddr *>(&client_addr), &client_addr_size);
    if (client_sock == -1)
    {
        std::cerr << "accept() error\n";
    }

    write(client_sock, message.c_str(), message.size());
    close(client_sock);
    close(server_sock);
}