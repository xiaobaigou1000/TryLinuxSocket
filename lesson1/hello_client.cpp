#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sock;
    sockaddr_in server_address{};
    char message[30];
    int str_len;
    std::fill(std::begin(message), std::end(message), 0);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "socket() error";
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9160);
    if (connect(sock, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() error\n";
    }

    str_len = read(sock, message, sizeof(message) - 1);
    std::cout << "Message from server :\n"
              << message << std::endl;
    close(sock);
    return 0;
}