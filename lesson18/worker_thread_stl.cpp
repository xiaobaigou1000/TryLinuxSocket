#include <iostream>
#include <thread>
#include <future>

int thread_summuation(int start, int end)
{
    int sum = 0;
    while (start <= end)
    {
        sum += start;
        ++start;
    }
    return sum;
}

int main()
{
    auto tha_sum_future = std::async(thread_summuation, 1, 5);
    auto thb_sum_future = std::async(thread_summuation, 6, 10);
    int sum = 0;
    sum += tha_sum_future.get();
    sum += thb_sum_future.get();
    std::cout << sum << std::endl;
}