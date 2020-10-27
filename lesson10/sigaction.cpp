#include <iostream>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM)
    {
        std::cout << "time out!\n";
    }
    alarm(2);
}

int main()
{
    struct sigaction action = {};
    action.sa_handler = timeout;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, nullptr);
    alarm(2);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "wait...\n";
        sleep(100);
    }
}