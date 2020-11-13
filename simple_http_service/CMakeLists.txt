cmake_minimum_required(VERSION 3.10)
project(SimpleHttpService)

find_package(spdlog)
find_package(Threads)

add_executable(SimpleHttpService main.cpp simple_server_socket.cpp simple_http_service.cpp)
target_include_directories(SimpleHttpService PRIVATE include)
target_link_libraries(SimpleHttpService PRIVATE Threads::Threads spdlog::spdlog)
target_compile_features(SimpleHttpService PRIVATE cxx_std_17)