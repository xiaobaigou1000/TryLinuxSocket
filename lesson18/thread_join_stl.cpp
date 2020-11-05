#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void thread_main(int count, std::promise<std::string> &&promise)
{
    for (int i = 0; i < count; i++)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        puts("running thread.");
    }
    promise.set_value(std::string("Hello,I'm a thread."));
}

int main()
{
    std::promise<std::string> promise;
    auto future = promise.get_future();
    std::thread tha{thread_main, 5, std::move(promise)};
    tha.join();
    std::cout << future.get() << std::endl;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    std::cout << "exit of main.\n";
}