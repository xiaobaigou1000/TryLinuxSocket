#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <numeric>

int main()
{
    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(9120);
    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "bind() failed.\n";
    }

    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "listen() error.\n";
    }

    for (int i = 0; i < 5; i++)
    {
        sockaddr_in client_socket_address;
        socklen_t client_socket_address_length = sizeof(client_socket_address);
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_socket_address), &client_socket_address_length);
        if (client_socket == -1)
        {
            std::cerr << "accept() failed.\n";
            continue;
        }

        char operationCount = 0;

        {
            int read_count;
            read_count = read(client_socket, &operationCount, 1);
            if (read_count == -1)
            {
                std::cerr << "read() failed.\n";
                close(client_socket);
                continue;
            }
            if (read_count == 0)
            {
                std::cerr << "unexpected EOF, close connection and continue\n";
                close(client_socket);
                continue;
            }
        }

        std::vector<int> operations(operationCount);

        {
            int current_size = 0;
            int read_count = 0;
            while (current_size < operationCount * sizeof(int))
            {
                read_count = read(client_socket, reinterpret_cast<char *>(operations.data()), operations.size() * sizeof(int) - current_size);
                current_size += read_count;
            }
        }

        int result = std::accumulate(operations.begin(), operations.end(), 0);
        write(client_socket, reinterpret_cast<char *>(&result), sizeof(int));
        close(client_socket);
    }
    close(server_socket);
}