cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(caic VERSION 1.0 LANGUAGES C CXX)

add_subdirectory(compiler)
add_subdirectory(unittests)
add_subdirectory(external)