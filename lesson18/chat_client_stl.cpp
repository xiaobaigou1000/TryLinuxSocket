#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

int main(int argc, char **argv)
{
    auto receiveMessage = [](const int client_socket) {
        std::vector<char> buffer(512);
        while (true)
        {
            int str_len = read(client_socket, buffer.data(), 512);
            spdlog::debug(str_len);
            if (str_len == 0)
            {
                spdlog::info("connection closed");
                return;
            }
            buffer[str_len] = 0;
            spdlog::info("{}", buffer.data());
        }
    };

    spdlog::set_level(spdlog::level::info);
    std::vector<char> userName(32);

    auto sendMessage = [&userName](const int client_socket) {
        while (true)
        {
            std::vector<char> inputStrBuffer(512);
            std::cin.getline(inputStrBuffer.data(), 512);
            spdlog::debug(inputStrBuffer.data());
            if (std::string_view(inputStrBuffer.data()) == "q" || std::string_view(inputStrBuffer.data()) == "Q")
            {
                spdlog::debug("close client");
                shutdown(client_socket, SHUT_WR);
                close(client_socket);
                return 0;
            }
            std::vector<char> buffer(512);
            auto str_len = fmt::format_to_n(buffer.data(), 512, "{} {}", userName.data(), inputStrBuffer.data());
            spdlog::debug(buffer.data());
            write(client_socket, buffer.data(), str_len.size);
        }
    };

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

    std::thread sendThread{sendMessage, client_socket};
    std::thread receiveThread{receiveMessage, client_socket};
    sendThread.join();
    receiveThread.join();

    return 0;
}
