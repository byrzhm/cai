cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(caic VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CAI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CAI_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CAI_SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/scripts)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

add_compile_options(-Wno-format-security)

## Boost
find_package(Boost REQUIRED COMPONENTS program_options)

## LLVM
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(llvm_libs support core irreader)

## termcolor
include_directories(${THIRD_PARTY_DIR}/termcolor/include)

## subdirectories
add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(unittests)
add_subdirectory(test)
add_subdirectory(app)

## Doxygen 文档生成
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_subdirectory(docs)
else(DOXYGEN_FOUND)
    message("Doxygen not found")
endif(DOXYGEN_FOUND)