#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    while (true)
    {
        std::string message;
        std::cin >> message;
        char buffer[512];
        sendto(client_socket, message.c_str(), message.size(), 0, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address));
        sockaddr_in from_address{};
        socklen_t from_address_length = sizeof(from_address);
        int strLength = recvfrom(client_socket, buffer, 512, 0, reinterpret_cast<sockaddr *>(&from_address), &from_address_length);
        buffer[strLength]=0;
        std::cout<<buffer<<std::endl;
    }
    close(client_socket);
}