cmake_minimum_required(VERSION 3.31)

project(MELHORARDOC)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV CONFIG REQUIRED)

add_executable(MELHORARDOC main.cpp)

target_link_libraries(MELHORARDOC PRIVATE opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)