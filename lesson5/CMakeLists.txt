cmake_minimum_required(VERSION 3.10)
project(FirstUDP)

add_executable(FirstUDPServer udp_echo_server.cpp)
add_executable(FirstUDPClient udp_echo_client.cpp)