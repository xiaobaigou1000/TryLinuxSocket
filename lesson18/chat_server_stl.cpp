#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

class ClientSocketsPool
{
public:
    void connect_client(const int client_socket)
    {
        std::lock_guard<std::mutex> lock(mutex);
        client_sockets.push_back(client_socket);
    }

    void remove_client(const int client_socket)
    {
        std::lock_guard<std::mutex> lock(mutex);
        auto iter = std::find(client_sockets.begin(), client_sockets.end(), client_socket);
        if (iter != client_sockets.end())
        {
            client_sockets.erase(iter);
        }
    }

    void broadcastMessage(const char *message, int len)
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (const auto client : client_sockets)
        {
            write(client, message, len);
        }
    }

private:
    std::vector<int> client_sockets;
    std::mutex mutex;
};

int main()
{
    auto errorHandle = [](const char *message) {
        spdlog::critical(message);
        return -1;
    };

    ClientSocketsPool clientSocketsPool;

    auto handleClient = [&clientSocketsPool](const int client_socket) {
        clientSocketsPool.connect_client(client_socket);
        std::vector<char> buffer(512);
        int str_len = 0;
        while ((str_len = read(client_socket, buffer.data(), 512)) != 0)
        {
            clientSocketsPool.broadcastMessage(buffer.data(), str_len);
        }
        clientSocketsPool.remove_client(client_socket);
        close(client_socket);
        spdlog::info("connection closed.");
        return nullptr;
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
        errorHandle("listen() error.");
    }

    while (true)
    {
        sockaddr_in client_address{};
        socklen_t client_address_length = sizeof(client_address);
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr *>(&client_address), &client_address_length);
        if (client_socket == -1)
        {
            spdlog::critical("accept() error.");
            continue;
        }
        std::thread clientHandleThread{handleClient, client_socket};
        clientHandleThread.detach();
        spdlog::info("new connection from: {}", inet_ntoa(client_address.sin_addr));
    }
}
