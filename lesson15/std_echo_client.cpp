#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <vector>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        fputs("connect() error.", stdout);
        return -1;
    }

    FILE *readfp = fdopen(client_socket, "r");
    FILE *writefp = fdopen(client_socket, "w");

    while (true)
    {
        fputs("Input message(Q to quit): ", stdout);
        std::vector<char> buffer(512);
        fgets(buffer.data(), 512, stdin);
        if (std::string_view(buffer.data()) == std::string_view("Q\n") || std::string_view(buffer.data()) == std::string_view("q\n"))
        {
            break;
        }

        fputs(buffer.data(), writefp);
        fflush(writefp);
        fgets(buffer.data(), 512, readfp);
        printf("Message from server: %s\n", buffer.data());
    }
    fclose(writefp);
    fclose(readfp);
}