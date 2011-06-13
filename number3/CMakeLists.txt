cmake_minimum_required(VERSION 2.6)
project(factors)

# uncomment to build debug
#set(CMAKE_BUILD_TYPE Debug)
include_directories(src)
add_library(factors src/factors.c)
add_executable(factor_me src/main.c)
target_link_libraries(factor_me factors)
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  SET_TARGET_PROPERTIES(factor_me PROPERTIES LINK_FLAGS -lm)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

ENABLE_TESTING()
add_test(usage_test ${CMAKE_CURRENT_BINARY_DIR}/factor_me -h)
add_test(test1 ${CMAKE_CURRENT_BINARY_DIR}/factor_me 3273)
add_test(test2 ${CMAKE_CURRENT_BINARY_DIR}/factor_me 80030004003271)
add_test(test3 ${CMAKE_CURRENT_BINARY_DIR}/factor_me 800300040303271)
