cmake_minimum_required(VERSION "3.10.1")

project(algorithm LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

if(UNIX)
elseif(WIN32)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(algorithm ${SOURCES})
