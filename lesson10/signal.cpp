#include<iostream>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
    if(sig==SIGALRM)
    {
        std::cout<<"Time out.\n";
    }
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig==SIGINT)
    {
        std::cout<<"Ctrl + C pressed.\n";
    }
}

int main()
{
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);

    for(int i=0;i<3;i++)
    {
        std::cout<<"wait...\n";
        sleep(100); //实际由信号处理唤醒，不会睡眠100s
    }
}