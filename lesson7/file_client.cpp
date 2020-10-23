#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    std::ofstream outputFile("./output");

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() failed.\n";
    }
    int read_count;
    char buffer[512];
    while ((read_count = read(client_socket, buffer, 512)) != 0)
    {
        outputFile.write(buffer, read_count);
    }
    std::cout << "read success.\n";
    write(client_socket, "Thank you", 10);
    outputFile.close();
    close(client_socket);
}