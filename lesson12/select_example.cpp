#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <vector>

int main()
{
    fd_set reads, temps;
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    while (true)
    {
        temps = reads;
        timeval timeout{};
        timeout.tv_sec = 5;
        timeout.tv_usec = 500;
        int result = select(1, &temps, nullptr, nullptr, &timeout);
        //no timeout version
        // int result = select(1, &temps, nullptr, nullptr, nullptr);
        if (result == -1)
        {
            printf("select() error.\n");
        }
        if (result == 0)
        {
            printf("time out.\n");
            continue;
        }

        if (FD_ISSET(0, &temps))
        {
            std::vector<char> buffer(512);
            int str_length = read(0, buffer.data(), 511);
            buffer[str_length] = 0;
            printf("Message from console: %s\n", buffer.data());
        }
    }
    return 0;
}