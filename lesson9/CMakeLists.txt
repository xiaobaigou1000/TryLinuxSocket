cmake_minimum_required(VERSION 3.10)
project(SocketOptions)

add_executable(GetSocketType get_socket_type.cpp)
add_executable(GetTCPSocketBufferSize get_tcp_socket_buffer_size.cpp)
add_executable(SetTCPSocketBufferSize set_tcp_socket_buffer_size.cpp)
add_executable(TcpReuseAddressServer tcp_reuse_addr_server.cpp)
add_executable(TcpReuseAddressClient tcp_reuse_addr_client.cpp)