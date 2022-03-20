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
#  JSONCPP_LIBRARY - wraps JsonCpp::JsonCpp or equi