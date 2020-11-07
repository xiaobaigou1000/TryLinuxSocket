#include <iostream>
#include <thread>
#include <condition_variable>

int main()
{
    std::mutex resource;
    std::condition_variable cv_read;
    std::condition_variable cv_accu;
    bool num_ready = false;
    bool num_processed = true;
    int num;

    auto read = [&] {
        for (int i = 0; i < 5; i++)
        {
            std::unique_lock<std::mutex> lock(resource);
            cv_read.wait(lock, [&] { return num_processed; });
            std::cout << "Input num: ";
            std::cin >> num;
            num_ready = true;
            num_processed = false;
            cv_accu.notify_one();
        }
    };

    auto accu = [&] {
        int sum = 0;
        for (int i = 0; i < 5; i++)
        {
            std::unique_lock<std::mutex> lock(resource);
            cv_accu.wait(lock, [&] { return num_ready; });
            sum += num;
            num_ready = false;
            num_processed = true;
            cv_read.notify_one();
        }
        std::cout << "Result: " << sum << std::endl;
    };

    std::thread tha(read);
    std::thread thb(accu);
    tha.join();
    thb.join();
}