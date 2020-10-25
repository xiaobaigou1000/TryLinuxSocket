#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    auto errorHandle = [tcp_socket](const char *message) {
        std::cerr << message << std::endl;
        close(tcp_socket);
        return 0;
    };

    int state;
    int receive_buffer_size = 3 * 1024;
    int send_buffer_size = 3 * 1024;
    state = setsockopt(tcp_socket, SOL_SOCKET, SO_RCVBUF, &receive_buffer_size, sizeof(receive_buffer_size));
    if (state)
    {
        errorHandle("setsockopt() failed.\n");
    }

    state = setsockopt(tcp_socket, SOL_SOCKET, SO_SNDBUF, &send_buffer_size, sizeof(send_buffer_size));
    if (state)
    {
        errorHandle("setsockopt() failed.\n");
    }

    socklen_t buffer_size_length = sizeof(receive_buffer_size);
    state = getsockopt(tcp_socket, SOL_SOCKET, SO_RCVBUF, &receive_buffer_size, &buffer_size_length);
    if (state)
    {
        errorHandle("getsockopt() failed.\n");
    }

    state = getsockopt(tcp_socket, SOL_SOCKET, SO_SNDBUF, &send_buffer_size, &buffer_size_length);
    if (state)
    {
        errorHandle("getsockopt() failed.\n");
    }

    std::cout << "Receive buffer size: " << receive_buffer_size << std::endl;
    std::cout << "Send buffer size: " << send_buffer_size << std::endl;
    close(tcp_socket);
}