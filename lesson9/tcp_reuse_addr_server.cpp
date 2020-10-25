#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    //Ubuntu20.04可以正常处理进程结束后的time-wait状态，故无法复现原书中在time-wait状态下的binding error
    //但在已有一进程占用端口时再次运行程序可以正常重新分配
    int option = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    // setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "bind() failed.\n";
        return 0;
    }
    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "listen() failed.\n";
        return 0;
    }

    sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
    if (client_socket == -1)
    {
        std::cout << "accept() error.\n";
    }
    std::cout << "accepted connection.\n";

    int read_length;
    char buffer[512];
    while ((read_length = read(client_socket, buffer, 512)) != 0)
    {
        write(client_socket, buffer, read_length);
    }

    close(client_socket);
    std::cout << "closed connection.\n";
    close(server_socket);
}