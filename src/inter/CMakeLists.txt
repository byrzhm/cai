add_library(cai_inter OBJECT inter.cpp)

target_include_directories(cai_inter PRIVATE ${CAI_INCLUDE_DIR})

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cai_inter>
    PARENT_SCOPE)