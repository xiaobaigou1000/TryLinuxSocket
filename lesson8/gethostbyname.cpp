#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
    hostent *host;
    host = gethostbyname("www.baidu.com");
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