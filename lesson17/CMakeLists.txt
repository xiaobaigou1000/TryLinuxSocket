cmake_minimum_required(VERSION 3.10)
project(TryEpoll)

add_executable(TryEpollServer try_epoll_server.cpp)

add_executable(LevelTrigger level_trigger_server.cpp)