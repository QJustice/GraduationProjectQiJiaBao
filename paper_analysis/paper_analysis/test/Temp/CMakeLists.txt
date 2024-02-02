
project(Temp)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE
    main.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE})

# link_libraries(${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMOCK_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${duckx_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${minidocx_LIBRARIES})

gtest_discover_tests(${PROJECT_NAME})