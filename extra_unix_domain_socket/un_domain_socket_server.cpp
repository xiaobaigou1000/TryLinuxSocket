#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

int main()
{
    sockaddr_un server_address{};
    server_address.sun_family = AF_UNIX;
    const char *filePath = "/home/xiaobaigou/hello";
    strncpy(server_address.sun_path, filePath, sizeof(server_address.sun_path) - 1);

    int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    unlink(filePath);
    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "bind() error.\n";
        return 0;
    }

    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "listen() error.\n";
        close(server_socket);
        return 0;
    }

    int client_socket = accept(server_socket, nullptr, nullptr);
    char buffer[512];
    int strLength = read(client_socket, buffer, 511);
    buffer[strLength] = 0;
    std::cout << buffer << std::endl;
    write(client_socket, buffer, strLength);

    close(client_socket);
    close(server_socket);
}