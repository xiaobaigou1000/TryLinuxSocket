#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == -1)
    {
        std::cerr << "socket init failed.\n";
        return 0;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "connect() failed.\n";
    }

    std::cout << "Operation count :";
    int operationCount;
    std::cin >> operationCount;
    char operationCountToSend = static_cast<char>(operationCount);

    std::vector<int> operations(operationCount);
    for (int i = 0; i < operationCount; i++)
    {
        std::cout << "input " << (i + 1) << "th operand :";
        std::cin >> operations[i];
    }

    write(client_socket, &operationCountToSend, 1);
    write(client_socket, reinterpret_cast<char *>(operations.data()), operationCount * sizeof(int));

    int result;
    read(client_socket,reinterpret_cast<char*>(&result),4);
    std::cout<<"Result from server : "<< result<<std::endl;
}