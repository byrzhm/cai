add_library(cai_util OBJECT cai_log.cpp)

target_include_directories(cai_util
    PRIVATE
        ${THIRD_PARTY_DIR}/termcolor/include
        ${CAI_INCLUDE_DIR}
)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cai_util>
    PARENT_SCOPE)