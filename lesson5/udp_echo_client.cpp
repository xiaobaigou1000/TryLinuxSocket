#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int client_socket = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    sockaddr_in server_address{};
    server_address.sin_family=AF_INET;
    
}