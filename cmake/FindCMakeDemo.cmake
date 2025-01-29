# - Try to find the Imagequality_Dalys library
# Once done this will define
#
#  Imagequality_Dalys_FOUND - system has Imagequality_Dalys
#  Imagequality_Dalys_INCLUDE_DIR - Imagequality_Dalys include directory
#  Imagequality_Dalys_LIB - Imagequality_Dalys library directory
#  Imagequality_Dalys_LIBRARIES - Imagequality_Dalys libraries to link

if(Imagequality_Dalys_FOUND)
    return()
endif()

# We prioritize libraries installed in /usr/local with the prefix .../Imagequality_Dalys-*,
# so we make a list of them here
file(GLOB lib_glob "/usr/local/lib/Imagequality_Dalys-*")
file(GLOB inc_glob "/usr/local/include/Imagequality_Dalys-*")

# Find the library with the name "Imagequality_Dalys" on the system. Store the final path
# in the variable Imagequality_Dalys_LIB
find_library(Imagequality_Dalys_LIB
    # The library is named "Imagequality_Dalys", but can have various library forms, like
    # libImagequality_Dalys.a, libImagequality_Dalys.so, libImagequality_Dalys.so.1.x, etc. This should
    # search for any of these.
    NAMES Imagequality_Dalys
    # Provide a list of places to look based on prior knowledge about the system.
    # We want the user to override /usr/local with environment variables, so
    # this is included here.
    HINTS
        ${Imagequality_Dalys_DIR}
        ${Imagequality_Dalys_DIR}
        $ENV{Imagequality_Dalys_DIR}
        $ENV{Imagequality_Dalys_DIR}
        ENV Imagequality_Dalys_DIR
    # Provide a list of places to look as defaults. /usr/local shows up because
    # that's the default install location for most libs. The globbed paths also
    # are placed here as well.
    PATHS
        /usr
        /usr/local
        /usr/local/lib
        ${lib_glob}
    # Constrain the end of the full path to the detected library, not including
    # the name of library itself.
    PATH_SUFFIXES 
        lib
)

# Find the path to the file "ImageQuality.hpp" on the system. Store the final
# path in the variables Imagequality_Dalys_INCLUDE_DIR. The HINTS, PATHS, and
# PATH_SUFFIXES, arguments have the same meaning as in find_library().
find_path(Imagequality_Dalys_INCLUDE_DIR source_file.hpp
    HINTS
        ${Imagequality_Dalys_DIR}
        ${Imagequality_Dalys_DIR}
        $ENV{Imagequality_Dalys_DIR}
        $ENV{Imagequality_Dalys_DIR}
        ENV Imagequality_Dalys_DIR
    PATHS
        /usr
        /usr/local
        /usr/local/include
        ${inc_glob}
    PATH_SUFFIXES 
        include
)


# Check that both the paths to the include and library directory were found.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Imagequality_Dalys
    "\nImagequality_Dalys not found --- You can download it using:\n\tgit clone
    https://github.com/mmorse1217/cmake-project-template\n and setting the Imagequality_Dalys_DIR environment variable accordingly"
    Imagequality_Dalys_LIB Imagequality_Dalys_INCLUDE_DIR)

# These variables don't show up in the GUI version of CMake. Not required but
# people seem to do this...
mark_as_advanced(Imagequality_Dalys_INCLUDE_DIR Imagequality_Dalys_LIB)

# Finish defining the variables specified above. Variables names here follow
# CMake convention.
set(Imagequality_Dalys_INCLUDE_DIRS ${Imagequality_Dalys_INCLUDE_DIR})
set(Imagequality_Dalys_LIBRARIES ${Imagequality_Dalys_LIB})

# If the above CMake code was successful and we found the library, and there is
# no target defined, lets make one.
if(Imagequality_Dalys_FOUND AND NOT TARGET Imagequality_Dalys::Imagequality_Dalys)
    add_library(Imagequality_Dalys::Imagequality_Dalys UNKNOWN IMPORTED)
    # Set location of interface include directory, i.e., the directory
    # containing the header files for the installed library
    set_target_properties(Imagequality_Dalys::Imagequality_Dalys PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Imagequality_Dalys_INCLUDE_DIRS}"
        )

    # Set location of the installed library
    set_target_properties(Imagequality_Dalys::Imagequality_Dalys PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        IMPORTED_LOCATION "${Imagequality_Dalys_LIBRARIES}"
        )
endif()
