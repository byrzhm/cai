cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(caic VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(unittests)
add_subdirectory(test)
add_subdirectory(app)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    add_subdirectory(docs)
else(DOXYGEN_FOUND)
    message("Doxygen not found")
endif(DOXYGEN_FOUND)