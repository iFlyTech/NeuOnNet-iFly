function(configure_version symbols_space_name)
    message(STATUS "You may specify version and revision variables to overload default all-zeroes filled values")
    if (NOT DEFINED version)
        set(version 0.0.0 CACHE INTERNAL "Version String")
    endif ()
    if (NOT DEFINED revision)
        set(revision 0000000 CACHE INTERNAL "Revision String")
    endif ()
    if (NOT DEFINED symbols_space_name)
        message(FATAL_ERROR "You have to define variable named symbols_space_name to be able to use automatic version string generator")
    endif ()

    set(version_revision ${version}+g${revision} CACH