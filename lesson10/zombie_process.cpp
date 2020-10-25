#include <unistd.h>
#include <iostream>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("I am a child process.\n");
    }
    else
    {
        printf("Child Process ID: %d\n", pid);
        sleep(30);
    }

    if (pid == 0)
    {
        printf("End of child process.\n");
    }
    else
    {
        printf("End of father process.\n");
    }
}