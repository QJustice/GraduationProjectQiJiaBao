# CMakeList.txt: PaperAnalysis 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PaperAnalysis")

# set XercesC_DIR to the path of the Xerces-C cmake directory
set (XercesC_DIR "C:/Program Files/xerces-c/cmake/")
set (jsoncpp_DIR "C:/Program Files/jsoncpp/lib/cmake/jsoncpp")
set (jsoncpp_LIBRARIES "jsoncpp_lib")
set (jsoncpp_INCLUDE_DIRS "C:/Program Files/jsoncpp/include/")

# find_package(XercesC REQUIRED)
find_package(XercesC CONFIG REQUIRED)
find_package (jsoncpp CONFIG REQUIRED)

message ("XercesC_INCLUDE_DIRS: " ${XercesC_INCLUDE_DIRS})
message ("XercesC_LIBRARIES: " ${XercesC_LIBRARIES})
message ("XercesC_VERSION: " ${XercesC_VERSION})
message ("XercesC_FOUND: " ${XercesC_FOUND})
message ("XercesC_PATH: " ${XercesC_DIR})

message(STATUS "jsoncpp_INCLUDE_DIRS: ${jsoncpp_INCLUDE_DIRS}")
message(STATUS "jsoncpp_LIBRARIES: ${jsoncpp_LIBRARIES}")
message(STATUS "jsoncpp_VERSION: ${jsoncpp_VERSION}")
message(STATUS "jsoncpp_FOUND: ${jsoncpp_FOUND}")
message(STATUS "jsoncpp_DIR: ${jsoncpp_DIR}")

set(SOURCE 
	src/PaperAnalysis.cpp
	src/PaperAnalysis.h
	src/test.cpp
)

# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} ${SOURCE})

# link_libraries(${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PaperAnalysis PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
