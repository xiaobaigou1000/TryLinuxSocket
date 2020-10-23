#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    hostent *host;
    sockaddr_in server_address{};
    server_address.sin_family=AF_INET;
    server_address.sin_addr.s_addr=inet_addr("39.156.66.14");
    
    host=gethostbyaddr(&server_address,sizeof(server_address),AF_INET);

    if (host == nullptr)
    {
        std::cerr << "get host failed.\n";
        return 0;
    }

    std::cout << "Official name: " << host->h_name << std::endl;
    for (int i = 0; host->h_aliases[i]; i++)
    {
        std::cout << "Aliases " << i << ": " << host->h_aliases[i] << std::endl;
    }
    std::cout << "Address type: " << ((host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6") << std::endl;
    for (int i = 0; host->h_addr_list[i]; i++)
    {
        std::cout << "IP address " << i << ": " << inet_ntoa(*reinterpret_cast<in_addr *>(host->h_addr_list[i])) << std::endl;
    }
}