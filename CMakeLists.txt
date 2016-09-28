cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(lat CXX)

find_package(LibArchive REQUIRED)

include_directories(${LibArchive_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LibArchive_LIBRARIES})
