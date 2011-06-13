cmake_minimum_required(VERSION 2.6)
project(vcdio)

add_definitions(-D${CMAKE_SYSTEM_NAME}=1)
# uncomment to build debug
#set(CMAKE_BUILD_TYPE Debug)
include_directories(src)
add_library(vcdio src/vcdio.c)
add_executable(vcdio_me src/main.c)
target_link_libraries(vcdio_me vcdio)
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  SET_TARGET_PROPERTIES(vcdio_me PROPERTIES LINK_FLAGS -lrt)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

ENABLE_TESTING()
add_test(usage_test ${CMAKE_CURRENT_BINARY_DIR}/vcdio_me -h)
add_test(test1 ${CMAKE_CURRENT_BINARY_DIR}/vcdio_me foobar.vcd)
add_test(test2 grep -i wire foobar.vcd)
