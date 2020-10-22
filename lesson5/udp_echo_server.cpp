#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_addr), sizeof(server_addr)) == -1)
    {
        std::cerr << "bind() error.\n";
    }

    sockaddr_in client_addr{};
    socklen_t client_address_length = sizeof(client_addr);

    while (true)
    {
        char buffer[512];
        int strLength = recvfrom(server_socket, buffer, 512, 0, reinterpret_cast<sockaddr *>(&client_addr), &client_address_length);
        sendto(server_socket,buffer,strLength,0,reinterpret_cast<const sockaddr*>(&client_addr),client_address_length);
    }
    close(server_socket);
}