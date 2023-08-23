
project("my_test")

add_executable(${PROJECT_NAME}  "my_test.cpp" "../src/translation_label.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})
