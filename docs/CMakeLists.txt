# doxygen
set(DOC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${DOC_OUTPUT_DIR}/Doxyfile
    @ONLY
)

add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${DOC_OUTPUT_DIR}/Doxyfile
    WORKING_DIRECTORY ${DOC_OUTPUT_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
)
