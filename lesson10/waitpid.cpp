#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid = fork();
    if (pid == 0)
    {
        sleep(15);
        exit(15);
    }

    while (!waitpid(pid, &status, WNOHANG))
    {
        sleep(3);
        std::cout << "Sleep 3s.\n";
    }

    if (WIFEXITED(status))
    {
        std::cout << "Child process send: " << WEXITSTATUS(status) << std::endl;
    }
}