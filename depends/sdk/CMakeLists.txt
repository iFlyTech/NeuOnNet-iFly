
CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
ENABLE_TESTING()

cmake_policy(VERSION 3.17)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cmake/version.cmake)
configure_version(mementor)
configure_birthday(mementor)

include(cmake/export.cmake)
configure_export(MEMENTOR mementor)

project(mementor VERSION ${version})
message(STATUS "Build ${PROJECT_NAME}-${version_revision} at ${birthday} on ${CMAKE_SYSTEM_NAME}")

find_package(FFMPEG COMPONENTS avcodec avformat swscale swresample)
find_package(Boost 1.70 MODULE REQUIRED COMPONENTS program_options log log_setup)
find_package(CURL)
find_package(spdlog)
find_package(GTest 1.8 CONFIG REQUIRED COMPONENTS gtest gmock gmock_main )
include(GoogleTest)

if(CURL_FOUND)
    add_library(curl OBJECT src/curl)
    target_link_libraries(curl PUBLIC CURL::libcurl)
    add_executable(ut_curl
        test/ut_curl.cpp
        src/curl.cpp
        )
    target_link_libraries(ut_curl PRIVATE GTest::gmock GTest::gmock_main CURL::libcurl)
    target_include_directories(ut_curl PRIVATE src/)
    gtest_discover_tests(ut_curl)
endif()
