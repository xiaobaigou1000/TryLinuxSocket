#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() failed.\n";
        close(client_socket);
        return 0;
    }

    int read_length;
    char buffer[512];

    while ((read_length = read(client_socket, buffer, 511)) != 0)
    {
        buffer[read_length] = 0;
        std::cout << buffer << std::endl;
    }
    close(client_socket);
}