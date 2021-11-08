cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)

set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.c *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})
target_link_libraries(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::GTest GTest::Main)
