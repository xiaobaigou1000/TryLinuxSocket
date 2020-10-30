#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int send_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in multicast_address{};
    multicast_address.sin_family = AF_INET;
    multicast_address.sin_addr.s_addr = inet_addr("224.1.1.2");
    multicast_address.sin_port = htons(9120);

    int ttl = 64;
    setsockopt(send_socket, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
    std::string helloString("hello world.");
    sendto(send_socket, helloString.data(), helloString.size(), 0, reinterpret_cast<const sockaddr *>(&multicast_address), sizeof(multicast_address));
    close(send_socket);
}