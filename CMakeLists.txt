cmake_minimum_required(VERSION 3.31)
project(opencv)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(opencv main.cpp)

target_link_libraries(opencv PRIVATE ${OpenCV_LIBS})