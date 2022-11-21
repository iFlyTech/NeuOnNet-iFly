cmake_minimum_required(VERSION 3.17)
cmake_policy(PUSH)
cmake_policy(VERSION 3.17)

include(../depends/sdk/cmake/version.cmake)
configure_version(neuon)
configure_birthday(neuon)

include(GNUInstallDirs)

project(neuon-library VERSION ${version} LANGUAGES CXX)

if (NOT TARGET neuon::headers)
    find_package(neuon REQUIRED COMPONENTS headers)
endif()

find_package(Threads REQUIRED)
find_package(Tensorflow REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(spdlog REQUIRED)
find_package(dlib REQUIRED)
find_package(Aquila REQUIRED)
find_package(Boost 1.70 REQUIRED COMPONENTS program_options filesystem)
find_package(FFMPEG REQUIRED COMPONENTS avcodec avformat swscale swresample)
find_package(Python3 COMPONENTS Interpreter)
if (NOT Python3_FOUND)
    option(NEUON_PYTHON_EXECUTABLE "Set to Python 3 executable path" /usr/bin/python3)
    set(Python3_EXECUTABLE ${NEUON_PYTHON_EXECUTABLE})
    message(WARNING "Manually set python path to ${Python3_EXECUTABLE} as it was not found automatically")
endif ()

add_executable(neuon-data
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/generated/birthday.cpp
    src/demo.cpp
    src/neuon_data.cpp
    src/license.cpp
    ../depends/sdk/src/extraction.cpp
    ../depends/sdk/src/source.cpp
    ../depends/sdk/src/demuxer.cpp
    ../depends/sdk/src/decoder.cpp
    ../depends/sdk/src/interruption.cpp
    ../de