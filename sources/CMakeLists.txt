cmake_minimum_required(VERSION 3.17)
cmake_policy(PUSH)
cmake_policy(VERSION 3.17)

include(../depends/sdk/cmake/version.cmake)
configure_version(neuon)
configure_birthday(neuon)

include(GNUInstallDirs)

project(neuon-library VERSION ${version} LANGUAGES CXX)

if (NOT TARGET neuon::headers)
 