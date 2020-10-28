#include <iostream>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };

    auto read_childproc = [](int sig) {
        int status;
        pid_t pid = waitpid(-1, &status, WNOHANG);
        printf("Removed proc id: %d\n", pid);
    };

    struct sigaction action
    {
    };
    action.sa_handler = read_childproc;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGCHLD, &action, nullptr);

    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        errorHandle("bind() failed.\n");
    }

    if (listen(server_socket, 5) == -1)
    {
        errorHandle("listen() failed.\n");
    }

    auto handleConnection = [server_socket](int client_socket) {
        close(server_socket);
        int strLength;
        std::vector<char> buffer(1024);
        while ((strLength = read(client_socket, buffer.data(), buffer.size())) != 0)
        {
            write(client_socket, buffer.data(), strLength);
        }

        close(client_socket);
        printf("client disconnected.\n");
        return 0;
    };

    while (true)
    {
        sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
        if (client_socket == -1)
        {
            continue;
        }

        printf("new client connected...\n");
        pid_t pid = fork();
        if (pid == -1)
        {
            close(client_socket);
            continue;
        }

        if (pid == 0)
        {
            handleConnection(client_socket);
        }
        close(client_socket);
    }
    close(server_socket);
    return 0;
}