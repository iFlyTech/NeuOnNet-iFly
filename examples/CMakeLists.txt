cmake_minimum_required(VERSION 3.17)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/depends/sdk/cmake")
include(depends/sdk/cmake/version.cmake)
configure_version(neuon_sample)
configure_birthday(neuon_sample)

project(neuon-sample VERSION ${version})
message(STATUS "Build ${PROJECT_NAME}-${version_revision} at ${birthday} on ${CMAKE_SYSTEM_NAME}")

find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost 1.70 REQUIRED COMPONENTS program_options)
find_package(FFMPEG REQUIRED COMPONENTS avcodec avformat swscale swresample)

if(NOT TARGET neuon::neuon)
    find_package(Neuon REQUIRED COMPONENTS headers neuon)
endif()

add_executable(neuon-sample
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/birthday.cpp
    src/neuon_sample.cpp
    depends/sdk/src/extraction.cpp
    depends/sdk/src/options.cpp
    depends/sdk/src/source.cpp
    depends/sdk/src/demuxer.cpp
    depends/sdk/src/decoder.cpp
    depends/sdk/src/interruption.cpp
    depends/sdk/src/track_adapter.c