#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iterator>

int main()
{
    std::ifstream inputFile("./input");
    std::string inputString{std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>()};

    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "bind() error.\n";
    }

    if (listen(server_socket, 5) == -1)
    {
        std::cerr << "listen() failed.\n";
    }

    sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
    int writeLength = write(client_socket, inputString.c_str(), inputString.size());
    shutdown(client_socket, SHUT_WR);
    char message[512];
    std::fill(std::begin(message), std::end(message), 0);
    int returnMessageLength = read(client_socket, message, 511);
    message[returnMessageLength] = 0;
    std::cout << message << std::endl;
    close(client_socket);
    close(server_socket);
}