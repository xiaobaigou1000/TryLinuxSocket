cmake_minimum_required(VERSION 3.10)
project(IOFunctions)

# 失败的代码，OOBSender无法正确发送MSG_OOB包，故OOBReceiver无法正常触发SIGURG信号，接收部分代码正确性未知

add_executable(OOBSender oob_sender.cpp)
add_executable(OOBReceiver oob_receiver.cpp)