#include <iostream>
#include <unistd.h>

int main()
{
    int pipe_fds[2];
    std::string message = "Who are you?";

    char buffer[32];
    int result = pipe(pipe_fds);
    if (result != 0)
    {
        std::cerr << "create pipe failed.\n";
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        write(pipe_fds[1], message.data(), message.size());
    }
    else
    {
        int strLength = read(pipe_fds[0], buffer, 31);
        buffer[strLength] = 0;
        puts(buffer);
    }
    return 0;
}