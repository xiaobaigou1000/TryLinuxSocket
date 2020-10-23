#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() failed.\n";
    }

    while (true)
    {
        std::cout << "Message to send(q to quit) :";
        std::string message;
        std::cin >> message;
        if (message == "q")
        {
            break;
        }
        // sendto(client_socket,message.data(),message.size(),0,reinterpret_cast<const sockaddr*>(&server_address),sizeof(server_address));
        write(client_socket, message.data(), message.size());

        sockaddr_in from_addr{};
        socklen_t from_addr_length = sizeof(from_addr);
        char buffer[512];
        // int strLength = recvfrom(client_socket,buffer,512,0,reinterpret_cast<sockaddr*>(&from_addr),&from_addr_length);
        int strLength = read(client_socket, buffer, 512);
        buffer[strLength] = 0;
        std::cout << buffer << std::endl;
    }
    close(client_socket);
}