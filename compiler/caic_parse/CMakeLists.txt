add_library(
  caic_parse
  OBJECT
  parser.cpp
)

set(ALL_OBJECT_FILES
    ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:caic_parse>
    PARENT_SCOPE)