cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

set(CAI_PARSE_TESTS lexer_test parser_test)
foreach(CAI_PARSE_TEST_NAME ${CAI_PARSE_TESTS})
    add_executable(${CAI_PARSE_TEST_NAME} ${CAI_PARSE_TEST_NAME}.cpp)

    gtest_add_tests(TARGET ${CAI_PARSE_TEST_NAME})
    message(STATUS "Adding test ${CAI_PARSE_TEST_NAME}")

    target_include_directories(${CAI_PARSE_TEST_NAME} PRIVATE ${CAI_INCLUDE_DIR})

    target_link_libraries(${CAI_PARSE_TEST_NAME}
        PRIVATE
            cai_lib
            gmock_main
    )

    set_target_properties(${CAI_PARSE_TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittests/parse
    )
    
endforeach()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_files DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittests/parse)