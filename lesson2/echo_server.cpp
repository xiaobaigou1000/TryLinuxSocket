#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in socket_address{};
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&socket_address), sizeof(socket_address)) == -1)
    {
        std::cerr << "bind() error.\n";
    }

    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "listen() error.\n";
    }

    sockaddr_in client_socket_address;
    socklen_t client_socket_length = sizeof(client_socket_address);

    for (int i = 0; i < 5; i++)
    {
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_socket_address), &client_socket_length);
        if (client_socket == -1)
        {
            std::cerr << "accept() error.\n";
        }
        std::cout << "connected.\nfd :" << client_socket << std::endl;
        std::cout << (i + 1) << " nd connection.\n";

        char message[30];
        int strLength;
        int current_position = 0;
        while ((strLength = read(client_socket, message, 30)) != 0)
        {
            write(client_socket, message, strLength);
        }

        close(client_socket);
    }
    close(server_socket);
}