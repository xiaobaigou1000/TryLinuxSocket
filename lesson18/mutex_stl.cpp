#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>

int main()
{
    int sum = 0;
    std::mutex mutex;
    auto thread_inc = [&sum, &mutex]() {
        std::lock_guard<std::mutex> lock_gurard(mutex);
        for (int i = 0; i < 5000000; i++)
        {
            sum += 1;
        }
    };
    auto thread_dec = [&sum, &mutex]() {
        std::lock_guard<std::mutex> lock_guard(mutex);
        for (int i = 0; i < 5000000; i++)
        {
            sum -= 1;
        }
    };
    
    std::vector<std::thread> ths(128);
    for (int i = 0; i < ths.size(); i++)
    {
        if (i % 2)
        {
            ths[i] = std::thread{thread_inc};
        }
        else
        {
            ths[i] = std::thread{thread_dec};
        }
    }
    for (auto &i : ths)
    {
        i.join();
    }
    std::cout << "Result: " << sum << std::endl;
}