
project("my_test")


include(CTest)
include(GoogleTest)

add_subdirectory("ParagraphPropertiesTest")
add_subdirectory("RunPropertiesTest")
add_subdirectory("ParagraphParserTest")

