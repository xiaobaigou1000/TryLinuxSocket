#include <iostream>
#include <sys/uio.h>
#include <vector>

int main()
{
    std::vector<iovec> vec;
    std::string buf1("ABCDEFG");
    std::string buf2("1234567");

    iovec temp;
    temp.iov_base = const_cast<char *>(buf1.data());
    temp.iov_len = buf1.size();
    vec.push_back(temp);

    temp.iov_base = const_cast<char *>(buf2.data());
    temp.iov_len = buf2.size();
    vec.push_back(temp);

    int str_length = writev(1, vec.data(), vec.size());
    puts("");
    printf("Write bytes: %d\n", str_length);
}