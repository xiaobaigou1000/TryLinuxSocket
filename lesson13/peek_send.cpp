#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };

    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        errorHandle("connect() error.");
    }

    char buffer[] = "233";

    write(client_socket, buffer, sizeof(buffer));
    close(client_socket);
    return 0;
}