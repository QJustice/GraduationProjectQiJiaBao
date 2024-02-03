# CMakeList.txt: paper_analysis 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# set XercesC_DIR to the path of the Xerces-C cmake directory
if (MSVC)
    set(XercesC_DIR "D:/LocalRepository/msvc_64/xerces-c/cmake/")
    set(duckx_DIR "D:/LocalRepository/msvc_64/duckx/lib/cmake/duckx/")
    set(jsoncpp_DIR "D:/LocalRepository/msvc_64/jsoncpp/lib/cmake/jsoncpp/")
    set(jsoncpp_LIBRARIES "jsoncpp_lib")
    set(jsoncpp_INCLUDE_DIRS "D:/LocalRepository/msvc_64/jsoncpp/include/")
    set(GTest_DIR "D:/LocalRepository/msvc_64/googletest-distribution/lib/cmake/GTest/")
    set(GTest_INCLUDE_DIRS "D:/LocalRepository/msvc_64/googletest-distribution/include/")
    include_directories("D:/LocalRepository/msvc_64/minidocx/include")
    set(minidocx_LIBRARIES "D:/LocalRepository/msvc_64/minidocx/lib/minidocx.lib")
elseif (MINGW)
    set(XercesC_DIR "D:/LocalRepository/mingw_64/xerces-c/cmake/")
    set(duckx_DIR "D:/LocalRepository/mingw_64/duckx/lib/cmake/duckx/")
    set(jsoncpp_DIR "D:/LocalRepository/mingw_64/jsoncpp/lib/cmake/jsoncpp/")
    set(jsoncpp_LIBRARIES "jsoncpp_lib")
    set(jsoncpp_INCLUDE_DIRS "D:/LocalRepository/mingw_64/jsoncpp/include/")
    set(GTest_DIR "D:/LocalRepository/mingw_64/googletest-distribution/lib/cmake/GTest/")
    set(GTest_INCLUDE_DIRS "D:/LocalRepository/mingw_64/googletest-distribution/include/")
    include_directories("D:/LocalRepository/mingw_64/minidocx/include")
    set(minidocx_LIBRARIES "D:/LocalRepository/mingw_64/minidocx/lib/libminidocx.a")
endif ()

set(GMOCK_LIBRARIES "GTest::gmock")
set(duckx_LIBRARIES "duckx::duckx")

find_package(GTest REQUIRED)
find_package(XercesC CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(duckx CONFIG REQUIRED)

include_directories("include")
include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCE
        include/Document.h
        include/Paragraph.h
        include/Run.h
        include/Style.h
        include/Template.h
        include/ErrorCode.h
        include/StringExtractor.h
        include/CommandParser.h
        include/XMLParserFactory.h
        include/DOMElementComparator.h
        include/NodeToElement.h
        include/EraseSpaces.h
        include/TransString.h
        include/FindElements.h
        src/main.cpp
        src/Document.cpp
        src/Paragraph.cpp
        src/Run.cpp
        src/Style.cpp
        src/Template.cpp
        src/ErrorCode.cpp
        src/StringExtractor.cpp
        src/CommandParser.cpp
        tools/XMLParserFactory.cpp
        tools/DOMElementComparator.cpp
        tools/NodeToElement.cpp
        tools/EraseSpaces.cpp
        tools/TransString.cpp
        tools/FindElements.cpp
)

# 将源代码添加到此项目的可执行文件。
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMOCK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${duckx_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${minidocx_LIBRARIES})

add_subdirectory("test")
enable_testing()

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET paper_analysis PROPERTY CXX_STANDARD 20)
endif ()

# TODO: 如有需要，请添加测试并安装目标。






#
#message(STATUS "duckx_DIR: " ${duckx_DIR})
#message(STATUS "duckx_LIBRARIES: " ${duckx_LIBRARIES})
#message(STATUS "duckx_VERSION: " ${duckx_VERSION})
#message(STATUS "duckx_FOUND: " ${duckx_FOUND})
#message(STATUS "duckx_PATH: " ${duckx_DIR})
#
#message(STATUS "GTEST_BOTH_LIBRARIES: " ${GTEST_BOTH_LIBRARIES})
#message(STATUS "GTEST_LIBRARIES: " ${GTEST_LIBRARIES})
#message(STATUS "GTEST_MAIN_LIBRARIES: " ${GTEST_MAIN_LIBRARIES})
#message(STATUS "GTEST_INCLUDE_DIRS: " ${GTEST_INCLUDE_DIRS})
#message(STATUS "GMOCK_LIBRARIES: " ${GMOCK_LIBRARIES})
#
#message(STATUS "XercesC_INCLUDE_DIRS: " ${XercesC_INCLUDE_DIRS})
#message(STATUS "XercesC_LIBRARIES: " ${XercesC_LIBRARIES})
#message(STATUS "XercesC_VERSION: " ${XercesC_VERSION})
#message(STATUS "XercesC_FOUND: " ${XercesC_FOUND})
#message(STATUS "XercesC_PATH: " ${XercesC_DIR})
#
#message(STATUS "Jsoncpp_INCLUDE_DIRS: ${jsoncpp_INCLUDE_DIRS}")
#message(STATUS "Jsoncpp_LIBRARIES: ${jsoncpp_LIBRARIES}")
#message(STATUS "Jsoncpp_VERSION: ${jsoncpp_VERSION}")
#message(STATUS "Jsoncpp_FOUND: ${jsoncpp_FOUND}")
#message(STATUS "Jsoncpp_DIR: ${jsoncpp_DIR}")
#
## 输出cmake版本
#message(STATUS "cmake version: ${CMAKE_VERSION}")