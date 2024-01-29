add_library(cai_ast OBJECT ast.cpp)

target_include_directories(
    cai_ast
        PRIVATE
            ${CAI_INCLUDE_DIR}
)

target_link_libraries(cai_ast PRIVATE ${llvm_libs})

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cai_ast>
    PARENT_SCOPE)