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

    if (connect(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() failed.\n";
        close(server_socket);
        return 0;
    }

    const char *fuckYouMessage = "fuck you!";

    write(server_socket, fuckYouMessage, sizeof(fuckYouMessage));
    char buffer[512];
    int strLength = read(server_socket, buffer, 511);
    buffer[strLength] = 0;
    std::cout << buffer << std::endl;
    close(server_socket);
}