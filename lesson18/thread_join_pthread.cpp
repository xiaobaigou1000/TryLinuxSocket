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
    std::string *message = new std::string("Hello, I'am a thread.");
    return reinterpret_cast<void *>(message);
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
    void *thread_ret;
    pthread_join(thread_id, &thread_ret);
    std::string *thread_return_string_pointer = reinterpret_cast<std::string *>(thread_ret);
    printf("Thread return message: %s\n", thread_return_string_pointer->c_str());
    delete thread_return_string_pointer;
    sleep(2);
    puts("end of main");
}