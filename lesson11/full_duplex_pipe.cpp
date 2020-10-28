#include <iostream>
#include <unistd.h>

int main()
{
    int fatherToChild[2], childToFather[2];
    pipe(fatherToChild);
    pipe(childToFather);
    std::string strToFather = "Who are you?";
    std::string strToChild = "Thank you for your message.";
    char buffer[64];

    pid_t pid = fork();
    if (pid == 0)
    {
        write(childToFather[1], strToFather.data(), strToFather.size());
        int length = read(fatherToChild[0], buffer, 63);
        buffer[length] = 0;
        printf("Child process output: %s\n", buffer);
    }
    else
    {
        write(fatherToChild[1], strToChild.data(), strToChild.size());
        int length = read(childToFather[0], buffer, 64);
        buffer[length] = 0;
        printf("Father process output: %s\n", buffer);
    }
    return 0;
}