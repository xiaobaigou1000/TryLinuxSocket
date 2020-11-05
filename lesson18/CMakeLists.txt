cmake_minimum_required(VERSION 3.10)
project(MultiThread)

find_package(Threads)

add_executable(CreateThread_Pthread create_thread_pthread.cpp)
target_link_libraries(CreateThread_Pthread PRIVATE Threads::Threads)
add_executable(CreateThread_STL create_thread_stl.cpp)
target_link_libraries(CreateThread_STL PRIVATE Threads::Threads)

add_executable(ThreadJoin_Pthread thread_join_pthread.cpp)
target_link_libraries(ThreadJoin_Pthread PRIVATE Threads::Threads)
add_executable(ThreadJoin_STL thread_join_stl.cpp)
target_link_libraries(ThreadJoin_STL PRIVATE Threads::Threads)

add_executable(WorkerThreadModel_Pthread worker_thread_pthread.cpp)
target_link_libraries(WorkerThreadModel_Pthread PRIVATE Threads::Threads)
add_executable(WorkerThreadModel_STL worker_thread_stl.cpp)
target_link_libraries(WorkerThreadModel_STL PRIVATE Threads::Threads)