cmake_minimum_required(VERSION 3.16)

find_package(absl CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)
add_executable(my_exe engine.cpp) 
target_link_libraries(my_exe gRPC::grpc++)
