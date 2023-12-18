cmake_minimum_required(VERSION 3.10.2)
project(SHELL C)

set(CMAKE_C_STANDARD 99)
find_package(Threads REQUIRED)

add_executable(SHELL shell.c
        include/shell.h
        command_executor.c
        include/command_executor.h
        command_parser.c
        include/command_parser.h
)
target_link_libraries(${PROJECT_NAME} Threads::Threads)