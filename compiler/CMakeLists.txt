add_subdirectory(caic)
add_subdirectory(caic_parse)

add_executable(caic ${EXECUTABLE_SOURCES})

add_library(cailib STATIC ${ALL_OBJECT_FILES})

target_link_directories(
  caic PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_directories(
  cailib PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)