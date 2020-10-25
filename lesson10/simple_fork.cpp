#include <iostream>
#include <unistd.h>

int main()
{
    int value = 20;

    pid_t pid = fork();
    if (pid == 0)
    {
        value += 20;
    }
    else
    {
        value -= 10;
    }

    if (pid == 0)
    {
        printf("Child process: %d\n", value);
    }
    else
    {
        printf("Father process: %d\n", value);
    }
}