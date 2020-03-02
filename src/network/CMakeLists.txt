# source file list
set(SOURCES
  network.cpp
)

message("/src/network SOURCES => ${SOURCES}")

add_compile_definitions(NETWORK_EXPORTS)

find_path(WEBSOCKETPP_INCLUDE_DIR
  NAME client.hpp
  HINTS )
message("WEBSOCKETPP_INCLUDE_DIR => ${WEBSOCKETPP_INCLUDE_DIR}")

include_directories(${WEBSOCKETPP_INCLUDE_DIR})

set(MODULE_NAME network)

add_library(${MODULE_NAME}
  SHARED
    ${SOURCES}
)

target_link_libraries(${MODULE_NAME}
  common
)
