
project("my_test")

add_executable(${PROJECT_NAME}  "my_test.cpp" "../header/paper_analysis.h" "../src/paper_analysis.cpp" "../src/translation_label.cpp" "../header/translation_label.h")

target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${jsoncpp_LIBRARIES})
