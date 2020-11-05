#include <iostream>
#include <thread>
#include <chrono>

int thread_main(int count)
{
    for (int i = 0; i < count; i++)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        puts("running thread.");
    }
    return 0;
}

int main()
{
    using namespace std::chrono_literals;
    std::thread tha{thread_main, 5};
    std::this_thread::sleep_for(10s);
    puts("end of main.");
}