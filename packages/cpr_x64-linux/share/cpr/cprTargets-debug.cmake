#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpr" for configuration "Debug"
set_property(TARGET cpr APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cpr PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "${_IMPORT_PREFIX}/debug/lib/libcurl.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/libcpr.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS cpr )
list(APPEND _IMPORT_CHECK_FILES_FOR_cpr "${_IMPORT_PREFIX}/debug/lib/libcpr.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
