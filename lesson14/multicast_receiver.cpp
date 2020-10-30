#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

int main()
{
    int receive_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in bind_address{};
    bind_address.sin_family = AF_INET;
    bind_address.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_address.sin_port = htons(9120);

    if (bind(receive_socket, reinterpret_cast<const sockaddr *>(&bind_address), sizeof(bind_address)) == -1)
    {
        std::cerr << "bind() failed.\n";
        return 0;
    }

    ip_mreq join_address{};
    join_address.imr_multiaddr.s_addr=inet_addr("224.1.1.2");
    join_address.imr_interface.s_addr=htonl(INADDR_ANY);
    setsockopt(receive_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &join_address, sizeof(join_address));

    std::vector<char> buffer(512);
    int str_length = recvfrom(receive_socket, buffer.data(), buffer.size(), 0, nullptr, nullptr);
    buffer[str_length] = 0;
    std::cout << buffer.data() << std::endl;
}