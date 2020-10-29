#include <iostream>
#include <algorithm>
#include <vector>
#include <sys/uio.h>

int main()
{
    std::vector<char> buffer1(8);
    std::vector<char> buffer2(512);

    std::vector<iovec> vec;

    vec.push_back({const_cast<char *>(buffer1.data()), 5});
    vec.push_back({const_cast<char *>(buffer2.data()), buffer2.size()});

    int str_length = readv(0, vec.data(), vec.size());
    printf("Read bytes: %d\n", str_length);
    printf("First message: %s\n", buffer1.data());
    printf("Second message: %s\n", buffer2.data());
}