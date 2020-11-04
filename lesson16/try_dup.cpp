#include <iostream>
#include <string_view>
#include <unistd.h>

int main()
{
    constexpr std::string_view str1 = "Hi~\n";
    constexpr std::string_view str2 = "It's nice day~\n";

    int copy_of_stdout_fd = dup(1);
    int copy_of_copy_fd_with_specified_fd_value = dup2(copy_of_stdout_fd, 17);

    std::cout << "copy_of_stdout_fd: " << copy_of_stdout_fd
              << ", copy_of_copy_fd_with_specified_fd_value: " << copy_of_copy_fd_with_specified_fd_value
              << std::endl;

    write(copy_of_stdout_fd, str1.data(), str1.size());
    write(copy_of_copy_fd_with_specified_fd_value, str2.data(), str2.size());

    close(copy_of_copy_fd_with_specified_fd_value);
    close(copy_of_stdout_fd);

    write(1, str1.data(), str1.size());
    close(1);
    write(1, str2.data(), str2.size());
}