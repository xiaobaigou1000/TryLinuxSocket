#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    std::cout << "SOCK_STREAM: " << SOCK_STREAM << std::endl;
    std::cout << "SOCK_DGRAM: " << SOCK_DGRAM << std::endl;

    int optValue;
    socklen_t optValueLength = sizeof(optValue);
    int state = getsockopt(tcp_socket, SOL_SOCKET, SO_TYPE, &optValue, &optValueLength);
    if (state)
    {
        std::cout << "getsockopt() failed.\n";
        close(tcp_socket);
        close(udp_socket);
        return 0;
    }
    std::cout << "Socket Type of TCP socket: " << optValue << std::endl;

    state = getsockopt(udp_socket, SOL_SOCKET, SO_TYPE, &optValue, &optValueLength);
    if (state)
    {
        std::cout << "getsockopt() failed.\n";
        close(tcp_socket);
        close(udp_socket);
        return 0;
    }
    std::cout << "Socket Type of UDP socket: " << optValue << std::endl;

    close(tcp_socket);
    close(udp_socket);
    return 0;
}