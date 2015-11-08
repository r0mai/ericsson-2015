cmake_minimum_required(VERSION 2.8)

project(ericsson-2015)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost)
find_package(Protobuf)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(src)

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -O0")
endif()

aux_source_directory(bin BIN_SOURCES)
aux_source_directory(src SRC_SOURCES)
aux_source_directory(test TEST_SOURCES)

add_library(libdoki STATIC ${SRC_SOURCES})
target_link_libraries(libdoki ${PROTOBUF_LIBRARIES})

add_executable(doki ${BIN_SOURCES})
target_link_libraries(doki libdoki)

add_executable(test_doki ${TEST_SOURCES})
target_link_libraries(test_doki libdoki)
