#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int tcp_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    auto errorHandle = [tcp_socket](const char *message) {
        std::cout << message << std::endl;
        close(tcp_socket);
    };

    int send_buffer_size, read_buffer_size, getopt_func_state;
    socklen_t optValueSize = sizeof(send_buffer_size);

    getopt_func_state = getsockopt(tcp_socket, SOL_SOCKET, SO_SNDBUF, &send_buffer_size, &optValueSize);
    if (getopt_func_state)
    {
        errorHandle("getsockopt() error.\n");
    }
    std::cout<<"TCP socket send buffer size: "<<send_buffer_size<<std::endl;

    getopt_func_state=getsockopt(tcp_socket,SOL_SOCKET,SO_RCVBUF,&read_buffer_size,&optValueSize);
}