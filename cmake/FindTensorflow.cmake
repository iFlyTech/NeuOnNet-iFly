cmake_policy(PUSH)
cmake_policy(VERSION 3.10)

find_package(PkgConfig QUIET)
if(${PKG_CONFIG_FOUND})
    pkg_check_modules(Tensorflow_PKGCONF QUIET tensorflow)
    if (Tensorflow_PKGCONF_INCLUDE_DIRS)
        set(Tensorflow_INCLUDE_HINTS ${Tensorflow_PKGCONF_INCLUDE_DIRS})
    endif ()
    if (Tensorflow_PKGCONF_LIBRARY_DIRS)
        set(Tensorflow_LIB_HINTS ${Tensorflow_PKGCONF_LIBRARY_DIRS})
    endif ()
    if (Tensorflow_PKGCONF_LIBRARIES)
        set(Tensorflow_LIB_NAMES ${Tensorflow_PKGCONF_LIBRARIES})
    endif ()
endif()

find_path(Tensorflow_INCLUDE_DIR NAMES tensorflow/c/c_api.h PATH_SUFFIXES tensorflow tensorflow/include HINTS 