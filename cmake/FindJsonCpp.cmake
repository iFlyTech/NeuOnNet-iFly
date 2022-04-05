# - Find jsoncpp - Overarching find module
# This is a over-arching find module to find older jsoncpp versions and those sadly built
# without JSONCPP_WITH_CMAKE_PACKAGE=ON, as well as those built with the cmake config file.
# It also wraps the different versions of the module.
#
# On CMake 3.0 and newer:
#  JsonCpp::JsonCpp - Imported target (possibly an interface/alias) to use:
#  if anything is populated, this is. If both shared and static are found, then
#  this will be the static version on DLL platforms and shared on non-DLL platforms.
#  JsonCpp::JsonCppShared - Imported target (possibly an interface/alias) for a
#  shared library version.
#  JsonCpp::JsonCppStatic - Imported target (possibly an interface/alias) for a
#  static library version.
#
# On all CMake versions: (Note that on CMake 2.8.10 and earlier, you may need to use JSONCPP_INCLUDE_DIRS)
#  JSONCPP_LIBRARY - wraps JsonCpp::JsonCpp or equiv.
#  JSONCPP_LIBRARY_IS_SHARED - if we know for sure JSONCPP_LIBRARY is shared, this is true-ish. We try to "un-set" it if we don't know one way or another.
#  JSONCPP_LIBRARY_SHARED - wraps JsonCpp::JsonCppShared or equiv.
#  JSONCPP_LIBRARY_STATIC - wraps JsonCpp::JsonCppStatic or equiv.
#  JSONCPP_INCLUDE_DIRS - Include directories - should (generally?) not needed if you require CMake 2.8.11+ since it handles target include directories.
#
#  JSONCPP_FOUND - True if JsonCpp was found.
#
# Original Author:
# 2016 Ryan Pavlik <ryan.pavlik@gmail.com>
# Incorporates work from the module contributed to VRPN under the same license:
# 2011 Philippe Crassous (ENSAM ParisTech / Institut Image) p.crassous _at_ free.fr
#
# Copyright Philippe Crassous 2011.
# Copyright Sensics, Inc. 2016.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

set(__jsoncpp_have_namespaced_targets OFF)
set(__jsoncpp_have_interface_support OFF)
if (NOT ("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 3.0))
    set(__jsoncpp_have_namespaced_targets ON)
    set(__jsoncpp_have_interface_support ON)
elseif (("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" EQUAL 2.8) AND "${CMAKE_PATCH_VERSION}" GREATER 10)
    set(__jsoncpp_have_interface_support ON)
endif ()

# sets __jsoncpp_have_jsoncpplib based on whether or not we have a real imported jsoncpp_lib target.
macro(_jsoncpp_check_for_real_jsoncpplib)
    set(__jsoncpp_have_jsoncpplib FALSE)
    if (TARGET jsoncpp_lib)
        get_property(__jsoncpp_lib_type TARGET jsoncpp_lib PROPERTY TYPE)
        # We make interface libraries. If an actual config module made it, it would be an imported library.
        if (NOT __jsoncpp_lib_type STREQUAL "INTERFACE_LIBRARY")
            set(__jsoncpp_have_jsoncpplib TRUE)
        endif ()
    endif ()
    #message(STATUS "__jsoncpp_have_jsoncpplib ${__jsoncpp_have_jsoncpplib}")
endmacro()

include(FindPackageHandleStandardArgs)
# Ensure that if this is TRUE later, it's because we set it.
set(JSONCPP_FOUND FALSE)
set(__jsoncpp_have_jsoncpplib FALSE)

# See if we find a CMake config file - there is no harm in calling this more than once,
# and we need to call it at least once every CMake invocation to create the original
# imported targets, since those don't stick around like cache variables.
find_package(jsoncpp QUIET NO_MODULE)

if (jsoncpp_FOUND)
    # Build a string to help us figure out when to invalidate our cache variables.
    # start with where we found jsoncpp
    set(__jsoncpp_info_string "[${jsoncpp_DIR}]")

    # part of the string to indicate if we found a real jsoncpp_lib (and what kind)
    _jsoncpp_check_for_real_jsoncpplib()

    macro(_jsoncpp_apply_map_config target)
        if (MSVC)
            # Can't do this - different runtimes, incompatible ABI, etc.
            set(_jsoncpp_debug_fallback)
        else ()
            set(_jsoncpp_debug_fallback DEBUG)
            #osvr_stash_map_config(DEBUG DEBUG RELWITHDEBINFO RELEASE MINSIZEREL NONE)
        endif ()
        # Appending, just in case using project or upstream fixes this.
        set_property(TARGET ${target} APPEND PROPERTY MAP_IMPORTED_CONFIG_RELEASE RELEASE RELWITHDEBINFO MINSIZEREL NONE ${_jsoncpp_debug_fallback})
        set_property(TARGET ${target} APPEND PROPERTY MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELWITHDEBINFO RELEASE MINSIZEREL NONE ${_jsoncpp_debug_fallback})
        set_property(TARGET ${target} APPEND PROPERTY MAP_IMPORTED_CONFIG_MINSIZEREL MINSIZEREL RELEASE RELWITHDEBINFO NONE ${_jsoncpp_debug_fallback})
        set_property(TARGET ${target} APPEND PROPERTY MAP_IMPORTED_CONFIG_NONE NONE RELEASE RELWITHDEBINFO MINSIZEREL ${_jsoncpp_debug_fallback})
        if (NOT MSVC)
            set_property(TARGET ${target} APPEND PROPERTY MAP_IMPORTED_CONFIG_DEBUG DEBUG RELWITHDEBINFO RELEASE MINSIZEREL NONE)
        endif ()
    endmacro()
    if (__jsoncpp_have_jsoncpplib)
        list(APPEND __jsoncpp_info_string "[${__jsoncpp_lib_type}]")
        _jsoncpp_apply_map_config(jsoncpp_lib)
    else ()
        list(APPEND __jsoncpp_info_string "[]")
    endif ()
    # part of the string to indicate if we found jsoncpp_static
    if (TARGET jsoncpp_static OR TARGET jsoncpp_lib_static)
        list(APPEND __jsoncpp_info_string "[T]")
        _jsoncpp_apply_map_config(jsoncpp_static)
    else ()
        list(APPEND __jsoncpp_info_string "[]")
    endif ()
endif ()


# If we found something, and it's not the exact same as what we've found before...
# NOTE: The contents of this "if" block update only (internal) cache variables!
# (since this will only get run the first CMake pass that finds jsoncpp or that finds a different/updated install)
if (jsoncpp_FOUND AND NOT __jsoncpp_info_string STREQUAL "${JSONCPP_CACHED_JSONCPP_DIR_DETAILS}")
    #message("Updating jsoncpp cache variables! ${__jsoncpp_info_string}")
    set(JSONCPP_CACHED_JSONCPP_DIR_DETAILS "${__jsoncpp_info_string}" CACHE INTERNAL "" FORCE)
    unset(JSONCPP_IMPORTED_LIBRARY_SHARED)
    unset(JSONCPP_IMPORTED_LIBRARY_STATIC)
    unset(JSONCPP_IMPORTED_LIBRARY)
    unset(JSONCPP_IMPORTED_INCLUDE_DIRS)
    unset(JSONCPP_IMPORTED_LIBRARY_IS_SHARED)

    # if(__jsoncpp_have_jsoncpplib) is equivalent to if(TARGET jsoncpp_lib) except it excludes our
    # "invented" jsoncpp_lib interface targets, made for convenience purposes after this block.

    if (__jsoncpp_have_jsoncpplib AND (TARGET jsoncpp_static OR TARGET jsoncpp_lib_static) )

        # A veritable cache of riches - we have both shared and static!
        set(JSONCPP_IMPORTED_LIBRARY_SHARED jsoncpp_lib CACHE INTERNAL "" FORCE)
        if(TARGET jsoncpp_static)
            set(JSONCPP_IMPORTED_LIBRARY_STATIC jsoncpp_static CACHE INTERNAL "" FORCE)
        else()
            set(JSONCPP_IMPORTED_LIBRARY_STATIC jsoncpp_lib_static CACHE INTERNAL "" FORCE)
        endif()
        if (WIN32 OR CYGWIN OR MINGW)
            # DLL platforms: static library should be default
            set(JSONCPP_IMPORTED_LIBRARY ${JSONCPP_IMPORTED_LIBRARY_STATIC} CACHE INTERNAL "" FORCE)
            set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED FALSE CACHE INTERNAL "" FORCE)
        else ()
            # Other platforms - might require PIC to be linked into shared libraries, so safest to prefer shared.
            set(JSONCPP_IMPORTED_LIBRARY ${JSONCPP_IMPORTED_LIBRARY_SHARED} CACHE INTERNAL "" FORCE)
            set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED TRUE CACHE INTERNAL "" FORCE)
        endif ()

    elseif (TARGET jsoncpp_static )
        # Well, only one variant, but we know for sure that it's static.
        set(JSONCPP_IMPORTED_LIBRARY_STATIC jsoncpp_static CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY jsoncpp_static CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED FALSE CACHE INTERNAL "" FORCE)
    elseif (TARGET jsoncpp_lib_static)
        # Well, only one variant, but we know for sure that it's static.
        set(JSONCPP_IMPORTED_LIBRARY_STATIC jsoncpp_lib_static CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY jsoncpp_lib_static CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED FALSE CACHE INTERNAL "" FORCE)
    elseif (__jsoncpp_have_jsoncpplib AND __jsoncpp_lib_type STREQUAL "STATIC_LIBRARY")
        # We were able to figure out the mystery library is static!
        set(JSONCPP_IMPORTED_LIBRARY_STATIC jsoncpp_lib CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY jsoncpp_lib CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED FALSE CACHE INTERNAL "" FORCE)

    elseif (__jsoncpp_have_jsoncpplib AND __jsoncpp_lib_type STREQUAL "SHARED_LIBRARY")
        # We were able to figure out the mystery library is shared!
        set(JSONCPP_IMPORTED_LIBRARY_SHARED jsoncpp_lib CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY jsoncpp_lib CACHE INTERNAL "" FORCE)
        set(JSONCPP_IMPORTED_LIBRARY_IS_SHARED TRUE CACHE INTERNAL "" FORCE)

    elseif (__jsoncpp_have_jsoncpplib)
        # One variant, and we have no idea if this is just an old version or if
        # this is shared based on the target name alone. Hmm.
        set(JSONCPP_IMPORTED_LIBRARY jsoncpp_lib CACHE INTERNAL "" FORCE)
    endif ()

    # Now, we need include directories. Can't just limit this to old CMakes, since
    # new CMakes might be used to build projects designed to support older ones.
    if (__jsoncpp_have_jsoncpplib)
        get_property(__jsoncpp_interface_include_dirs TARGET jsoncpp_lib PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
        if (__jsoncpp_interface_include_dirs)
            set(JSONCPP_IMPORTED_INCLUDE_DIRS "${__jsoncpp_interface_include_dirs}" CACHE INTERNAL "" FORCE)
        endif ()
    endif ()
    if ((TARGET jsoncpp_static OR TARGET jsoncpp_lib_static) AND NOT JSONCPP_IMPO