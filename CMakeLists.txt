cmake_minimum_required(VERSION 3.13)
project(ThreadPoolCPP)
set(PROJECT_NAME ThreadPoolCPP)

add_subdirectory(libThreadPool)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} threadPool)