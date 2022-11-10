cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab1 VERSION 0.1.0)

set(SRC_FILES
        "${CMAKE_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_SOURCE_DIR}/src/Maze.cpp")

add_executable(lab1 ${SRC_FILES})

target_include_directories(lab1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
