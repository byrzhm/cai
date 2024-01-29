add_subdirectory(driver)
add_subdirectory(ast)
add_subdirectory(inter)
add_subdirectory(parse)
add_subdirectory(util)

add_library(cai_lib STATIC ${ALL_OBJECT_FILES})