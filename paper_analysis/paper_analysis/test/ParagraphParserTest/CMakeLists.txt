
project(ParagraphParserTest)

set(CMAKE_CXX_STANDARD 23)
set(SOURCE
    main.cpp
    paragraph_parser.cpp
    paragraph_parser.h
)
add_executable(ParagraphParserTest ${SOURCE})

# link_libraries(${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMOCK_LIBRARIES})

gtest_discover_tests(ParagraphParserTest)