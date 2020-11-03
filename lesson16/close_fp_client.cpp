#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        fputs("connect() failed.\n", stderr);
        fflush(stderr);
        return -1;
    }

    FILE *readfp = fdopen(client_socket, "r");
    FILE *writefp = fdopen(client_socket, "w");

    while (true)
    {
        std::vector<char> buffer(512);
        if (fgets(buffer.data(), buffer.size(), readfp) == nullptr)
        {
            break;
        }
        fputs(buffer.data(), stdout);
        fflush(stdout);
    }
    fputs("From Client: Thank you!\n", writefp);
    fflush(writefp);
    fclose(readfp);
    fclose(writefp);
}