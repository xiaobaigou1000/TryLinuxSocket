cmake_minimum_required(VERSION 3.10)
project(TryLinuxProcess)

add_executable(SimpleFork simple_fork.cpp)
add_executable(ZombieProcess zombie_process.cpp)
add_executable(WaitProcessReturnValue wait.cpp)
add_executable(WaitProcessReturnValueByPID waitpid.cpp)