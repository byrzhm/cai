add_library(cai_driver OBJECT cai_driver.cpp)

target_include_directories(cai_driver PUBLIC ${CAI_INCLUDE_DIR})

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cai_driver>
    PARENT_SCOPE)