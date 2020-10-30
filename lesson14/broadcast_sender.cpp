#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

int main()
{
    int send_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in broadcast_address{};
    broadcast_address.sin_family = AF_INET;
    broadcast_address.sin_addr.s_addr = inet_addr("255.255.255.255");
    broadcast_address.sin_port = htons(9120);

    int broadcast_option = 1;
    setsockopt(send_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_address, sizeof(broadcast_address));

    std::vector<std::string> messages{"hello", "world", "are", "you", "ok", "?"};
    for (const auto &i : messages)
    {
        sendto(send_socket, i.data(), i.size(), 0, reinterpret_cast<const sockaddr *>(&broadcast_address), sizeof(broadcast_address));
        sleep(2);
    }
    close(send_socket);
}