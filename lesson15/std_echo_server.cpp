#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };
    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == -1)
    {
        errorHandle("socket() error.");
    }

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
        errorHandle("listen() handle.");
    }

    for (int i = 0; i < 5; i++)
    {
        sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_size);
        FILE *readfp = fdopen(client_socket, "r");
        FILE *writefp = fdopen(client_socket, "w");
        std::vector<char> buffer(512);
        while (!feof(readfp))
        {
            fgets(buffer.data(), 512, readfp);
            fputs(buffer.data(), writefp);
            fflush(writefp);
        }
        fclose(readfp);
        fclose(writefp);
    }
    close(server_socket);
}