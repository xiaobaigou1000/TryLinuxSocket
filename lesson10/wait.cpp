#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        exit(3);
    }

    pid = fork();
    if (pid == 0)
    {
        exit(7);
    }

    std::cout << "Child process id: " << pid << std::endl;
    wait(&status);
    if (WIFEXITED(status))
    {
        std::cout << "Child process send: " << WEXITSTATUS(status) << std::endl;
    }

    wait(&status);
    if (WIFEXITED(status))
    {
        std::cout << "Child process send: " << WEXITSTATUS(status) << std::endl;
    }
    sleep(30);
    return 0;
}