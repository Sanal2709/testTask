cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.h *.c *.cpp)

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
