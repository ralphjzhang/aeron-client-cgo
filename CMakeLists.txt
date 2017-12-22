cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
cmake_policy(VERSION 2.8.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wall -std=c++11 -fexceptions -g -m64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -Wall -std=c11 -g -m64")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DDISABLE_BOUNDS_CHECKS")

SET(AERON_CLIENT_SOURCE
    aeron-client/Publication.cpp
    aeron-client/ExclusivePublication.cpp
    aeron-client/Subscription.cpp
    aeron-client/ClientConductor.cpp
    aeron-client/Aeron.cpp
    aeron-client/LogBuffers.cpp
    aeron-client/util/MemoryMappedFile.cpp
    aeron-client/util/CommandOption.cpp
    aeron-client/util/CommandOptionParser.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/aeron-client)
set(CGO_SOURCE
    aeron.cpp
    ${AERON_CLIENT_SOURCE})

add_library(aeron_client_cgo STATIC ${CGO_SOURCE})

add_executable(aeron_test
    aeron_test.cpp
    #sub.cpp
    ${CGO_SOURCE})

target_link_libraries(aeron_test
    aeron_client_cgo
    pthread
    )
