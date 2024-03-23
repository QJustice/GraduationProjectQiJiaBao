#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "duckx::duckx" for configuration "RelWithDebInfo"
set_property(TARGET duckx::duckx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(duckx::duckx PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/duckx.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/duckx.dll"
  )

list(APPEND _cmake_import_check_targets duckx::duckx )
list(APPEND _cmake_import_check_files_for_duckx::duckx "${_IMPORT_PREFIX}/lib/duckx.lib" "${_IMPORT_PREFIX}/bin/duckx.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
