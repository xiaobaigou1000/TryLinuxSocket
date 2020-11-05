#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int source_fd = open("source.txt", O_RDONLY);
    int destiny_fd = open("destiny.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IFREG);

    int length = 0;
    std::vector<char> buffer(512);
    while ((length = read(source_fd, buffer.data(), 512)) != 0)
    {
        write(destiny_fd, buffer.data(), length);
    }
    close(source_fd);
    close(destiny_fd);
}