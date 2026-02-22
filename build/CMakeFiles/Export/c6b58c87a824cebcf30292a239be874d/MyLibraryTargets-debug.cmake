#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyLibrary::MyLibrary" for configuration "Debug"
set_property(TARGET MyLibrary::MyLibrary APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MyLibrary::MyLibrary PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/MyLibrary.lib"
  )

list(APPEND _cmake_import_check_targets MyLibrary::MyLibrary )
list(APPEND _cmake_import_check_files_for_MyLibrary::MyLibrary "${_IMPORT_PREFIX}/lib/MyLibrary.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
