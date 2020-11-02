#include <cstdio>
#include <fcntl.h>

int main()
{
    int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        fputs("file open error", stdout);
        return -1;
    }

    FILE *fp = fdopen(fd, "w");
    fputs("Network C++ programming\n", fp);
    fclose(fp);
    return 0;
}