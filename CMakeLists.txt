cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
cmake_policy(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wpedantic -Wextra -Wno-unused-parameter -std=c++11 -fexceptions -g -m64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Wall -Wpedantic -Wextra -Wno-unused-parameter -std=c11 -g -m64")

set(AERON_CLIENT_SOURCE_PATH "${CMAKE_SOURCE_DIR}/aeron-client")

add_subdirectory(${AERON_CLIENT_SOURCE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/aeron-client)
set(SOURCE
    aeron.cpp)

add_library(aeron_client_cgo STATIC ${SOURCE})
