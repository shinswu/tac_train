cmake_minimum_required(VERSION 2.6)
project(divide)

# uncomment to build debug
#set(CMAKE_BUILD_TYPE Debug)
include_directories(src)
add_library(divide_me src/divide_me.c)
add_executable(test_me src/main.c)
target_link_libraries(test_me divide_me)

ENABLE_TESTING()
add_test(usage_test ${CMAKE_CURRENT_BINARY_DIR}/test_me -h)
add_test(test1 ${CMAKE_CURRENT_BINARY_DIR}/test_me 400 200 2)
add_test(test2 ${CMAKE_CURRENT_BINARY_DIR}/test_me 121 11  11)
add_test(test3 ${CMAKE_CURRENT_BINARY_DIR}/test_me 6120110403 3 100)
