cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

add_executable(parse_args_test parse_args_test.cpp)

gtest_add_tests(TARGET parse_args_test)
message(STATUS "parse_args_test added to tests")

target_link_libraries(parse_args_test PRIVATE
    gtest_main
    Boost::program_options
)

target_compile_features(parse_args_test PRIVATE cxx_std_17)

set_target_properties(parse_args_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/arg
)