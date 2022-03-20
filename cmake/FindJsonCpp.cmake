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
    set(_