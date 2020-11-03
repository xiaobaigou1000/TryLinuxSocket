#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
    if (client_socket == -1)
    {
        errorHandle("accept() error.");
    }

    FILE *readfp = fdopen(client_socket, "r");
    FILE *writefp = fdopen(client_socket, "w");

    fputs("From Server: Hi~ Client?\n", writefp);
    fputs("I love all of the world\n", writefp);
    fputs("You are awesome!\n", writefp);
    fflush(writefp);

    fclose(writefp);
    std::vector<char> buffer(512);
    fgets(buffer.data(), buffer.size(), readfp);
    fputs(buffer.data(), stdout);
    fclose(readfp);
}