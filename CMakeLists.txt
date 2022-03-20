cmake_minimum_required(VERSION 3.17)
cmake_policy(PUSH)
cmake_policy(VERSION 3.17)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/depends/sdk/cmake")
include(depends/sdk/cmake/version.cmake)
configure_version(neuon)
configure_birthday(neuon)

project(neuon VERSION ${version} LANGUAGES CXX)
message(STATUS "Build ${PROJECT_NAME}-${version_revision} at ${birthday} on ${CMAKE_SYSTEM_NAME}")

add_subdirectory(headers)
add_subdirectory(sources)
add_subdirectory(examples)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
configure_package_config_file(res/neuon-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/neuon-config.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
write_basic_package_version_file( ${CMAKE_CURRENT_BINARY_DIR}/neuon-config-version.cmake VERSION ${version} COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/neuon-config.cmake ${CMAKE_CURRENT_BINARY_DIR}/neuon-config-version.cmake DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/neuon/cmake COMPONENT devel)

install(FILES cmake/FindTensorflow.cmake DESTINATION ${CMAKE_INSTALL_