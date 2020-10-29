#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };

    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        errorHandle("bind() error.");
    }

    if (listen(server_socket, 5) == -1)
    {
        errorHandle("listen() error.");
    }

    sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    int receive_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_size);
    if (receive_socket == -1)
    {
        errorHandle("accept() error.");
    }

    std::vector<char> buffer(512);
    while (true)
    {
        int str_length = recv(receive_socket, buffer.data(), 511, MSG_PEEK | MSG_DONTWAIT);
        if (str_length > 0)
        {
            buffer[str_length] = 0;
            printf("Buffering %d bytes: %s\n", str_length, buffer.data());
            break;
        }
    }

    int str_length = recv(receive_socket, buffer.data(), 511, 0);
    buffer[str_length] = 0;
    printf("Read again: %s\n", buffer.data());
    close(receive_socket);
    close(server_socket);
}