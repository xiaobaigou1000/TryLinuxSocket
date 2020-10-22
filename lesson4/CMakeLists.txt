cmake_minimum_required(VERSION 3.10)
project(CustomOperation)

add_executable(CustomOperationServer op_server.cpp)
add_executable(CustomOperationClient op_client.cpp)