cmake_minimum_required(VERSION 3.10)
project(SimpleFileServer)

add_executable(SimpleFileServer file_server.cpp)
add_executable(SimpleFileClient file_client.cpp)