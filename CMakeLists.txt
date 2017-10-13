cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
cmake_policy(VERSION 2.8.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -Wpedantic -Wextra -Wno-unused-parameter -std=c++11 -fexceptions -g -m64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Wall -Wpedantic -Wextra -Wno-unused-parameter -std=c11 -g -m64")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DDISABLE_BOUNDS_CHECKS")

set(AERON_CLIENT_SOURCE_PATH "${CMAKE_SOURCE_DIR}/aeron-client")

file(GLOB AERON_CLIENT_SOURCE
    "${AERON_CLIENT_SOURCE_PATH}/*.cpp"
    "${AERON_CLIENT_SOURCE_PATH}/util/*.cpp"
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/aeron-client)
set(CGO_SOURCE
    aeron.cpp
    ${AERON_CLIENT_SOURCE})

add_library(aeron_client_cgo STATIC ${CGO_SOURCE})

add_executable(aeron_test
    aeron_test.cpp
    ${CGO_SOURCE})

target_link_libraries(aeron_test
    aeron_client_cgo
    pthread
    )
