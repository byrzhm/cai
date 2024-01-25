add_executable(caic main.cpp)

target_include_directories(caic
    PRIVATE
        ${CAI_INCLUDE_DIR}
)

target_link_libraries(caic
    PRIVATE
        Boost::program_options
        cai_lib
    )

target_compile_features(caic PRIVATE cxx_std_17)

set_target_properties(caic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/app
)