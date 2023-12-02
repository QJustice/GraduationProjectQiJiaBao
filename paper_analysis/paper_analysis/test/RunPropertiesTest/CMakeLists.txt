
project(RunPropertiesTest)

set(CMAKE_CXX_STANDARD 23)
set( SOURCE
        run_properties.cpp
        run_properties.cpp
        main.cpp
)
add_executable(RunPropertiesTest ${SOURCE})

# link_libraries(${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})

add_test(NAME RunPropertiesTest COMMAND test)