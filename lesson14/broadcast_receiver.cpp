#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

int main()
{
    int receive_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in client_address{};
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = htonl(INADDR_ANY);
    client_address.sin_port = htons(9120);

    if (bind(receive_socket, reinterpret_cast<const sockaddr *>(&client_address), sizeof(client_address)) == -1)
    {
        std::cerr << "bind() error.";
        return 1;
    }

    while (true)
    {
        std::vector<char> buffer(512);
        int str_length = recvfrom(receive_socket, buffer.data(), 511, 0, nullptr, nullptr);
        if (str_length < 0)
        {
            break;
        }
        buffer[str_length] = 0;
        std::cout << buffer.data() << std::endl;
    }
    close(receive_socket);
}