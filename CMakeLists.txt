cmake_minimum_required(VERSION 3.31)

project(BetterDocs)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

add_executable(BetterDocs
        main.cpp
        ProcessadorImagem.cpp
)

target_link_libraries(BetterDocs
        ${OpenCV_LIBS}
)