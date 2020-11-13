cmake_minimum_required(VERSION 3.10)
project(MultiThread)

find_package(Threads)
find_package(spdlog)

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

add_executable(Mutex_Pthread mutex_pthread.cpp)
target_link_libraries(Mutex_Pthread PRIVATE Threads::Threads)
add_executable(Mutex_STL mutex_stl.cpp)
target_link_libraries(Mutex_STL PRIVATE Threads::Threads)

add_executable(Semaphore_Pthread semaphore_pthread.cpp)
target_link_libraries(Semaphore_Pthread PRIVATE Threads::Threads)
add_executable(ConditionVariable_STL condition_variable_stl.cpp)
target_link_libraries(ConditionVariable_STL PRIVATE Threads::Threads)

add_executable(ChatServer_Pthread chat_server_pthread.cpp)
target_link_libraries(ChatServer_Pthread PRIVATE Threads::Threads spdlog::spdlog)
add_executable(ChatClient_Pthread chat_client_pthread.cpp)
target_link_libraries(ChatClient_Pthread PRIVATE Threads::Threads spdlog::spdlog)
target_compile_features(ChatClient_Pthread PRIVATE cxx_std_17)

add_executable(ChatServer_STL chat_server_stl.cpp)
target_link_libraries(ChatServer_STL PRIVATE Threads::Threads spdlog::spdlog)
target_compile_features(ChatServer_STL PRIVATE cxx_std_17)
add_executable(ChatClient_STL chat_client_stl.cpp)
target_link_libraries(ChatClient_STL PRIVATE Threads::Threads spdlog::spdlog)
target_compile_features(ChatClient_STL PRIVATE cxx_std_17)