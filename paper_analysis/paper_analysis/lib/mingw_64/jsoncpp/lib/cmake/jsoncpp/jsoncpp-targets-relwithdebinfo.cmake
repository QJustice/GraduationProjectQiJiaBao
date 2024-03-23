#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "jsoncpp_lib" for configuration "RelWithDebInfo"
set_property(TARGET jsoncpp_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(jsoncpp_lib PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libjsoncpp.dll.a"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/libjsoncpp.dll"
  )

list(APPEND _cmake_import_check_targets jsoncpp_lib )
list(APPEND _cmake_import_check_files_for_jsoncpp_lib "${_IMPORT_PREFIX}/lib/libjsoncpp.dll.a" "${_IMPORT_PREFIX}/bin/libjsoncpp.dll" )

# Import target "jsoncpp_static" for configuration "RelWithDebInfo"
set_property(TARGET jsoncpp_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(jsoncpp_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libjsoncpp.a"
  )

list(APPEND _cmake_import_check_targets jsoncpp_static )
list(APPEND _cmake_import_check_files_for_jsoncpp_static "${_IMPORT_PREFIX}/lib/libjsoncpp.a" )

# Import target "jsoncpp_object" for configuration "RelWithDebInfo"
set_property(TARGET jsoncpp_object APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(jsoncpp_object PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELWITHDEBINFO ""
  IMPORTED_OBJECTS_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_reader.cpp.obj;${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_value.cpp.obj;${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_writer.cpp.obj"
  )

list(APPEND _cmake_import_check_targets jsoncpp_object )
list(APPEND _cmake_import_check_files_for_jsoncpp_object "${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_reader.cpp.obj;${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_value.cpp.obj;${_IMPORT_PREFIX}/lib/objects-RelWithDebInfo/jsoncpp_object/json_writer.cpp.obj" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
