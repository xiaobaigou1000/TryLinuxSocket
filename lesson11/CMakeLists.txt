cmake_minimum_required(VERSION 3.10)
project(InterProcessCommunication)

add_executable(SimplePipe simple_pipe.cpp)
add_executable(FullDuplexPipe full_duplex_pipe.cpp)