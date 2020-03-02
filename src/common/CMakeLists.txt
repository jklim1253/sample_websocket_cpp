# source file list
set(SOURCES
  elapsed_time.cpp
)

message("/src/common SOURCES => ${SOURCES}")

#add_compile_definitions(COMMON_EXPORTS)

set(MODULE_NAME common)

add_library(${MODULE_NAME}
  STATIC
    ${SOURCES}
)



