#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        std::cerr << "connect() failed.\n";
    }

    while (true)
    {
        std::string echoString;
        std::cin >> echoString;
        if (echoString == "q" || echoString == "Q")
        {
            break;
        }

        std::cout << echoString << ' ' << echoString.size() << std::endl;

        size_t writeLength = write(client_socket, echoString.c_str(), echoString.size());
        char message[30];
        int strLength;
        int currentPosition = 0;
        strLength = read(client_socket, message, 30);
        message[strLength] = 0;
        std::cout << message << std::endl;
    }

    close(client_socket);
}