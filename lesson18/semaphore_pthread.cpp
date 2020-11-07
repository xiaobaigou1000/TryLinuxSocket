#include <iostream>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_one;
sem_t sem_two;
int num;

void *read(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        fputs("Input num: ", stdout);
        sem_wait(&sem_two);
        std::cin >> num;
        sem_post(&sem_one);
    }
    return nullptr;
}

void *accu(void *arg)
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sem_wait(&sem_one);
        sum += num;
        sem_post(&sem_two);
    }
    printf("Result: %d\n", sum);
    return nullptr;
}

int main()
{
    sem_init(&sem_one, 0, 0);
    sem_init(&sem_two, 0, 1);
    pthread_t id_th1, id_th2;
    pthread_create(&id_th1, nullptr, read, nullptr);
    pthread_create(&id_th2, nullptr, accu, nullptr);

    pthread_join(id_th1, nullptr);
    pthread_join(id_th2, nullptr);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}