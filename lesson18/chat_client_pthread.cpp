#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

std::vector<char> userName;
void *send_message(void *arg);
void *receive_message(void *arg);

int main(int argc, char **argv)
{
    spdlog::set_level(spdlog::level::debug);
    userName.resize(32);
    if (argc != 2)
    {
        spdlog::critical("Usage: {} <user_name>", argv[0]);
        return -1;
    }

    fmt::format_to_n(userName.data(), userName.size(), "[{}]", argv[1]);

    int client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9120);

    if (connect(client_socket, reinterpret_cast<const sockaddr *>(&server_address), sizeof(server_address)) == -1)
    {
        spdlog::critical("connect() failed.");
        return -1;
    }

    pthread_t send_thread{};
    pthread_t receive_thread{};
    pthread_create(&send_thread, nullptr, send_message, reinterpret_cast<void *>(&client_socket));
    pthread_create(&receive_thread, nullptr, receive_message, reinterpret_cast<void *>(&client_socket));
    pthread_join(send_thread, nullptr);
    pthread_join(receive_thread, nullptr);
    return 0;
}

void *send_message(void *arg)
{
    int client_socket = *reinterpret_cast<int *>(arg);
    while (true)
    {
        std::vector<char> inputStrBuffer(512);
        std::cin.getline(inputStrBuffer.data(), 512);
        spdlog::debug(inputStrBuffer.data());
        if (std::string_view(inputStrBuffer.data()) == "q" || std::string_view(inputStrBuffer.data()) == "Q")
        {
            close(client_socket);
            return 0;
        }
        std::vector<char> buffer(512);
        auto str_len = fmt::format_to_n(buffer.data(), 512, "{} {}", userName.data(), inputStrBuffer.data());
        spdlog::debug(buffer.data());
        write(client_socket, buffer.data(), str_len.size);
    }
}

void *receive_message(void *arg)
{
    int client_socket = *reinterpret_cast<int *>(arg);
    std::vector<char> buffer(512);
    while (true)
    {
        int str_len = read(client_socket, buffer.data(), 512);
        if (str_len == -1)
        {
            spdlog::debug("connection closed");
            return reinterpret_cast<void *>(-1);
        }
        buffer[str_len] = 0;
        spdlog::info("{}", buffer.data());
    }
    return nullptr;
}