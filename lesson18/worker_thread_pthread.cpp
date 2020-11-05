#include <pthread.h>
#include <iostream>

void *thread_summuation(void *arg)
{
    int start = reinterpret_cast<int *>(arg)[0];
    int end = reinterpret_cast<int *>(arg)[1];

    int *sum = new int{0};
    while (start <= end)
    {
        *sum += start;
        ++start;
    }
    return reinterpret_cast<void *>(sum);
}

int main()
{
    int sum = 0;
    int range1[] = {1, 5};
    int range2[] = {6, 10};
    pthread_t tha, thb;
    pthread_create(&tha, nullptr, thread_summuation, reinterpret_cast<void *>(range1));
    pthread_create(&thb, nullptr, thread_summuation, reinterpret_cast<void *>(range2));

    void *th_result = 0;
    pthread_join(tha, &th_result);
    sum += *reinterpret_cast<int *>(th_result);
    delete reinterpret_cast<int *>(th_result);
    pthread_join(thb, &th_result);
    sum += *reinterpret_cast<int *>(th_result);
    delete reinterpret_cast<int *>(th_result);

    std::cout << sum << std::endl;
}