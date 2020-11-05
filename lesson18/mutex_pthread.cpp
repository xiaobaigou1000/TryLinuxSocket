#include <pthread.h>
#include <cstdio>
#include <vector>

int sum = 0;
pthread_mutex_t mutex{};

void *thread_inc(void *arg)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5000000; i++)
    {
        sum += 1;
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

void *thread_dec(void *arg)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5000000; i++)
    {
        sum -= 1;
    }
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

int main()
{
    pthread_mutex_init(&mutex, nullptr);
    std::vector<pthread_t> ths(128);
    for (size_t i = 0; i < ths.size(); i++)
    {
        if (i % 2)
        {
            pthread_create(&ths[i], nullptr, thread_inc, nullptr);
        }
        else
        {
            pthread_create(&ths[i], nullptr, thread_dec, nullptr);
        }
    }
    for (size_t i = 0; i < ths.size(); i++)
    {
        pthread_join(ths[i], nullptr);
    }
    printf("Result: %d\n", sum);
    pthread_mutex_destroy(&mutex);
    return 0;
}