#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>

int main()
{
    //此处代码正确性未知，OOBSender无法正常发包，此处无法触发SIGURG信号
    auto urgent_message_handler = [](int signo, siginfo_t *info, void *ucontext) {
        std::vector<char> buffer(512);
        int receiver_socket = info->si_fd;
        int str_len = recv(receiver_socket, buffer.data(), 511, MSG_OOB);
        buffer[str_len] = 0;
        printf("Urgent message: %s\n", buffer.data());
    };

    auto errorHandle = [](const char *message) {
        puts(message);
        exit(1);
    };

    int accept_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    if (bind(accept_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        errorHandle("bind() error.");
    }

    if (listen(accept_socket, 5) == -1)
    {
        errorHandle("listen() failed.");
    }

    sockaddr_in client_address{};
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(accept_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);

    int state;
    state = fcntl(client_socket, F_SETOWN, getpid());
    if (state != 0)
    {
        errorHandle("fcntl() error.");
    }

    struct sigaction action
    {
    };
    action.sa_sigaction = urgent_message_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    state = sigaction(SIGURG, &action, nullptr);
    if (state != 0)
    {
        errorHandle("sigaction() error.");
    }

    int str_length;
    std::vector<char> buffer(512);
    while ((str_length = recv(client_socket, buffer.data(), 511, 0)) != 0)
    {
        if (str_length == -1)
        {
            continue;
        }
        buffer[str_length] = 0;
        puts(buffer.data());
    }
    close(client_socket);
    close(accept_socket);
}