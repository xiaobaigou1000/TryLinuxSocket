#include <spdlog/spdlog.h>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int client_count = 0;
std::vector<int> client_sockets;
pthread_mutex_t mutex;

void connect_client(int client_socket);
void remove_client(int client_socket);
void *handle_client(void *arg);
void send_message(const char *message, int len);

int main()
{
    auto errorHandle = [](const char *message) {
        spdlog::critical(message);
        return -1;
    };

    pthread_mutex_init(&mutex, nullptr);
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
        pthread_t th_id;
        pthread_create(&th_id, nullptr, handle_client, reinterpret_cast<void *>(&client_socket));
        pthread_detach(th_id);
        spdlog::info("new connection from: {}", inet_ntoa(client_address.sin_addr));
    }
}

void *handle_client(void *arg)
{
    int client_socket = *reinterpret_cast<int *>(arg);
    connect_client(client_socket);
    std::vector<char> buffer(512);
    int str_len = 0;
    while ((str_len = read(client_socket, buffer.data(), 512)) != 0)
    {
        send_message(buffer.data(), str_len);
    }
    remove_client(client_socket);
    close(client_socket);
    return nullptr;
}

void connect_client(int client_socket)
{
    pthread_mutex_lock(&mutex);
    client_sockets.push_back(client_socket);
    pthread_mutex_unlock(&mutex);
}

void remove_client(int client_socket)
{
    pthread_mutex_lock(&mutex);
    auto iter = std::find(client_sockets.begin(), client_sockets.end(), client_socket);
    if (iter != client_sockets.end())
    {
        client_sockets.erase(iter);
    }
    pthread_mutex_unlock(&mutex);
}

void send_message(const char *message, int len)
{
    pthread_mutex_lock(&mutex);
    for (const auto client : client_sockets)
    {
        write(client, message, len);
    }
    pthread_mutex_unlock(&mutex);
}
