#include <pthread.h>
#include <unistd.h>
#include <iostream>

void *thread_main(void *arg)
{
    int count = *reinterpret_cast<int *>(arg);
    for (int i = 0; i < count; i++)
    {
        sleep(1);
        puts("running thread.");
    }
    return 0;
}

int main()
{
    pthread_t thread_id;
    int param = 5;
    if (pthread_create(&thread_id, nullptr, thread_main, reinterpret_cast<void *>(&param)) != 0)
    {
        puts("pthread create error.");
        return -1;
    }
    sleep(10);
    puts("end of main");
}