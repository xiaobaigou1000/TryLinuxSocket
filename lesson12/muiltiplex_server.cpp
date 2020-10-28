#include <iostream>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
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

    fd_set reads, copy_reads;
    FD_ZERO(&reads);
    FD_SET(server_socket, &reads);
    int fd_max = server_socket;

    while (true)
    {
        copy_reads = reads;
        timeval timeout{};
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        int fd_num;
        if ((fd_num = select(fd_max + 1, &copy_reads, nullptr, nullptr, &timeout)) == -1)
        {
            break;
        }
        if (fd_num == 0)
        {
            continue;
        }

        int loopLength = fd_max + 1;
        for (int i = 0; i < loopLength; i++)
        {
            if (!FD_ISSET(i, &copy_reads))
            {
                continue;
            }

            if (i == server_socket)
            {
                sockaddr_in client_address{};
                socklen_t client_address_length = sizeof(client_address);
                int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
                if (client_socket == -1)
                {
                    printf("accept() failed.\n");
                    continue;
                }

                FD_SET(client_socket, &reads);
                fd_max = fd_max < client_socket ? client_socket : fd_max;
                printf("connected client: %d\n", client_socket);
            }
            else
            {
                std::vector<char> buffer(512);
                int str_length = read(i, buffer.data(), buffer.size());
                if (str_length == 0)
                {
                    FD_CLR(i, &reads);
                    close(i);
                    printf("Closed client: %d\n", i);
                }
                else
                {
                    write(i, buffer.data(), str_length);
                }
            }
        }
    }
    close(server_socket);
    return 0;
}