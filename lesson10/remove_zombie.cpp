#include <iostream>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        std::cout << "Removed proc id: " << pid << std::endl;
        std::cout << "Child send: " << WEXITSTATUS(status) << std::endl;
    }
}

int main()
{
    struct sigaction action = {};
    action.sa_handler = read_childproc;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGCHLD, &action, nullptr);

    pid_t pid = fork();
    if(pid==0)
    {
        printf("Child process run.\n");
        sleep(10);
        return 12;
    }

    printf("Child process id: %d\n",pid);
    pid = fork();
    if(pid==0)
    {
        printf("Child process run.\n");
        sleep(10);
        return 24;
    }

    printf("Child process id: %d\n",pid);
    for(int i=0;i<5;i++)
    {
        printf("wait...\n");
        sleep(5);
    }
}