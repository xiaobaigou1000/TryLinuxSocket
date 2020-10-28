#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };

    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);



    sockaddr_in receiver_address{};
    receiver_address.sin_family = AF_INET;
    receiver_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    receiver_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&receiver_address), sizeof(receiver_address)) == -1)
    {
        errorHandle("connect() failed.");
    }

    int result = 0;

    write(client_socket, "123", strlen("123"));
    result = send(client_socket, "4", strlen("4"), MSG_OOB);//发包不成功，原因未知
    write(client_socket, "567", strlen("567"));
    result = send(client_socket, "890", strlen("890"), 0);
    close(client_socket);
    return 0;
}