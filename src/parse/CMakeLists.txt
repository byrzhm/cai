#
# See
#   https://cmake.org/cmake/help/latest/module/FindBISON.html
#   https://cmake.org/cmake/help/latest/module/FindFLEX.html
#
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(GENERATED_SOURCE_FILES 
    ${CAI_SOURCE_DIR}/parse/yy_parser.cc
    ${CAI_SOURCE_DIR}/parse/yy_lexer.cc
)
set(GENERATE_SCRIPT ${CAI_SCRIPTS_DIR}/gen_parser.sh)
set(LEXER_FILE lexer.ll)
set(PARSER_FILE parser.yy)

add_custom_command(
    OUTPUT ${GENERATED_SOURCE_FILES}
    COMMAND cd ${CMAKE_SOURCE_DIR} && ${GENERATE_SCRIPT}
    DEPENDS ${LEXER_FILE} ${PARSER_FILE} ${GENERATE_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating parser and lexer"
)

add_custom_target(
    generate_parser
    DEPENDS ${GENERATED_SOURCE_FILES}
)

add_library(cai_parser OBJECT yy_driver.cpp ${GENERATED_SOURCE_FILES})

target_include_directories(
    cai_parser
        PRIVATE
            ${CAI_INCLUDE_DIR}
            ${CAI_INCLUDE_DIR}/parse
)

add_dependencies(cai_parser generate_parser)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cai_parser>
    PARENT_SCOPE)