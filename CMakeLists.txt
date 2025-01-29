# CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ImageQuality_Dalys VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")


# Finding OpenCV
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "Found OpenCV: ${OpenCV_VERSION}")
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV and try again.")
endif()

# Finding LAPACK
find_package(LAPACK REQUIRED)
if(LAPACK_FOUND)
    message(STATUS "Found LAPACK")
else()
    message(FATAL_ERROR "LAPACK not found. Please install LAPACK and try again.")
endif()

# Prepend paths for source files
function(PREPEND var)
    set(listVar "")
    foreach(f ${${var}})
        list(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
    endforeach()
    set(${var} "${listVar}" PARENT_SCOPE)
endfunction()

# Source and include directories
add_subdirectory(src)
add_subdirectory(include)


# Header files
set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/ImageQuality.hpp
)

# Target library
add_library(ImageQuality_Dalys STATIC
        src/ImageQuality.cpp
        src/main.cpp
)

add_executable(ImageQuality_Executable src/main.cpp src/ImageQuality.cpp)
target_include_directories(ImageQuality_Executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Link libraries
target_link_libraries(ImageQuality_Dalys PUBLIC ${OpenCV_LIBS} ${LAPACK_LIBRARIES})
target_link_libraries(ImageQuality_Executable PRIVATE ${OpenCV_LIBS})

# Directories for the target
target_include_directories(ImageQuality_Dalys PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation
set(ImageQuality_Dalys_INCLUDE_DEST "include")
set(ImageQuality_Dalys_LIB_DEST "lib")

install(
        TARGETS ImageQuality_Dalys
        EXPORT ImageQuality_DalysTargets
        LIBRARY DESTINATION ${ImageQuality_Dalys_LIB_DEST}
        ARCHIVE DESTINATION ${ImageQuality_Dalys_LIB_DEST}
        INCLUDES DESTINATION ${ImageQuality_Dalys_INCLUDE_DEST}
)

install(
        EXPORT ImageQuality_DalysTargets
        FILE ImageQuality_DalysTargets.cmake
        NAMESPACE ImageQuality_Dalys::
        DESTINATION ${ImageQuality_Dalys_LIB_DEST}
)

install(FILES ${ImageQuality_Dalys_INC} DESTINATION ${ImageQuality_Dalys_INCLUDE_DEST})

# Version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ImageQuality_DalysConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
