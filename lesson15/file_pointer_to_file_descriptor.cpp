#include <cstdio>
#include <fcntl.h>

int main()
{
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IFREG);
    if (fd == -1)
    {
        fputs("file open error.", stdout);
        return -1;
    }

    printf("First file descriptor: %d\n", fd);
    FILE *fp = fdopen(fd, "w");
    fputs("TCP/IP socket programming.\n", fp);
    printf("Second file descriptor: %d\n", fileno(fp));
    fclose(fp);
    return 0;
}