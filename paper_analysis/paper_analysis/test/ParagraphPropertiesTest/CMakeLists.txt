
project(ParagraphPropertiesTest)

set(CMAKE_CXX_STANDARD 23)
set( SOURCE
        paragraph_properties.cpp
        paragraph_properties.h
        main.cpp
)
add_executable(ParagraphPropertiesTest ${SOURCE})

# link_libraries(${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})

add_test(NAME ParagraphPropertiesTest COMMAND test)