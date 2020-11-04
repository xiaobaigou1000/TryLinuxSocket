#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main()
{
    auto errorHandle = [](const char *message) {
        puts(message);
        return -1;
    };

    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9120);

    if (bind(server_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        errorHandle("bind() error.");
    }
    if (listen(server_socket, 5) == -1)
    {
        errorHandle("listen() eror.");
    }
    int epoll_fd = epoll_create(INT32_MAX);
    std::vector<epoll_event> ep_events(16);
    epoll_event event{};
    event.data.fd = server_socket;
    event.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event);

    while (true)
    {
        int event_count = epoll_wait(epoll_fd, ep_events.data(), ep_events.size(), -1);
        if (event_count == -1)
        {
            errorHandle("epoll_wait() error.");
        }

        for (int i = 0; i < event_count; i++)
        {
            if (ep_events[i].data.fd == server_socket)
            {
                sockaddr_in client_address{};
                socklen_t client_address_size = sizeof(client_address);
                int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_size);
                if (client_socket == -1)
                {
                    continue;
                }
                epoll_event event{};
                event.events = EPOLLIN;
                event.data.fd = client_socket;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event);
                printf("Connected client: %d\n", client_socket);
            }
            else
            {
                std::vector<char> buffer(512);
                int str_len = read(ep_events[i].data.fd, buffer.data(), buffer.size());
                if (str_len == 0)
                {
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ep_events[i].data.fd, nullptr);
                    close(ep_events[i].data.fd);
                    printf("Closed client: %d\n", ep_events[i].data.fd);
                }
                else
                {
                    write(ep_events[i].data.fd, buffer.data(), str_len);
                }
            }
        }
    }
    close(server_socket);
    close(epoll_fd);
}