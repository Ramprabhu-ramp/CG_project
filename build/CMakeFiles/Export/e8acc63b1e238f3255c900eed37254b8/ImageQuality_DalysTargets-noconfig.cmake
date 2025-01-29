#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ImageQuality_Dalys::ImageQuality_Dalys" for configuration ""
set_property(TARGET ImageQuality_Dalys::ImageQuality_Dalys APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ImageQuality_Dalys::ImageQuality_Dalys PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libImageQuality_Dalys.a"
  )

list(APPEND _cmake_import_check_targets ImageQuality_Dalys::ImageQuality_Dalys )
list(APPEND _cmake_import_check_files_for_ImageQuality_Dalys::ImageQuality_Dalys "${_IMPORT_PREFIX}/lib/libImageQuality_Dalys.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
