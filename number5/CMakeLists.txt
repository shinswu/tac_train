cmake_minimum_required(VERSION 2.6)
project(cube)

add_definitions(-D${CMAKE_SYSTEM_NAME}=1)
# uncomment to build debug
#set(CMAKE_BUILD_TYPE Debug)
add_executable(cube_me src/cube.c)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  SET(GL_INCLUDE_DIR /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/Headers)
  SET(GLUT_INCLUDE_DIR /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/GLUT.framework/Headers)
  SET(GL_LIB /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL)
  SET(GLUT_LIB /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/GLUT.framework/GLUT)
  SET_TARGET_PROPERTIES(cube_me PROPERTIES LINK_FLAGS "${GL_LIB} ${GLUT_LIB}")
endif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  SET(GL_INCLUDE_DIR /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/OpenGL.framework/Headers)
  SET(GLUT_INCLUDE_DIR /Developer/SDKs/MacOSX10.6.sdk/System/Library/Frameworks/GLUT.framework/Headers)
  SET(GL_LIB -lGL)
  SET(GLUT_LIB -lglut)
  SET(GLU_LIB -lGLU)
  SET_TARGET_PROPERTIES(cube_me PROPERTIES LINK_FLAGS "${GL_LIB} ${GLUT_LIB} ${GLU_LIB}")
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

include_directories(src ${GL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})


ENABLE_TESTING()
