#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpr" for configuration "Release"
set_property(TARGET cpr APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cpr PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "${_IMPORT_PREFIX}/lib/libcurl.a"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libcpr.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS cpr )
list(APPEND _IMPORT_CHECK_FILES_FOR_cpr "${_IMPORT_PREFIX}/lib/libcpr.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
