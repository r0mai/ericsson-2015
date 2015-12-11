cmake_minimum_required(VERSION 2.8)

project(ericsson-2015)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost)
find_package(Protobuf)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -O0")
endif()

aux_source_directory(final SRC_SOURCES)

add_executable(doki ${SRC_SOURCES})
target_link_libraries(doki ${PROTOBUF_LIBRARIES})
